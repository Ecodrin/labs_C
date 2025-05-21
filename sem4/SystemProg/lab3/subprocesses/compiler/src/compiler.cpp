#include "../include/compiler.hpp"

Compiler::Compiler(const char *ftok_shm_file, int ftok_shm_id, const char *ftok_sem_file, int ftok_sem_id)
    : server_shared_memory{ftok_shm_file, ftok_shm_id, ftok_sem_file, ftok_sem_id, sizeof(SharedMemoryData)} {
	logger = Logger::Builder()
	             .addHandler(std::make_unique<FileLoggerHandler>("logs/compiler.log"))
	             .setName("Compiler")
	             .setLevel(Logger::LOG_INFO)
	             .build();
	logger->LogInfo("server init");
}

Compiler::~Compiler() { logger->LogInfo("server stop"); }

int Compiler::compile(const std::string &filename) {
	if (filename.empty()) {
		return 1;
	}
	size_t index = filename.rfind('.');
	if (index == std::string::npos) {
		return 1;
	}

	std::string file_extension = filename.substr(index + 1);
	std::string file_name_without_extension = filename.substr(0, index);
	if (file_extension != "tex" and file_extension != "cpp") {
		return 1;
	}

	pid_t pid = fork();
	if (pid < 0) {
		return 2;
	}
	if (pid == 0) {
		if (file_extension == "tex") {
			char *cmd[] = {(char *)"./subprocesses/compiler/include/utils/compile_tex.sh", (char *)filename.c_str(),
			               (char *)file_name_without_extension.c_str(), nullptr};
			execv("./subprocesses/compiler/include/utils/compile_tex.sh", cmd);
		} else {
			char *cmd[] = {(char *)"./subprocesses/compiler/include/utils/compile_cpp.sh", (char *)filename.c_str(),
			               (char *)file_name_without_extension.c_str(), nullptr};
			execv("./subprocesses/compiler/include/utils/compile_cpp.sh", cmd);
		}

		exit(1);
	} else {
		int status = 0;
		waitpid(pid, &status, 0);
		std::cout << "Status: " << status << std::endl;
		if (status != 0) {
			return 1;
		}
	}
	return 0;
}

void Compiler::work() {
	while (true) {
		SharedMemoryData data;
		server_shared_memory.rcv(&data, sizeof(SharedMemoryData));

		if (data.status == SharedMemoryData::STOP_SERVER) {
			SharedMemoryData out_data;
			if (data.pass == admin_password) {
				out_data.status = SharedMemoryData::SUCCESS;
				server_shared_memory.send(&out_data, sizeof(SharedMemoryData));
				std::chrono::milliseconds timespan(1000);
				std::this_thread::sleep_for(timespan);
				break;
			} else {
				out_data.status = SharedMemoryData::INCORRECT_PASSWORD;
				server_shared_memory.send(&out_data, sizeof(SharedMemoryData));
				continue;
			}
		}

		SharedMemoryData output_data;
		if (compile(data.filename)) {
			logger->LogError("compilation error: " + std::string{data.filename});
			output_data.status = SharedMemoryData::COMPILATION_ERROR;
		} else {
			logger->LogInfo("compilation success: " + std::string{data.filename});
			std::string filename(data.filename);
			std::string file_name_without_extension = filename.substr(0, filename.rfind('.'));
			std::string file_extension = filename.substr(filename.rfind('.') + 1);
			output_data.status = SharedMemoryData::SUCCESS;
			if (file_extension == "tex") {
				file_name_without_extension += ".pdf";
			}
			std::memmove(output_data.filename, file_name_without_extension.c_str(), file_name_without_extension.size());
		}
		server_shared_memory.send(&output_data, sizeof(SharedMemoryData));
	}
}
