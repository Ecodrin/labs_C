#include "../include/logs_generator.hpp"
#include "../include/logger.hpp"

int main() {
    Logger* l = LoggerBuilder::build("asdas");
    l->addHandler(std::make_unique<FileLoggerHandler>("asd.log"));
    l->LogWarning("govno");
}