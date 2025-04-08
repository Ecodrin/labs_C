#pragma once


#include <map>
#include <iostream>

#include "logs_generator.hpp"

class LogsAnalyzer {
private:
    SafeQueue<std::string> &queue;
    static in_addr_t string_to_api(const std::string &ip_str);

    struct IPStats {
        size_t total_sent = 0;
        size_t total_received = 0;
        size_t connections = 0;
        std::map<in_addr_t, std::map<in_port_t, size_t>> connected_ips;
    };
public:
    explicit LogsAnalyzer(SafeQueue<std::string> &queue);

    static void *analyzing_traffic(void *arg) {
        auto analyzer = static_cast<LogsAnalyzer *>(arg);
        if (analyzer == nullptr) {
            return nullptr;
        }

        std::map<in_addr_t, tcp_traffic> data;

    }

};