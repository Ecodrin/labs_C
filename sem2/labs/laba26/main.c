#include "UDT.h"

int main() {
    udt u;
    udt_create(&u, 1);
    udt_push_front(&u, 1);
    udt_push_front(&u, 2);
    udt_push_front(&u, 3);

    udt_push_front(&u, 6);
    udt_push_front(&u, 7);
    udt_push_front(&u, -1);
    udt_push_front(&u, 4);
    udt_print(&u);
    bubbleSort(&u);
    udt_print(&u);
    udt_delete(&u);
    return 0;
}
