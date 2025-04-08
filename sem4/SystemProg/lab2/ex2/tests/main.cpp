#include "../include/logs_generator.hpp"
#include "../include/logs_analyzer.hpp"
#include "../include/logger.hpp"
#include "../include/safe_queue.hpp"


int main() {
    SafeQueue<std::string> q;
    LogsGenerator a{q, "Traffic", Logger::LOG_DEBUG};
    a.start_traffic(3);



}
