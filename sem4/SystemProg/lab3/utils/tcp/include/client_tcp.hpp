#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <cstring>
#include <functional>
#include <memory>

#include "custom_exceptions.hpp"
#include "logger.hpp"

class ClientTCP {
   private:
	int sockfd;

   public:
	ClientTCP(const std::string& ip, in_port_t port);
	~ClientTCP();

	[[nodiscard]] int accept_connection() const;
	void rcv_all(void* buf, size_t len) const;
	void send_message(const void* data) const;
	void receive_message(void* data) const;
	void send_all(const void* data, uint32_t len) const;
};