#include "../include/client_message_queue.hpp"

ClientMsgQueue::ClientMsgQueue(const char *ftok_q_msg_input_file, int ftok_q_msg_input_id,
                               const char *ftok_q_msg_output_file, int ftok_q_msg_output_id) {
	key_t q_msg_input_key = ftok(ftok_q_msg_input_file, ftok_q_msg_input_id);
	if (q_msg_input_key == -1) {
		throw std::invalid_argument("ftok shared memory returned -1");
	}
	msg_id_input = msgget(q_msg_input_key, 0666);
	if (msg_id_input == -1) {
		throw std::invalid_argument("msgget returned -1");
	}

	key_t q_msg_output_key = ftok(ftok_q_msg_output_file, ftok_q_msg_output_id);
	if (q_msg_output_key == -1) {
		throw std::invalid_argument("ftok shared memory returned -1");
	}
	msg_id_output = msgget(q_msg_output_key, 0666);
	if (msg_id_output == -1) {
		throw std::invalid_argument("msgget returned -1");
	}
}

void ClientMsgQueue::rcv(void *msg, size_t size_msg, long id) const {
	if (msg == nullptr) {
		throw std::invalid_argument("msg = null ptr in ClientMsgQueue::rcv");
	}

	if (msgrcv(msg_id_output, msg, size_msg - sizeof(long), id, 0) == -1) {
		throw std::runtime_error("msgrcv in ClientMsgQueue");
	}
}

void ClientMsgQueue::send(void *msg, size_t size_msg) const {
	if (msg == nullptr) {
		throw std::invalid_argument("msg = null ptr in ClientMsgQueue::send");
	}
	if (msgsnd(msg_id_input, msg, size_msg - sizeof(long), 0)) {
		throw std::runtime_error("msgsnd in ClientMsgQueue");
	}
}
