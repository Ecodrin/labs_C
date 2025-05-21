#include "../include/server.hpp"

Server::~Server() {
	std::cout << "server destructor\n";
	for (auto &el : data) {
		if (el.second.thread.joinable()) {
			el.second.thread.join();
		}
	}
	stop_thread.join();
	logger->LogInfo("main server stopped");
}

Server::Server(in_addr_t port) : server_tcp(port) {
	std::lock_guard<std::mutex> lock(mutex);
	logger = Logger::Builder()
	             .setName("MainServer")
	             .setLevel(Logger::LOG_INFO)
	             .addHandler(std::make_unique<FileLoggerHandler>("logs/main_server.log"))
	             .build();

	logger->LogInfo("main server init");

	stop_thread = std::thread([this]() { check_stop(); });
}

void Server::work() {
	while (!stop.load(std::memory_order_acquire)) {
		int client_sockfd = server_tcp.accept_connection();
		if (client_sockfd < 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			continue;
		}
		if (stop.load(std::memory_order_acquire)) {
			break;
		}
		{
			std::lock_guard<std::mutex> lock(mutex);
			Info::id += 1;
			logger->LogInfo("client " + std::to_string(Info::id) + " connected");
			data[Info::id] = {.sockfd = client_sockfd,
			                  .thread = std::thread([this, id = Info::id]() { client_handler(id); })};
		}
	}
	logger->LogDebug("work break");
}
void Server::get_file(const std::string &filename, int sockfd, size_t size_file) const {
	std::ofstream file(filename, std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("can't create file");
	}
	std::vector<char> buffer(4096);

	size_t remaining = size_file;
	while (remaining > 0) {
		size_t chunk_size = std::min(buffer.size(), remaining);
		ServerTCP::rcv_all(sockfd, buffer.data(), chunk_size);
		file.write(buffer.data(), chunk_size);
		remaining -= chunk_size;
	}
}

void Server::send_file(int sockfd, const std::string &filename) const {
	std::ifstream f(filename, std::ios::binary | std::ios::ate);
	if (!f) {
		logger->LogError("error in send_file");
		throw std::runtime_error("opening file failed");
	}
	size_t file_size = f.tellg();
	SocketData socket_data = {.size = htonl(sizeof(SocketData))};
	std::memmove(socket_data.data, filename.c_str(), filename.size());
	socket_data.info = file_size;
	f.seekg(0);
	socket_data.command = SocketData::SUCCESS;
	ServerTCP::send_message(sockfd, &socket_data);

	std::vector<char> buffer(4096);

	size_t total_sent = 0;

	while (total_sent < file_size) {
		size_t to_read = std::min(buffer.size(), file_size - total_sent);
		f.read(buffer.data(), to_read);
		ServerTCP::send_all(sockfd, buffer.data(), to_read);
		total_sent += to_read;
	}
}

void Server::client_handler(size_t id) {
	int client_sockfd;
	{
		std::lock_guard<std::mutex> lock(mutex);
		client_sockfd = data[id].sockfd;
	}
	SocketData socket_data;
	while (true) {
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (stop) {
				SocketData tmp = {
				    .size = htonl(sizeof(SocketData)),
				    .command = SocketData::DISCONNECT,
				};
				disconnect_client(client_sockfd, tmp, id);
				break;
			}
		}
		try {
			ServerTCP::receive_message(client_sockfd, &socket_data);
		} catch (ConnectError &error) {
			logger->LogError(std::to_string(id) + " " + error.what());
			{
				std::lock_guard<std::mutex> lock(mutex);
				data[id].stop = true;
			}
			break;
		} catch (...) {
			throw;
		}
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (stop) {
				SocketData tmp = {
				    .size = htonl(sizeof(SocketData)),
				    .command = SocketData::DISCONNECT,
				};
				disconnect_client(client_sockfd, tmp, id);
				break;
			}
		}
		if (socket_data.command == SocketData::STOP_SERVER) {
			stop_server(socket_data, socket_data.info, id);
			{
				std::lock_guard<std::mutex> lock(mutex);
				if(socket_data.command != SocketData::INCORRECT_PASSWORD) {
					logger->LogInfo("client " + std::to_string(id) + " stopped server");
					disconnect_client(client_sockfd, socket_data, id);
					break;
				} else {
					ServerTCP::send_message(client_sockfd, &socket_data);
				}
			}
		} else if (socket_data.command == SocketData::DISCONNECT) {
			{
				std::lock_guard<std::mutex> lock(mutex);
				disconnect_client(client_sockfd, socket_data, id);
			}
			break;
		} else if (socket_data.command == SocketData::COMPILE) {
			compile(client_sockfd, socket_data);
		} else if (socket_data.command == SocketData::GAME) {
			play_sticks(client_sockfd, id);
		}
	}
}

void Server::check_stop() {
	while (!stop) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		{
			std::lock_guard<std::mutex> lock(mutex);
			for (auto it = data.begin(); it != data.end();) {
				if ((*it).second.stop) {
					if ((*it).second.thread.joinable()) {
						(*it).second.thread.join();
					}
					logger->LogInfo("map: " + std::to_string((*it).first) + " clear");
					it = data.erase(it);
				} else {
					++it;
				}
			}
		}
	}
}

