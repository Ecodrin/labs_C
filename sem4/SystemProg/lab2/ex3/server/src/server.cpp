#include "../include/server.hpp"

Server::Server(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file,
               int ftok_sem_id,size_t shm_size) :
        memory{ftok_shm_file, ftok_shm_id, ftok_sem_file, ftok_sem_id, shm_size} {

    logger = Logger::Builder()
            .setName("Server")
            .setLevel(Logger::LOG_INFO)
            .addHandler(std::make_unique<FileLoggerHandler>("server.log"))
            .addHandler(std::make_unique<StreamLoggerHandler>(std::cout))
            .build();

    clients[root_login].password = root_password;
    logger->LogInfo("Initial server");
}

Server::~Server() {
    for (auto &el: threads) {
        pthread_join(el, nullptr);
    }
    delete logger;
}

void Server::work() {
    logger->LogInfo("Start server");
    unsigned short op1[] = {0, 1};
    memory.set_sem_val(op1);
    while (true) {
        SharedMemory::Msg msg{};
        SharedMemory::Msg answer{};

        memory.rcv(&msg);

        switch (msg.type) {
            case SharedMemory::Msg::STOP_SERVER: {
                std::unique_lock<std::mutex> lock(mutex);
                if (strcmp(msg.login_sender, root_login.c_str()) == 0 or msg.count_pkgs == root_password) {
                    lock.unlock();
                    logger->LogInfo("Server stop");
                    return;
                }
                lock.unlock();
                break;
            }
            case SharedMemory::Msg::REGISTER: {
                std::unique_lock<std::mutex> lock(mutex);
                if (clients.find(msg.login_sender) != clients.end()) {
                    char s[] = "this login already exist";
                    std::memmove(answer.data, s, sizeof(s));
                    answer.type = SharedMemory::Msg::ERROR;
                    break;
                }
                clients[msg.login_sender].password = msg.count_pkgs;
                lock.unlock();
                msg.type = SharedMemory::Msg::CONNECT;
                logger->LogInfo("Client " + std::string{msg.login_sender} + " register");
            }
            case SharedMemory::Msg::CONNECT: {
                std::unique_lock<std::mutex> lock(mutex);
                if (clients.find(msg.login_sender) == clients.end() or
                    clients[msg.login_sender].password != msg.count_pkgs or
                    clients[msg.login_sender].online
                        ) {
                    char s[] = "incorrect login or password";
                    std::memmove(answer.data, s, sizeof(s));
                    answer.type = SharedMemory::Msg::ERROR;
                    break;
                }
                lock.unlock();
            }
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    clients[msg.login_sender].online = true;
                    threads.push_back({});
                    auto *data_thread = new ThreadData{this, msg.login_sender};
                    pthread_create(&threads[threads.size() - 1], nullptr, processing, (void *) data_thread);
                    lock.unlock();
                }

                logger->LogInfo("Client " + std::string{msg.login_sender} + " connect");

                {
                    char s[] = "Sign in successful";
                    std::memmove(answer.data, s, sizeof(s));
                    answer.type = SharedMemory::Msg::CONNECT;
                    size_t count_pkgs = 0;
                    for (const auto &el: clients[msg.login_sender].chats) {
                        count_pkgs += el.second.size();
                    }
//                    std::cout << msg.login_sender << " " << clients[msg.login_sender].chats.size() << std::endl;
                    answer.count_pkgs = count_pkgs;
                }
                break;
            default:
                logger->LogWarning("Unrecognized command or incorrect command");
                char s[] = "Unrecognized command or incorrect command";
                std::memmove(answer.data, s, sizeof(s));
                answer.type = SharedMemory::Msg::ERROR;
        }

        memory.send(&answer);
    }
}

