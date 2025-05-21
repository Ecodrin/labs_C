#include "../include/server_message_queue.hpp"

ServerMsgQueue::ServerMsgQueue(const char *ftok_q_msg_input_file, int ftok_q_msg_input_id,
                               const char *ftok_q_msg_output_file, int ftok_q_msg_output_id) {
	key_t q_msg_input_key = ftok(ftok_q_msg_input_file, ftok_q_msg_input_id);
	if (q_msg_input_key == -1) {
		throw std::invalid_argument("ftok shared memory returned -1");
	}
	msg_id_input = msgget(q_msg_input_key, IPC_CREAT | 0666);
	if (msg_id_input == -1) {
		throw std::invalid_argument("shmget returned -1");
	}

	key_t q_msg_output_key = ftok(ftok_q_msg_output_file, ftok_q_msg_output_id);
	if (q_msg_output_key == -1) {
		throw std::invalid_argument("ftok shared memory returned -1");
	}
	msg_id_output = msgget(q_msg_output_key, IPC_CREAT | 0666);
	if (msg_id_output == -1) {
		msgctl(msg_id_input, IPC_RMID, nullptr);
		throw std::invalid_argument("shmget returned -1");
	}
}

ServerMsgQueue::~ServerMsgQueue() {
	msgctl(msg_id_input, IPC_RMID, nullptr);
	msgctl(msg_id_output, IPC_RMID, nullptr);
}

void ServerMsgQueue::rcv(void *msg, size_t size_msg, long id) const {
	if (msg == nullptr) {
		throw std::invalid_argument("msg = nullptr in ServerMsgQueue::rcv");
	}

	if (msgrcv(msg_id_input, msg, size_msg - sizeof(long), id, 0) == -1) {
		throw std::runtime_error("msgrcv in ServerMsgQueue");
	}
}

void ServerMsgQueue::send(void *msg, size_t size_msg) const {
	if (msg == nullptr) {
		throw std::invalid_argument("msg = nullptr in ServerMsgQueue::send");
	}
	if (msgsnd(msg_id_output, msg, size_msg - sizeof(long), 0)) {
		throw std::runtime_error("msgsnd in ServerMsgQueue");
	}
}
