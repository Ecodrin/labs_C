#include "../include/logs_analyzer.hpp"

LogsAnalyzer::LogsAnalyzer(SafeQueue<std::string> &queue) : queue(queue) {

}

in_addr_t LogsAnalyzer::string_to_api(const std::string &ip_str) {
    struct in_addr addr{};
    int result = inet_pton(AF_INET, ip_str.c_str(), &addr);
    if (result == 0) {
        throw std::invalid_argument("Invalid IPv4 address format: " + ip_str);
    } else if (result < 0) {
        throw std::runtime_error("Error in IP address conversion");
    }
    return addr.s_addr;
}
