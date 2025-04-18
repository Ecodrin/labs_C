#include <utility>

#include "../include/logger.hpp"


std::string Logger::get_datetime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm timeBuf{};

    localtime_r(&time, &timeBuf);

    std::ostringstream timeStream;
    timeStream << std::put_time(&timeBuf, "%Y-%m-%d %H:%M:%S");
    std::string timeStr = timeStream.str();
    return timeStr;
}

void Logger::Log(Logger::LevelLogger level, const std::string &log) {
    if(level > log_level) return;

    const char* level_str[] = {
            "[CRITICAL]", "[ERROR]", "[WARNING]", "[INFO]", "[DEBUG]"
    };

    std::string log_msg = "[" + get_datetime() + "][" + logger_name + "]"
                          + level_str[level] + " " + log;
    std::lock_guard<std::mutex> lock(mutex);
    for(auto& handler : handlers) {
        handler->write(log_msg);
    }
}

void Logger::LogError(const std::string &log) {
    Log(LOG_ERROR, log);
}

void Logger::LogCritic(const std::string &log) {
    Log(LOG_CRITICAL, log);
}

void Logger::LogWarning(const std::string &log) {
    Log(LOG_WARNING, log);
}

void Logger::LogInfo(const std::string &log) {
    Log(LOG_INFO, log);
}

void Logger::LogDebug(const std::string &log) {
    Log(LOG_DEBUG, log);
}

void Logger::addHandler(std::unique_ptr<LogHandler> handler) {
    handlers.push_back(std::move(handler));
}

void Logger::setHandler(Logger::LevelLogger level) {
    log_level = level;
}

Logger::Logger(std::string logger_n, Logger::LevelLogger logger_level) : logger_name(std::move(logger_n)),
                                                                                log_level(logger_level) {

}

void Logger::close_logger() {
    handlers.clear();

}

StreamLoggerHandler::StreamLoggerHandler(std::ostream &stream) : stream_{stream} {}

void StreamLoggerHandler::write(const std::string &message) {
    stream_ << message << std::endl;
}


Logger *LoggerBuilder::build(const std::string &logger_name, Logger::LevelLogger logger_level) {
    return new Logger{logger_name, logger_level};
}

void FileLoggerHandler::write(const std::string &message) {
    out << message << std::endl;
}

FileLoggerHandler::FileLoggerHandler(const std::string &filename) : out(filename, std::ios::app) {
}

FileLoggerHandler::~FileLoggerHandler() {
    out.close();
}
