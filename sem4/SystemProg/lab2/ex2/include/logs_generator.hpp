#pragma once

#include <iostream>

#include "logger.hpp"
#include "safe_queue.hpp"


#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <random>


struct tcp_traffic_pkg {
    in_port_t src_port;
    in_addr_t dst_addr;
    in_port_t dst_port;
    size_t sz;
};

struct tcp_traffic {
    in_addr_t src_addr;
    struct tcp_traffic_pkg *pkgs;
    size_t pkgs_sz;
};


class LogQueueHandler : public LogHandler {
protected:
    SafeQueue<std::string> &queue;
public:
    explicit LogQueueHandler(SafeQueue<std::string> &q) : queue(q) {};
    void write(const std::string &str) override;
};

class LogsGenerator {
private:
    Logger *logger;
    SafeQueue<std::string> &queue;

    static std::string ip_to_string(in_addr_t ip);

public:
    explicit LogsGenerator(SafeQueue<std::string> &q, const std::string &logger_name,
                           Logger::LevelLogger logger_level);

    static void* generate_sample_traffic(void * arg);

    void start_traffic(size_t count_threads = 3);
};