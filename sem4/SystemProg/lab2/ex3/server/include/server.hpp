#pragma once

#include "shared_memory.hpp"


class Server {
private:
    SharedMemory memory;
    size_t count_thread;
public:
    explicit Server(size_t count_threads = 3, const char *ftok_shm_file = "/tmp", int ftok_shm_id = 12,
           const char *ftok_sem_file = "/tmp", int ftok_sem_id=15,
           size_t shm_size=4096);


    static void * processing() {
        // TODO
        return nullptr;
    }
};