#pragma once

#include <iostream>
#include <utility>

class ConnectError : std::exception {
   private:
	std::string err;

   public:
	explicit ConnectError(std::string msg) : err{std::move(msg)} {};
	[[nodiscard]] const char* what() const noexcept override;
};