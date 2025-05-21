#include "../include/sticks_game.hpp"

StickGameManager::StickGameManager(const char *ftok_q_msg_input_file, int ftok_q_msg_input_id,
                                   const char *ftok_q_msg_output_file, int ftok_q_msg_output_id)
    : init_queue{ftok_q_msg_input_file, ftok_q_msg_input_id, ftok_q_msg_output_file, ftok_q_msg_output_id},
      main_queue{ftok_q_msg_input_file, ftok_q_msg_input_id + 2, ftok_q_msg_output_file, ftok_q_msg_output_id + 2} {
	logger = Logger::Builder()
	             .setName("StickGameManager")
	             .addHandler(std::make_unique<FileLoggerHandler>("logs/stick_game_manager.log"))
	             .setLevel(Logger::LOG_INFO)
	             .build();
	logger->LogInfo("stick game server init");
}

StickGameManager::~StickGameManager() {
	logger->LogInfo("stick game server stop");
	for (auto &el : data) {
		if (el.second.thread.joinable()) {
			el.second.thread.join();
		}
	}
}

void StickGameManager::work() {
	DataQueueMsg input_msg, output_msg;
	while (true) {
		init_queue.rcv(&input_msg, sizeof(DataQueueMsg), 0);
		if (input_msg.status == DataQueueMsg::STOP_SERVER) {
			if (input_msg.move_sticks == admin_password) {
				output_msg.mtype = input_msg.mtype;
				output_msg.status = DataQueueMsg::SUCCESS;
				init_queue.send(&output_msg, sizeof(DataQueueMsg));
				std::chrono::milliseconds timespan(10000);
				std::this_thread::sleep_for(timespan);
				break;
			} else {
				output_msg.mtype = input_msg.mtype;
				output_msg.status = DataQueueMsg::INCORRECT_PASSWORD;
				init_queue.send(&output_msg, sizeof(DataQueueMsg));
				logger->LogInfo("user: " + std::to_string(input_msg.person_id) + " tried to stop server");
				continue;
			}
		}
		if (input_msg.status == DataQueueMsg::CONNECT) {
			std::lock_guard<std::mutex> lock(mutex);
			logger->LogInfo("user: " + std::to_string(input_msg.person_id) + " connected");
			size_t copy_person_id = input_msg.person_id;
			data[copy_person_id] = {.id = input_msg.mtype,
			                    .thread = std::thread([this, copy_person_id]() { play(copy_person_id); }),
			                    .count_sticks = N,
			                    .is_first_move = true};
			output_msg.status = DataQueueMsg::SUCCESS;
		} else if (input_msg.status == DataQueueMsg::DISCONNECT) {
			{
				std::lock_guard<std::mutex> lock(mutex);
				data[input_msg.person_id].thread.join();
				data.erase(input_msg.person_id);
				output_msg.status = DataQueueMsg::SUCCESS;
			}
			logger->LogInfo("user: " + std::to_string(input_msg.person_id) + " disconnected");
		} else if (input_msg.status == DataQueueMsg::NEW_GAME) {
			std::lock_guard<std::mutex> lock(mutex);
			logger->LogInfo("user: " + std::to_string(input_msg.person_id) + " started new game");
			size_t copy_person_id = input_msg.person_id;
			if(data[copy_person_id].thread.joinable()) {
				data[copy_person_id].thread.join();
			}
			data[copy_person_id] = {.id = input_msg.mtype,
			                    .thread = std::thread([this, copy_person_id]() { play(copy_person_id); }),
			                    .count_sticks = N,
			                    .is_first_move = true};
		} else {
			logger->LogWarning("user:" + std::to_string(input_msg.person_id) + " send incorrect command");
		}
		output_msg.mtype = input_msg.mtype;
		output_msg.person_id = input_msg.person_id;
		init_queue.send(&output_msg, sizeof(DataQueueMsg));
	}
}

void StickGameManager::play(size_t person_id) {
	size_t id;
	{
		std::lock_guard<std::mutex> lock(mutex);
		auto &user = data[person_id];
		id = user.id;
		user.count_sticks = N;
	}
	DataQueueMsg input_msg, output_msg = {.mtype = (long)id};
	while (true) {
		main_queue.rcv(&input_msg, sizeof(DataQueueMsg), (long)id);

		{
			std::lock_guard<std::mutex> lock(mutex);
			auto &user = data[person_id];

			if (input_msg.move_sticks < 1 || input_msg.move_sticks > M or input_msg.move_sticks > user.count_sticks) {
				output_msg.status = DataQueueMsg::INCORRECT_MOVE_STICKS;
				output_msg.move_sticks = 0;
				main_queue.send(&output_msg, sizeof(DataQueueMsg));
				continue;
			}

			user.count_sticks -= input_msg.move_sticks;

			if (user.count_sticks == 0) {
				output_msg.status = DataQueueMsg::WIN;
				output_msg.move_sticks = 0;
				main_queue.send(&output_msg, sizeof(DataQueueMsg));
				break;
			} else {
				size_t server_move;
				if (user.is_first_move) {
					// Оптимальный первый ход для N=15, M=3: 15 -> 13
					server_move = (N - 1) % (M + 1);
					server_move = (server_move == 0) ? M : server_move;
					server_move = std::min(server_move, user.count_sticks);
					user.is_first_move = false;
				} else {
					// Последующие ходы: M+1 - ход игрока
					server_move = (M + 1) - input_msg.move_sticks;
					server_move = std::min(server_move, user.count_sticks);
				}

				user.count_sticks -= server_move;
				output_msg.move_sticks = server_move;

				if (user.count_sticks == 0) {
					output_msg.status = DataQueueMsg::LOSS;
					main_queue.send(&output_msg, sizeof(DataQueueMsg));
					break;
				} else {
					output_msg.status = DataQueueMsg::SUCCESS;
				}
			}
		}
		output_msg.person_id = person_id;
		main_queue.send(&output_msg, sizeof(DataQueueMsg));
	}
}
