#include "compiler.hpp"


int main() {
    Compiler compiler{"/tmp", 25, "/tmp", 35};
    try {
		compiler.work();
	} catch (std::exception & err) {
		compiler.logger->LogError(err.what());
	}
}