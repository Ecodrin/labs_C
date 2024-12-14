#include "free-blocks-allocators.h"


int main() {
    Allocator* allocator = allocator_create(ALLOCATOR_SIZE);
    if (!allocator) {
        fprintf(stderr, "Failed to create allocator\n");
        return 1;
    }

    void* ptr1 = allocator_alloc(allocator, 100);
    void* ptr2 = allocator_alloc(allocator, 200);

    if (ptr1) {
        memset(ptr1, 0, 100);
        printf("Allocated 100 bytes at %p\n", ptr1);
    }

    if (ptr2) {
        memset(ptr2, 0, 200);
        printf("Allocated 200 bytes at %p\n", ptr2);
    }

    allocator_free(allocator, ptr1);
    allocator_free(allocator, ptr2);

    allocator_destroy(allocator);

    return 0;
}