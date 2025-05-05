//
// Created by matvey on 4/20/25.
//

#include <algorithm>
#include "../include/client.hpp"


Client::Client(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file,
               int ftok_sem_id, size_t shm_size) :
        memory{ftok_shm_file, ftok_shm_id, ftok_sem_file, ftok_sem_id, shm_size} {
    logger = Logger::Builder()
            .setName("client")
            .setLevel(Logger::LOG_INFO)
            .addHandler(std::make_unique<FileLoggerHandler>("client.log"))
            .build();
}

Client::~Client() {
    delete logger;
}

void Client::start() {

    while (true) {
        std::system("clear");
        login.clear();
        password = 0;
        chats.clear();

        SharedMemory::Msg::Type tp = sign_in_or_up();
        if (tp == SharedMemory::Msg::EXIT) {
            break;
        }
        std::pair<std::string, size_t> lp = get_login_and_password();

        password = std::hash<size_t>{}(lp.second);
        SharedMemory::Msg msg = {
                .type = tp,
                .count_pkgs=password};
        std::memmove(msg.login_sender, lp.first.c_str(), lp.first.size());
        login = lp.first;


        SharedMemory::Msg m{};
        memory.send(&msg);

        memory.rcv(&m);
        if (m.type == SharedMemory::Msg::ERROR) {
            logger->LogError("Connect: " + std::string{m.data});
            std::cout << "Connect: " + std::string{m.data} << std::endl;
            continue;
        }
        logger->LogInfo("Client + " + login + " connect.");

        SharedMemory personal_client_memory("/tmp",
                                            std::abs((int) std::hash<std::string>{}(login)),
                                            "/tmp",
                                            std::abs((int) std::hash<std::string>{}(login))
        );
        get_msgs(&personal_client_memory, m.count_pkgs);


        if (processing(&personal_client_memory)) {
            break;
        }

    }
}


