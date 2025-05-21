#pragma once

#include <sys/wait.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "logger.hpp"
#include "server_shared_memory.hpp"

class Compiler {
   private:
	size_t admin_password = std::hash<std::string>{}("stop");
	ServerSharedMemory server_shared_memory;

	struct SharedMemoryData {
		size_t pass{};
		char filename[4096]{};

		enum Status {
			SUCCESS,
			COMPILATION_ERROR,
			INCORRECT_PASSWORD,
			STOP_SERVER,
		} status = SUCCESS;
	};

   public:
	std::unique_ptr<Logger> logger;

	Compiler(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file, int ftok_sem_id);

	static int compile(const std::string &filename);

	void work();

	~Compiler();
};