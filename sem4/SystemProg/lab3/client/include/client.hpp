#pragma once

#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

#include "client_tcp.hpp"
#include "custom_exceptions.hpp"
#include "logger.hpp"

#define N 15
#define M 5

class Client {
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

	ClientTCP client_tcp;
	bool stop = false;

   public:
	std::unique_ptr<Logger> logger;
	Client(in_port_t port, const std::string &ip);

	void work();

	~Client();

	void get_file(const std::string &filename, size_t size_file) const;
	void send_file(const std::string &filename, SocketData::Command command) const;

	int stop_server(size_t password);
	void compile();

	void play();
};