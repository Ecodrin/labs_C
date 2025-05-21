#pragma once

#include <map>
#include <thread>

#include "client_message_queue.hpp"
#include "client_shared_memory.hpp"
#include "logger.hpp"
#include "server_tcp.hpp"

class Server {
   private:
	ServerTCP server_tcp;

	std::mutex mutex;
	std::atomic<bool> stop = false;
	std::thread stop_thread;
	size_t admin_password = std::hash<std::string>{}("stop");

	// для подсервера игры
	inline static const char *server_stick_game_ftok_q_msg_input_file = "/tmp";
	inline static int server_stick_game_ftok_q_msg_input_id = 12;
	inline static const char *server_stick_game_ftok_q_msg_output_file = "/tmp";
	inline static int server_stick_game_ftok_q_msg_output_id = 13;
	// для подсервера компиляции
	inline static const char *server_compiler_ftok_shm_file = "/tmp";
	inline static int server_compiler_ftok_shm_id = 25;
	inline static const char *server_compiler_ftok_sem_file = "/tmp";
	inline static int server_compiler_ftok_sem_id = 35;

	ClientMsgQueue init_queue{server_stick_game_ftok_q_msg_input_file, server_stick_game_ftok_q_msg_input_id,
	                          server_stick_game_ftok_q_msg_output_file, server_stick_game_ftok_q_msg_output_id};
	ClientMsgQueue main_queue{server_stick_game_ftok_q_msg_input_file, server_stick_game_ftok_q_msg_input_id + 2,
	                          server_stick_game_ftok_q_msg_output_file, server_stick_game_ftok_q_msg_output_id + 2};

	struct SocketData {
		uint32_t size{};
		enum Command {
			COMPILE,
			GAME,
			COMPILING_ERROR,
			INCORRECT_PASSWORD,
			STOP_SERVER,
			SUCCESS,
			DISCONNECT,
			GAME_ERROR,
			INCORRECT_MOVE_STICKERS,
			WIN_STICKERS,
			LOSS_STICKERS
		} command{};
		size_t info{};
		char data[4096]{};
	};

	struct Info {
		inline static size_t id = 0;
		int sockfd{};
		std::thread thread{};
		bool stop = false;
	};

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

	struct DataQueueMsg {
		long mtype = 0;
		size_t move_sticks = 0;
		enum status {
			SUCCESS,
			CONNECT,
			STOP_SERVER,
			INCORRECT_PASSWORD,
			WIN,
			LOSS,
			DISCONNECT,
			INCORRECT_MOVE_STICKS,
			NEW_GAME
		} status = SUCCESS;
		size_t person_id{};
	};

	std::map<size_t, Info> data;

	void send_file(int sockfd, const std::string &filename) const;
	void get_file(const std::string &filename, int sockfd, size_t size_file) const;

   public:
	std::unique_ptr<Logger> logger;
	explicit Server(in_addr_t port);
	void client_handler(size_t id);
	void work();
	void check_stop();
	void disconnect_client(int client_sockfd, SocketData socket_data, size_t id);
	void stop_server(SocketData &socket_data, size_t password, size_t id);
	void compile(int client_sockfd, SocketData socket_data);

	void play_sticks(int sockfd, size_t id);

	~Server();
};
