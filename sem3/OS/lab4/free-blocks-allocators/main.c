#include "free-block-allocator.h"

struct Point{
    int x;
    int y;
};

int main() {
    Allocator *allocator = allocator_create(ALLOCATOR_SIZE);
    if (!allocator) {
        fprintf(stderr, "Failed to create allocator\n");
        return 1;
    }

    struct Point *ptr1 = allocator_alloc(allocator, sizeof(struct Point));
    struct Point *ptr2 = allocator_alloc(allocator, sizeof(struct Point));
    if (ptr1 == NULL) {
        exit(2);
    }

    if (ptr2 == NULL) {
        memset(ptr2, 0, 200);

        exit(2);
    }
    ptr1->x = 12;
    ptr1->y = 13;
    ptr2->x = -12;
    ptr2->y = -13;
    printf("Point 1: %d %d\n", ptr1->x, ptr1->y);
    printf("Point 2: %d %d\n", ptr2->x, ptr2->y);


    allocator_free(allocator, ptr1);
    allocator_free(allocator, ptr2);

    allocator_destroy(allocator);

    return 0;
}