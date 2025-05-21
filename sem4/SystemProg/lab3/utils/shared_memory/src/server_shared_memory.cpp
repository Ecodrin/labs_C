#include "../include/server_shared_memory.hpp"

ServerSharedMemory::ServerSharedMemory(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file, int ftok_sem_id,
                                       size_t shm_size, int count_sems) : size{shm_size}, count_sems{count_sems} {
    key_t shm_key = ftok(ftok_shm_file, ftok_shm_id);
    if (shm_key == -1) {
        throw std::invalid_argument("ftok shared memory returned -1");
    }
    shm_id = shmget(shm_key, shm_size, IPC_CREAT | 0666);
    if (shm_id == -1) {
        throw std::invalid_argument("shmget returned -1");
    }

    key_t sem_key = ftok(ftok_sem_file, ftok_sem_id);
    if (sem_key == -1) {
        shmctl(sem_id, 0, IPC_RMID);
        throw std::invalid_argument("ftok sem returned -1");
    }
    sem_id = semget(sem_key, count_sems, IPC_CREAT | 0666);
    if (sem_id == -1) {
        shmctl(sem_id, 0, IPC_RMID);
        throw std::invalid_argument("shmget returned -1");
    }

    data = shmat(shm_id, nullptr, 0);
    if (data == nullptr) {
        throw std::invalid_argument("shmat returned nullptr");
    }

    unsigned short op[2] ={0, 1};
    set_sem_val(op);
}

ServerSharedMemory::~ServerSharedMemory() {
    shmdt(data);
    semctl(sem_id, 0, IPC_RMID, 0);
    shmctl(shm_id, 0, IPC_RMID);
}

void ServerSharedMemory::set_sem_val(unsigned short *op) const {
    union semun init = {.array = op};
    int err = semctl(sem_id, 0, SETALL, init);
    if (err == -1) {
        throw std::invalid_argument("semctl returned -1");
    }
}

void ServerSharedMemory::get_sem_val(unsigned short *res) const {
    int err = semctl(sem_id, 0, GETALL, res);
    if (err == -1) {
        throw std::invalid_argument("semctl returned -1");
    }
}

void ServerSharedMemory::change_sem_val(short *op) const {
    for (unsigned short i = 0; i < count_sems; ++i) {
        struct sembuf buf = {
                .sem_num = i,
                .sem_op = op[i],
                .sem_flg = 0
        };
        int err = semop(sem_id, &buf, 1);
        if (err == -1) {
            throw std::invalid_argument("semop returned -1");
        }
    }
}

void ServerSharedMemory::change_sem_val(short op, unsigned short num_sem) const {
    struct sembuf buf = {num_sem, op, 0};
    int err = semop(sem_id, &buf, 1);
    if (err == -1) {
        throw std::invalid_argument("semop returned -1");
    }
}

void ServerSharedMemory::send(const void *msg, size_t size_msg) {
    if(msg == nullptr) {
        throw std::invalid_argument("msg = null ptr in ServerSharedMemory::send");
    }

    short op[2];
    std::memmove(data, msg, size_msg);
    op[0] = 1;
    op[1] = 1;

    change_sem_val(op);

}

void ServerSharedMemory::rcv(void *msg, size_t size_msg) {
    if(msg == nullptr) {
        throw std::invalid_argument("msg = null ptr in ServerSharedMemory::rcv");
    }

    short op[2];
    op[0] = -1;
    op[1] = 0;


    change_sem_val(op);

    std::memmove(msg, data, size_msg);

}
