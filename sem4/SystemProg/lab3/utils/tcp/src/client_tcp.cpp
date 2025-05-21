#include "../include/client_tcp.hpp"


ClientTCP::ClientTCP(const std::string& ip, in_port_t port) {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in serv_addr{};
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
		throw ConnectError("Invalid address");
	}

	if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		throw ConnectError("Connection failed");
	}
}


ClientTCP::~ClientTCP() {
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}

void ClientTCP::send_all(const void* data, uint32_t len) const {
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

void ClientTCP::receive_message(void* data) const {
	uint32_t net_size, out_size;
	rcv_all(&net_size, sizeof(net_size));
	out_size = ntohl(net_size) - sizeof(out_size);
	std::memmove(data, &net_size, sizeof(out_size));
	data = static_cast<char*>(data) + sizeof(out_size);

	rcv_all(data, out_size);

}
void ClientTCP::send_message(const void* data) const {
	uint32_t net_size, out_size;
	std::memmove(&net_size, data, sizeof(uint32_t));
	out_size = ntohl(net_size);

	send_all(data, out_size);
}

void ClientTCP::rcv_all(void* buf, size_t len) const {
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