int Client::processing(SharedMemory *personal_memory) {
    std::string tmp;
    while (true) {
        std::system("clear");
        std::cout << "Dialogs:\n";

        update_info(personal_memory);
        print_dialogs();
        const char *MSG1[] = {
                "1. Leave",
                "2. Dialog",
                "3. Update"
        };
        std::cout << "You can write the following command:\n";
        for (const char *el: MSG1) {
            std::cout << el << std::endl;
        }
        std::cin >> tmp;
        if (tmp == "1") {
            SharedMemory::Msg msg = {
                    .type = SharedMemory::Msg::EXIT,
                    .count_pkgs=password,
            };
            std::memmove(msg.login_sender, login.c_str(), login.size());
            personal_memory->send(&msg);
            return 0;
        } else if (tmp == "2") {
            processing_dialog(personal_memory);
        } else if (tmp == "StopServer") {
            SharedMemory::Msg msg = {
                    .type = SharedMemory::Msg::STOP_SERVER,
                    .count_pkgs=password,
            };
            std::memmove(msg.login_sender, login.c_str(), login.size());
            memory.send(&msg);
            return 1;
        }else if(tmp == "3"){
            update_info(personal_memory);
        } else {
            std::cout << "Incorrect command" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::flush(std::cout);
    }
}

void Client::processing_dialog(SharedMemory *personal_shared_memory) {
    std::string r_login;
    std::cout << "Write recipient_login: ";
    std::cin >> r_login;
    while (true) {
        update_info(personal_shared_memory);
        std::system("clear");
        print_dialog(r_login);
        std::string command;
        std::getline(std::cin, command);
        command = command.substr(0, 2048);

        if(command.empty()) {
            continue;
        }
        if(command == "update"){
            update_info(personal_shared_memory);
            continue;
        }

        if (command == "exit") {
            return;
        }
        command = command.substr(0, 2040);
        SharedMemory::Msg s{
                .type = SharedMemory::Msg::SEND,
                .count_pkgs = 1,
                .time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        };
        std::memmove(s.login_sender, login.c_str(), login.size());
        std::memmove(s.login_recipient, r_login.c_str(), r_login.size());
        std::memmove(s.data, command.c_str(), command.size());
        personal_shared_memory->send(&s);
        SharedMemory::Msg r{};
        personal_shared_memory->rcv(&r);
        if (r.type == SharedMemory::Msg::ERROR) {
            logger->LogError("Send " + std::string{r.data});
            std::cout << r.data << std::endl;
            return;
        }
        add_msg(&s, true);

    }
}


std::pair<std::string, size_t> Client::get_login_and_password() {
    std::pair<std::string, size_t> lp;
    std::cout << "Write login(max 100): ";
    while (std::cin >> lp.first and lp.first.empty()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Incorrect login." << std::endl << "Write login(max 100): ";
    }
    lp.first = lp.first.substr(0, 100);

    std::cout << "Write password: ";
    std::cin >> lp.second;
    return lp;
}

void Client::get_msgs(SharedMemory *personal_client_memory, size_t count_pkgs) {
    SharedMemory::Msg m{};
    for (size_t i = 0; i < count_pkgs; ++i) {
        SharedMemory::Msg s{.type = SharedMemory::Msg::PUT_ALL_MSGS};
        std::memmove(s.login_sender, login.c_str(), login.size());

        personal_client_memory->send(&s);


        personal_client_memory->rcv(&m);
        if (m.login_sender == login) {
            chats[m.login_recipient].emplace_back(0, m.time, m.data);
        } else if (m.login_recipient == login) {
            chats[m.login_sender].emplace_back(1, m.time, m.data);
        } else {
            logger->LogWarning("Login not in login_sender or login_recipient");
        }
    }
    logger->LogInfo("Get all msgs");
}


void Client::print_dialog(const std::string &who) {
    std::sort(chats[who].begin(), chats[who].end(), [&](
            const std::tuple<int, size_t, std::string>& a,
            const std::tuple<int, size_t, std::string>& b)->bool {
        return std::get<1>(a) < std::get<1>(b);
    });
    for (const auto &w: chats[who]) {
        if (std::get<0>(w) == 0) {
            std::cout << get_datetime(std::get<1>(w)) << " " << login << ": " << std::get<2>(w) << std::endl;
        } else {
            std::cout << get_datetime(std::get<1>(w)) << " " << who << ": " << std::get<2>(w) << std::endl;
        }
    }
}


std::string Client::get_datetime(time_t t) {
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %X");
    return ss.str();
}

SharedMemory::Msg::Type Client::sign_in_or_up() {
    std::cout << "You can\n1.sign in\n2.sign up\n3.exit" << std::endl;
    size_t d = 0;
    std::cin >> d;
    while ((d == 0 or d >= 4)) {
        std::cout << "You can\n1.sign in\n2.sign up\n3.exit" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> d;
    }
    return (SharedMemory::Msg::Type) (d - 1);
}

void Client::print_dialogs() {
    for (auto el: chats) {
        if (!el.second.empty()) {
            std::cout << el.first << " ";
            if (std::get<0>(el.second[el.second.size() - 1]) == 0) {
                std::cout << login << " ";
            } else {
                std::cout << el.first << " ";
            }
            std::cout << get_datetime(std::get<1>(el.second[el.second.size() - 1])) << " "
                      << std::get<2>(el.second[el.second.size() - 1]) << std::endl;
        }
    }
}

void Client::add_msg(SharedMemory::Msg *msg, bool you) {
    if(msg->login_sender == login) {
        chats[msg->login_recipient].emplace_back(!you, msg->time, msg->data);
    } else {
        chats[msg->login_sender].emplace_back(!you, msg->time, msg->data);
    }
}

void Client::update_info(SharedMemory *personal_shared_memory) {
    SharedMemory::Msg update_msg{
            .type=SharedMemory::Msg::GET
    };
    std::memmove(update_msg.login_sender, login.c_str(), login.size());
    SharedMemory::Msg response{};
    do {
        personal_shared_memory->send(&update_msg);
        personal_shared_memory->rcv(&response);
        if (response.count_pkgs) {
            add_msg(&response, false);
        }
    } while (response.count_pkgs);
}

