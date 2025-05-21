#include "../include/sticks_game.hpp"

int main() {
	StickGameManager manager{"/tmp", 12, "/tmp", 13};
	try {
		manager.work();
	} catch (std::exception & exception) {
		manager.logger->LogError(exception.what());
	}
}