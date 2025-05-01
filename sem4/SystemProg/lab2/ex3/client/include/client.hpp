
#pragma once

#include <chrono>
#include <map>

#include "shared_memory.hpp"
#include "logger.hpp"


class Client {
private:
    std::string login;
    Logger * logger;
    size_t password;
    std::map<std::string, std::vector<std::tuple<int, std::time_t, std::string>>> chats;
    SharedMemory memory;


    void add_msg(SharedMemory::Msg * msg, bool you);
    void update_info(SharedMemory * personal_shared_memory);

public:
    explicit Client(const char *ftok_shm_file = "/tmp", int ftok_shm_id = 0,
                    const char *ftok_sem_file = "/tmp", int ftok_sem_id=0,
                    size_t shm_size=4096);

    void start();

    static std::pair<std::string, size_t> get_login_and_password();
    void get_msgs(SharedMemory * personal_client_memory, size_t count_pkgs);
    void print_dialog(const std::string &who);
    void print_dialogs();
    static std::string get_datetime(time_t t);
    static SharedMemory::Msg::Type sign_in_or_up();

    int processing(SharedMemory * personal_memory);
    void processing_dialog(SharedMemory * personal_shared_memory);


    ~Client();
};