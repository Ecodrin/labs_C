#pragma once

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>

#include "logger.hpp"
#include "server_message_queue.hpp"

#define N 15
#define M 3

class StickGameManager {
   private:
	std::mutex mutex;
	size_t admin_password = std::hash<std::string>{}("stop");

	ServerMsgQueue init_queue;
	ServerMsgQueue main_queue;

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

	struct Info {
		long id = 0;
		std::thread thread{};
		size_t count_sticks{};
		bool is_first_move = true;
	};
	std::map<size_t , Info> data;

   public:
	std::unique_ptr<Logger> logger;
	StickGameManager(const char *ftok_q_msg_input_file, int ftok_q_msg_input_id, const char *ftok_q_msg_output_file,
	                 int ftok_q_msg_output_id);

	void play(size_t person_id);

	void work();

	~StickGameManager();
};