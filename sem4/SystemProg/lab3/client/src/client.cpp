#include "../include/client.hpp"

void Client::send_file(const std::string& filename, SocketData::Command command) const {
	std::ifstream f(filename, std::ios::binary | std::ios::ate);
	if (!f) {
		logger->LogError("error in send_file");
		throw std::runtime_error("opening file failed");
	}
	size_t file_size = f.tellg();
	SocketData socket_data = {.size = htonl(sizeof(SocketData)), .command = command};
	std::memmove(socket_data.data, filename.c_str(), filename.size());
	socket_data.info = file_size;
	f.seekg(0);
	client_tcp.send_message(&socket_data);

	std::vector<char> buffer(4096);

	size_t total_sent = 0;

	while (total_sent < file_size) {
		size_t to_read = std::min(buffer.size(), file_size - total_sent);
		f.read(buffer.data(), to_read);
		client_tcp.send_all(buffer.data(), to_read);
		total_sent += to_read;
	}
}

void Client::get_file(const std::string& filename, size_t size_file) const {
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		throw std::runtime_error("can't create file");
	}
	std::vector<char> buffer(4096);

	size_t remaining = size_file;
	while (remaining > 0) {
		size_t chunk_size = std::min(buffer.size(), remaining);
		client_tcp.rcv_all(buffer.data(), chunk_size);
		file.write(buffer.data(), chunk_size);
		remaining -= chunk_size;
	}
	file.close();
}
Client::~Client() { logger->LogInfo("client stopped"); }

Client::Client(in_port_t port, const std::string& ip) : client_tcp(ip, port) {
	logger = Logger::Builder()
	             .setName("Client")
	             .setLevel(Logger::LOG_INFO)
	             .addHandler(std::make_unique<FileLoggerHandler>("logs/client.log"))
	             .build();

	logger->LogInfo("client init");
}

void Client::work() {
	SocketData socket_data = {.size = htonl(sizeof(SocketData))};

	std::string input;
	while (true) {
		if (stop) {
			break;
		}
		std::cout << "You can:\n1. Compile file(.cpp, .tex)\n2. Play stick game.\n3. exit" << std::endl;
		std::cin >> input;
		if (input == "1") {
			compile();
			logger->LogInfo("client write compile");
		} else if (input == "2") {
			try {
				play();
			} catch (ConnectError& error) {
				logger->LogError(error.what());
				std::cout << "server not available" << std::endl;
				break;
			} catch (...) {
				throw;
			}
			logger->LogInfo("client write play sticks");
		} else if (input == "3") {
			try {
				socket_data.command = SocketData::DISCONNECT;
				client_tcp.send_message(&socket_data);
				client_tcp.receive_message(&socket_data);

				break;
			} catch (ConnectError& error) {
				logger->LogError(error.what());
				std::cout << "server not available" << std::endl;
				break;
			} catch (...) {
				throw;
			}
		} else if (input == "stop_server") {
			std::cout << "Write password: ";
			std::string password;
			std::cin >> password;
			if (stop_server(std::hash<std::string>{}(password))) {
				break;
			}
			logger->LogInfo("client write stop server");

		} else {
			logger->LogInfo("user write incorrect command");
			std::cout << "Incorrect command" << std::endl;
		}

	}
}

int Client::stop_server(size_t password) {
	SocketData socket_data = {
	    .size = htonl(sizeof(SocketData)),
	    .command = SocketData::STOP_SERVER,
	    .info = password,
	};
	client_tcp.send_message(&socket_data);
	client_tcp.receive_message(&socket_data);
	std::cout << "Status: " << socket_data.command << std::endl;
	std::cout << socket_data.data << std::endl;
	if (socket_data.command == SocketData::SUCCESS) {
		return 1;
	}
	return 0;
}

void Client::compile() {
	std::string file_name;
	std::cout << "Write filename: ";
	std::cin >> file_name;
	file_name = file_name.substr(0, 4096);
	try {
		send_file(file_name, SocketData::COMPILE);
	} catch (ConnectError& error) {
		stop = true;
		logger->LogError(error.what());
		std::cout << "server not available" << std::endl;
		return;
	} catch (std::exception& exception) {
		logger->LogError(exception.what());
		std::cout << exception.what() << std::endl;
		return;
	}

	SocketData socket_data;
	try {
		client_tcp.receive_message(&socket_data);
	} catch (std::exception& exception) {
		stop = true;
		return;
	}
	if (socket_data.command == SocketData::COMPILING_ERROR) {
		std::cout << "Compile error\n";
		return;
	} else if (socket_data.command == SocketData::DISCONNECT) {
		std::cout << "disconnect\n";
		stop = true;
		return;
	} else if (socket_data.command != SocketData::SUCCESS) {
		std::cout << "error\n";
		return;
	}

	std::string output_file;
	std::string ex = file_name.substr(file_name.rfind('.') + 1);
	file_name = file_name.substr(0, file_name.rfind('.'));
	if (ex == "tex") {
		file_name += ".pdf";
	}

	try {
		get_file(file_name, socket_data.info);
	} catch (std::exception& exception) {
		logger->LogError(exception.what());
		std::cout << exception.what() << std::endl;
		return;
	}
	logger->LogInfo("get compiled file");
}
void Client::play() {
	SocketData socket_data = {
	    .size = htonl(sizeof(SocketData)),
	    .command = SocketData::GAME,
	};
	client_tcp.send_message(&socket_data);
	client_tcp.receive_message(&socket_data);
	if (socket_data.command != SocketData::SUCCESS) {
		logger->LogError("get error status: " + std::to_string(socket_data.command) + " in connect to stick game");
		if(socket_data.command == SocketData::DISCONNECT) {
			stop = true;
		}
		return;
	}
	size_t count_sticks = N;
	size_t move;
	while (true) {
		std::cout << "Now sticks: " << count_sticks << std::endl << "Write count move_sticks: ";
		std::cin >> move;
		if (move < 1 or move > M or count_sticks < move) {
			std::cout << "incorrect move" << std::endl;
			continue;
		}
		socket_data.info = move;
		client_tcp.send_message(&socket_data);
		client_tcp.receive_message(&socket_data);
		if (socket_data.command == SocketData::INCORRECT_MOVE_STICKERS) {
			std::cout << "incorrect move" << std::endl;
			continue;
		} else if (socket_data.command == SocketData::WIN_STICKERS) {
			std::cout << "WIN" << std::endl;
			return;
		} else if (socket_data.command == SocketData::LOSS_STICKERS) {
			std::cout << "LOSS" << std::endl;
			return;
		}
		count_sticks -= move;
		std::cout << "Move server: " << socket_data.info << std::endl;
		count_sticks -= socket_data.info;
	}
}
