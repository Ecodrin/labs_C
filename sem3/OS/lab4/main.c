#include <stdio.h>
#include <dlfcn.h>
#include <sys/mman.h>

#include "SystemErrors/errors.h"

#define MEMORY_SIZE 1024 * 1024

typedef struct Allocator Allocator;

typedef Allocator *create_allocator_func(void *memory, size_t size);

typedef void *allocator_alloc_func(Allocator *const allocator, const size_t size);

typedef void allocator_free_func(Allocator *const allocator, void *const memory);

typedef void allocator_destroy_func(Allocator *const allocator);

static create_allocator_func *create_allocator;
static allocator_alloc_func *allocator_alloc;
static allocator_free_func *allocator_free;
static allocator_destroy_func *allocator_destroy;


error_msg init_library(void *library) {
    create_allocator = dlsym(library, "allocator_create");
    if (create_allocator == NULL) {
        dlclose(library);
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "main", "failed to find create function"};
    }

    allocator_alloc = dlsym(library, "allocator_alloc");
    if (allocator_alloc == NULL) {
        dlclose(library);
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "main", "failed to find alloc function"};
    }

    allocator_free = dlsym(library, "allocator_free");
    if (allocator_free == NULL) {
        dlclose(library);
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "main", "failed to find free function"};
    }

    allocator_destroy = dlsym(library, "allocator_destroy");
    if (allocator_destroy == NULL) {
        dlclose(library);
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "main", "failed to find destroy function"};
    }
    return (error_msg) {SUCCESS, "", ""};
}


int main(int argc, char **argv) {

    void *library = NULL;

    if (argc == 2) {
        library = dlopen(argv[1], RTLD_LOCAL | RTLD_NOW);
    }
    if (argc != 2 || library == NULL) {
        library = dlopen("libfree-block-allocator.so", RTLD_GLOBAL | RTLD_LAZY);
    }
    if (library == NULL) {
        return print_error((error_msg) {INCORRECT_OPTIONS_ERROR, "main", "incorrect count args"});
    }

    void *memory = mmap(
            NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0
    );

    if (memory == MAP_FAILED) {
        return print_error((error_msg) {MEMORY_ALLOCATED_ERROR, "main", "map"});
    }

    error_msg errorMsg = init_library(library);
    if(errorMsg.type){
        dlclose(library);
        return print_error(errorMsg);
    }

    Allocator * allocator = create_allocator(memory, MEMORY_SIZE);
    if(allocator == NULL){
        return print_error((error_msg) {MEMORY_ALLOCATED_ERROR, "main", "allocator didn't create"});
    }

    // Тест
    int * a = allocator_alloc(allocator, sizeof(int) * 10);
    if(a == NULL){
        return print_error((error_msg) {MEMORY_ALLOCATED_ERROR, "main", "memory allocated"});
    }
    a[0] = 13;
    a[9] = 19;
    printf("%d %d\n", a[0], a[9]);

    allocator_free(allocator, a);

    allocator_destroy(allocator);

    dlclose(library);
    return 0;
}