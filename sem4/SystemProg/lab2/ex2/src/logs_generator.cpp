#include "../include/logs_generator.hpp"

LogsGenerator::LogsGenerator(SafeQueue<std::string> &q, const std::string &logger_name,
                             Logger::LevelLogger logger_level)
        : queue{q} {
    logger = LoggerBuilder::build(logger_name, logger_level);
    logger->addHandler(std::make_unique<LogQueueHandler>(q));
    logger->addHandler(std::make_unique<FileLoggerHandler>("s.log"));
}

std::string LogsGenerator::ip_to_string(in_addr_t ip) {
    struct in_addr addr{};
    addr.s_addr = ip;
    return inet_ntoa(addr);
}

void *LogsGenerator::generate_sample_traffic(void *arg) {
    auto *instance = static_cast<LogsGenerator *>(arg);
    if (instance == nullptr) {
        return nullptr;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<in_addr_t> ip_dist(0x0A000001, 0x0A0000FF);
    std::uniform_int_distribution<in_port_t> port_dist(1024, 65535);
    std::uniform_int_distribution<size_t> size_dist(64, 4096);
    std::uniform_int_distribution<size_t> what_pkgs(0, 1);
    std::uniform_int_distribution<size_t> is_fatal(0, 100); // Допустим вероятность выпадения ошибки 1%
    tcp_traffic traffic{};


    traffic.src_addr = ip_dist(gen);
    traffic.pkgs_sz = 2 + gen() % 10;

    const char *what_pk[5] = {"POST ", "GET "};

    traffic.pkgs = new tcp_traffic_pkg[traffic.pkgs_sz];

   tcp_traffic_pkg tmp_pkg = {
            .src_port = port_dist(gen),
            .dst_addr = ip_dist(gen),
            .dst_port = port_dist(gen),
    };

    std::string tmp1 = ip_to_string(traffic.src_addr) + ":" +
                       std::to_string(ntohs(tmp_pkg.src_port)) + " → " +
                       ip_to_string(tmp_pkg.dst_addr) + ":" +
                       std::to_string(ntohs(tmp_pkg.dst_port));


    for (size_t i = 0; i < traffic.pkgs_sz; ++i) {
        traffic.pkgs[i] = tmp_pkg;
        traffic.pkgs[i].sz = size_dist(gen);
        if (i == 0) {
            instance->logger->LogInfo(
                    "CONNECT " +
                    tmp1
            );
        } else if (i != traffic.pkgs_sz - 1) {
            instance->logger->LogInfo(
                    what_pk[what_pkgs(gen)] +
                    tmp1 +
                    " (" + std::to_string(traffic.pkgs[i].sz) + " bytes)"
            );
        } else {
            instance->logger->LogInfo(
                    "STOP " +
                    tmp1
            );
        }
        if (is_fatal(gen) == 0) {
            instance->logger->LogError(
                    "STOP " +
                    tmp1
            );
            break;
        }
    }
    delete traffic.pkgs;
    return nullptr;
}

void LogsGenerator::start_traffic(size_t count_threads) {
    pthread_t threads[count_threads];
    for (int i = 0; i < count_threads; ++i) {
        pthread_create(&threads[i], nullptr, &LogsGenerator::generate_sample_traffic, this);
    }

    for (int i = 0; i < count_threads; ++i) {
        pthread_join(threads[i], nullptr);
    }
}

void LogQueueHandler::write(const std::string &str) {
    queue.push(str);
}
