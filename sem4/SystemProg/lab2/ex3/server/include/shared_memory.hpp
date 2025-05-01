#pragma once

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <cstring>
#include <iostream>
#include <ctime>


union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

class SharedMemory {
    // серверная версия
private:


    size_t size = 4096;
    int count_sems;
    int shm_id;
    int sem_id;
    void *data;
public:

    struct Msg {
        enum Type{
            CONNECT,
            REGISTER,
            EXIT,
            ERROR,
            DISCONNECT,
            SEND,
            GET,
            PUT_ALL_MSGS,
            STOP_SERVER
        }type;
        size_t count_pkgs;
        char login_sender[100];
        char login_recipient[100];
        char data[2048];
        std::time_t time;
    };

    explicit SharedMemory(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file, int ftok_sem_id,
                          size_t shm_size = 4096, int count_sems = 2);
    ~SharedMemory();

    void set_sem_val(unsigned short op[2]) const;
    void get_sem_val(unsigned short *res) const;
    void change_sem_val(short *op) const;
    void change_sem_val(short op, unsigned short num_sem) const;

    void send(const Msg *msg= nullptr);
    void rcv(const Msg *msg);
};

