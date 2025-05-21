#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <functional>
#include <memory>

#include "custom_exceptions.hpp"
#include "logger.hpp"

class ServerTCP {
   private:
	int sockfd;

	static int set_nonblocking(int fd);

   public:
	std::unique_ptr<Logger> logger;

	explicit ServerTCP(in_port_t port);
	~ServerTCP();

	[[nodiscard]] int accept_connection() const;
	static void rcv_all(int sockfd, void* buf, size_t len);
	static void send_message(int sockfd, void* data);
	static void receive_message(int sockfd, void* data);
	static void send_all(int sockfd, const void* data, uint32_t len);
};