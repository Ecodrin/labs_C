#pragma once

#include <map>

#include "shared_memory.hpp"
#include "safe_queue.hpp"
#include "logger.hpp"

class Server {
private:
    std::vector<pthread_t> threads;
    Logger *logger;
    SharedMemory memory;
    std::mutex mutex;
    std::string root_login = "admin";
    size_t root_password = std::hash<size_t>{}(123);


    struct ThreadData{
        Server * server;
        std::string login;
    };

    struct Session {
        size_t password;
        bool online;
        SafeQueue<std::tuple<std::string, std::time_t, std::string>> queue_msgs;
        std::map<std::string, std::vector<std::tuple<int, std::time_t, std::string>>> chats;
    };
    std::map<std::string, Session> clients;



public:
    explicit Server(const char *ftok_shm_file = "/tmp", int ftok_shm_id = 0,
           const char *ftok_sem_file = "/tmp", int ftok_sem_id=0,
           size_t shm_size=4096);

    ~Server();

    static void *processing(void *arg);

    void work();
};