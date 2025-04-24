#include <iostream>

#include "include/shared_memory.hpp"

int main() {
    SharedMemory memory{"/tmp", 112, "/tmp", 113, 1024};
    unsigned short a[2] = {0, 1};
    memory.set_sem_val(a);

    short b[2] = {0, -1};
    memory.change_sem_val(b);

    unsigned short r[2];
    memory.get_sem_val(r);
    for (auto el: r) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;

    SharedMemory::Msg msg = {12, 13};
    memory.send(&msg, SharedMemory::CLIENT);


    memory.get_sem_val(r);
    for (auto el: r) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}