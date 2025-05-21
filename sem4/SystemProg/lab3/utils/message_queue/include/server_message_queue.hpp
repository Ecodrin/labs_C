#pragma once

#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <iostream>


class ServerMsgQueue {
   private:
	int msg_id_input;
	int msg_id_output;

   public:
	ServerMsgQueue(const char *ftok_q_msg_input_file, int ftok_q_msg_input_id, const char *ftok_q_msg_output_file,
	               int ftok_q_msg_output_id);

	void rcv(void *msg, size_t size_msg, long id) const;
	void send(void *msg, size_t size_msg) const;
	~ServerMsgQueue();
};