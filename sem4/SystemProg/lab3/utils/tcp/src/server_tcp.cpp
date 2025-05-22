#include "../include/server_tcp.hpp"

void ServerTCP::send_message(int sockfd, void* data) {
	uint32_t net_size, out_size;
	std::memmove(&net_size, data, sizeof(uint32_t));
	out_size = ntohl(net_size);

	send_all(sockfd, data, out_size);
}

void ServerTCP::receive_message(int sockfd, void* data)  {
	uint32_t net_size, out_size;
	rcv_all(sockfd, &net_size, sizeof(net_size));
	out_size = ntohl(net_size) - sizeof(out_size);
	std::memmove(data, &net_size, sizeof(out_size));
	data = static_cast<char*>(data) + sizeof(out_size);

	rcv_all(sockfd, data, out_size);
}

void ServerTCP::rcv_all(int sockfd, void* buf, size_t len) {
	char* p = static_cast<char*>(buf);
	while(len > 0) {
		ssize_t received = read(sockfd, p, len);
		if(received < 0) {
			throw ConnectError("error rcv_all");
		}
		p += received;
		len -= received;
	}
}
ServerTCP::~ServerTCP() {
	shutdown(sockfd, SHUT_RDWR);
	close(sockfd);
}

void ServerTCP::send_all(int sockfd, const void* data, uint32_t len) {
	const char* p = static_cast<const char*>(data);
	while (len > 0) {
		ssize_t sent = send(sockfd, p, len, 0);
		if (sent <= 0) {
			throw ConnectError("error send_all");
		}
		p += sent;
		len -= sent;
	}
}


ServerTCP::ServerTCP(in_port_t port) {
	logger = Logger::Builder()
		.setName("ServerTcp")
		.addHandler(std::make_unique<FileLoggerHandler>("logs/server_tcp.log"))
		.build();
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		logger->LogError("socket error");
		throw ConnectError("Socket creation failed");
	}

	sockaddr_in address{};
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);


	if(set_nonblocking(sockfd) < 0) {
		logger->LogError("non blocking failed");
		throw ConnectError("non blocking failed");
	}


	int yes = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	if (bind(sockfd, (sockaddr*)&address, sizeof(address)) < 0) {
		close(sockfd);
		logger->LogError("bind error");
		throw ConnectError("bind failed");
	}
	if(listen(sockfd, 5) < 0) {
		close(sockfd);
		logger->LogError("listen error");
		throw ConnectError("listen failed");
	}

	logger->LogInfo("tcp_server init");
}

int ServerTCP::accept_connection() const {
	sockaddr_in address{};
	socklen_t addrlen = sizeof(address);
	int new_socketfd = accept(sockfd, (sockaddr*)&address, &addrlen);

	if (new_socketfd < 0) {
		if (errno == EWOULDBLOCK || errno == EAGAIN ) {
			return -1;
		} else {
			logger->LogError("error in accept connection");
			throw ConnectError("accept failed");
		}
	}
	return new_socketfd;
}
int ServerTCP::set_nonblocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) return -1;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