void Server::stop_server(Server::SocketData &socket_data, size_t password, size_t id) {
	socket_data.size = htonl(sizeof(Server::SocketData));
	if (password != admin_password) {
		socket_data.command = SocketData::INCORRECT_PASSWORD;
		std::string s = "incorrect password";
		std::memmove(socket_data.data, s.c_str(), s.size());
		return;
	} else {
		socket_data.command = SocketData::SUCCESS;
	}

	ClientSharedMemory client_shared_memory{server_compiler_ftok_shm_file, server_compiler_ftok_shm_id,
	                                        server_compiler_ftok_sem_file, server_compiler_ftok_sem_id};

	SharedMemoryData shared_memory_data = {.pass = admin_password, .status = SharedMemoryData::STOP_SERVER};

	client_shared_memory.send(&shared_memory_data, sizeof(SharedMemoryData));
	client_shared_memory.rcv(&shared_memory_data, sizeof(SharedMemoryData));

	DataQueueMsg queue_memory_data = {
	    .mtype = (long)id, .move_sticks = password, .status = DataQueueMsg::STOP_SERVER, .person_id = id};
	init_queue.send(&queue_memory_data, sizeof(DataQueueMsg));
	init_queue.rcv(&queue_memory_data, sizeof(DataQueueMsg), id);

	{
		std::lock_guard<std::mutex> lock(mutex);
		stop = true;
	}
}

void Server::compile(int client_sockfd, Server::SocketData socket_data) {
	try {
		ClientSharedMemory client_shared_memory{server_compiler_ftok_shm_file, server_compiler_ftok_shm_id,
		                                        server_compiler_ftok_sem_file, server_compiler_ftok_sem_id};

		SharedMemoryData shared_memory_data;
		std::string filename(socket_data.data);

		std::string base_filename = filename.substr(filename.find_last_of("/\\") + 1);

		get_file(base_filename, client_sockfd, socket_data.info);

		std::memmove(shared_memory_data.filename, base_filename.c_str(), base_filename.size());
		client_shared_memory.send(&shared_memory_data, sizeof(SharedMemoryData));

		client_shared_memory.rcv(&shared_memory_data, sizeof(SharedMemoryData));

		if (shared_memory_data.status) {
			socket_data.command = SocketData::COMPILING_ERROR;
			socket_data.size = htonl(sizeof(SocketData));
			remove(base_filename.c_str());
			ServerTCP::send_message(client_sockfd, &socket_data);
		} else {
			send_file(client_sockfd, shared_memory_data.filename);
			remove(base_filename.c_str());
			remove(shared_memory_data.filename);
			logger->LogInfo("file " + std::string{shared_memory_data.filename} + " compiled");
		}
	} catch (std::exception &exception) {
		logger->LogError(exception.what());
	}
}

void Server::disconnect_client(int client_sockfd, Server::SocketData socket_data, size_t id) {

	socket_data.size = htonl(sizeof(SocketData));
	ServerTCP::send_message(client_sockfd, &socket_data);

	if (socket_data.command != SocketData::INCORRECT_PASSWORD) {
		close(client_sockfd);
	}
	if (socket_data.command != SocketData::INCORRECT_PASSWORD) {
		logger->LogInfo("client " + std::to_string(id) + " disconnected");
		data[id].stop = true;
	}

}

void Server::play_sticks(int sockfd, size_t id) {
	if (stop) {
		return;
	}
	DataQueueMsg data_queue_msg = {.mtype = (long)id, .status = DataQueueMsg::CONNECT, .person_id = id};
	init_queue.send(&data_queue_msg, sizeof(data_queue_msg));
	init_queue.rcv(&data_queue_msg, sizeof(DataQueueMsg), (long)id);
	SocketData socket_data = {
	    .size = htonl(sizeof(SocketData)),
	};
	if (data_queue_msg.status == DataQueueMsg::SUCCESS) {
		socket_data.command = SocketData::SUCCESS;
		ServerTCP::send_message(sockfd, &socket_data);
	} else {
		socket_data.command = SocketData::GAME_ERROR;
		ServerTCP::send_message(sockfd, &socket_data);
		return;
	}
	logger->LogInfo("id: " + std::to_string(id) + " started game");
	while (true) {
		std::cout << stop << "  " << id << std::endl;
		ServerTCP::receive_message(sockfd, &socket_data);

		data_queue_msg.move_sticks = socket_data.info;
		main_queue.send(&data_queue_msg, sizeof(DataQueueMsg));
		main_queue.rcv(&data_queue_msg, sizeof(DataQueueMsg), (long)id);

		switch (data_queue_msg.status) {
			case DataQueueMsg::INCORRECT_MOVE_STICKS:
				socket_data.command = SocketData::INCORRECT_MOVE_STICKERS;
				break;
			case DataQueueMsg::WIN:
				socket_data.command = SocketData::WIN_STICKERS;
				break;
			case DataQueueMsg::LOSS:
				socket_data.command = SocketData::LOSS_STICKERS;
				break;
			case DataQueueMsg::SUCCESS:
				socket_data.command = SocketData::SUCCESS;
				socket_data.info = data_queue_msg.move_sticks;
				break;
			default:
				break;
		}
		ServerTCP::send_message(sockfd, &socket_data);
		if (socket_data.command == SocketData::WIN_STICKERS or socket_data.command == SocketData::LOSS_STICKERS) {
			break;
		}
	}
	if (!stop) {
		data_queue_msg.status = DataQueueMsg::DISCONNECT;
		init_queue.send(&data_queue_msg, sizeof(DataQueueMsg));
		init_queue.rcv(&data_queue_msg, sizeof(DataQueueMsg), (long)id);
	}
}
