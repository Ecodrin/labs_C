#include "../include/custom_exceptions.hpp"

const char* ConnectError::what() const noexcept {
	return err.c_str();
}