void *Server::processing(void *arg) {
    auto *data = static_cast<ThreadData *>(arg);
    if (data == nullptr) {
        return nullptr;
    }

    auto &session = data->server->clients[data->login];
    auto &mutex = data->server->mutex;
    auto &clients = data->server->clients;
    SharedMemory personal_client_memory("/tmp",
                                        std::abs((int) std::hash<std::string>{}(data->login)),
                                        "/tmp",
                                        std::abs((int) std::hash<std::string>{}(data->login))
    );


    unsigned short op1[] = {0, 1};
    personal_client_memory.set_sem_val(op1);


    SharedMemory::Msg get{}, send{};
    {
        std::unique_lock<std::mutex> lock(mutex);

        // отправляем все сообщения
        for (const auto &chat: clients[data->login].chats) {
            for (const std::tuple<int, time_t, std::string> &msg: chat.second) {
                std::memset(&get, 0, sizeof(SharedMemory::Msg));
                std::memset(&send, 0, sizeof(SharedMemory::Msg));
                personal_client_memory.rcv(&get);
                send.count_pkgs = SharedMemory::Msg::PUT_ALL_MSGS;
                std::memmove(send.data, std::get<2>(msg).c_str(), std::get<2>(msg).size());
                if (std::get<0>(msg) == 0) {
                    std::memmove(send.login_sender, data->login.c_str(), data->login.size());
                    std::memmove(send.login_recipient, chat.first.c_str(), chat.first.size());
                } else {
                    std::memmove(send.login_recipient, data->login.c_str(), data->login.size());
                    std::memmove(send.login_sender, chat.first.c_str(), chat.first.size());
                }
                send.time = std::get<1>(msg);
                personal_client_memory.send(&send);
            }
        }
        lock.unlock();
    }

    while (true) {
        personal_client_memory.rcv(&get);
        std::memset(&send, 0, sizeof(SharedMemory::Msg));
        switch (get.type) {
            case SharedMemory::Msg::EXIT: {
                std::unique_lock<std::mutex> lock(mutex);
                data->server->logger->LogInfo("Client " + data->login + " exit");
                data->server->clients[data->login].online = false;
                free(arg);
                personal_client_memory.send(&send);
                lock.unlock();
                return nullptr;
            }
            case SharedMemory::Msg::SEND: {
                std::unique_lock<std::mutex> lock(mutex);
                if(clients.find(get.login_recipient) == clients.end()) {
                    char s[] = "login_recipient doesn't exist";
                    std::memmove(send.data, s, sizeof(s));
                    send.type = SharedMemory::Msg::ERROR;
                    personal_client_memory.send(&send);
                    break;
                }
                clients[get.login_recipient].chats[get.login_sender].emplace_back(1, get.time, get.data);
                if(strcmp(get.login_sender, get.login_recipient) != 0) {
                    session.chats[get.login_recipient].emplace_back(0, get.time, get.data);
                    if (clients[get.login_recipient].online) {
                        clients[get.login_recipient].queue_msgs.push({get.login_sender, get.time, get.data});
                    }
                }
                personal_client_memory.send(&send);
                break;
            }
            case SharedMemory::Msg::GET: {
                std::unique_lock<std::mutex> lock(mutex);
                std::tuple<std::string, time_t, std::string> waiting_msg;
                if (!session.queue_msgs.empty()) {
                    send.count_pkgs = 1;
                    waiting_msg = session.queue_msgs.pop();
                } else {
                    send.count_pkgs = 0;
                    personal_client_memory.send(&send);
                    lock.unlock();
                    break;
                }

                send.type = SharedMemory::Msg::GET;
                std::memmove(send.data, std::get<2>(waiting_msg).c_str(), std::get<2>(waiting_msg).size());
                std::memmove(send.login_sender, std::get<0>(waiting_msg).c_str(), std::get<0>(waiting_msg).size());
                std::memmove(send.login_recipient, data->login.c_str(), data->login.size());

                send.time = std::get<1>(waiting_msg);
                personal_client_memory.send(&send);

                lock.unlock();
                break;
            }
            default:
                break;
        }
    }
}
