#pragma once

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <cstring>
#include <iostream>


union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

class SharedMemory {
private:
    constexpr static short default_block_user[2] = {0, -1};
    constexpr static short default_server_block_read[2] = {-1, 0};
    constexpr static short default_server_block_write[2] = {1, 1};
    constexpr static short default_user_block_read[2] = {-1, -1};
    constexpr static short default_user_block_write[2] = {0, 1};


    const size_t size = 4096;
    int count_sems;
    int shm_id;
    int sem_id;
    void * data;
public:

    struct Msg {
        size_t count_pkgs;
        size_t index_pkg;
        size_t size;
        char * data;
    };

    enum TypeUser {
        SERVER,
        CLIENT
    };

    explicit SharedMemory(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file, int ftok_sem_id,
                          size_t shm_size=4096, int count_sems = 2);
    ~SharedMemory();

    void set_sem_val(unsigned short op[2]) const;
    void get_sem_val(unsigned short * res) const;
    void change_sem_val(short * op) const;
    void change_sem_val(short op, unsigned short num_sem) const;

    void send(const Msg * msg, TypeUser type,
              const short* server_block_read=default_server_block_read,
              const short* server_block_write=default_server_block_write,
              const short* user_block_read=default_user_block_read,
              const short* user_block_write=default_user_block_write
              );
    void rcv(const Msg * msg, TypeUser type,
              const short* server_block_read=default_server_block_read,
              const short* server_block_write=default_server_block_write,
              const short* user_block_read=default_user_block_read,
              const short* user_block_write=default_user_block_write
    );
};

