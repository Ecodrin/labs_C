#include "../include/server.hpp"

Server::Server(size_t count_threads, const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file,
               int ftok_sem_id,size_t shm_size) :
               memory{ftok_shm_file, ftok_shm_id, ftok_sem_file, ftok_sem_id, shm_size},
               count_thread{count_threads}{}
