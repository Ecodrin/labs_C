#pragma once

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libs/mstring/mstring.h"
#include "../libs/vector/charvector.h"
#include "../libs/CustomErrors/errors.h"

#define MAX_LOGIN_LEN 6
#define SECRET_PASSWORD 12345

typedef struct User {
	char login[MAX_LOGIN_LEN + 1];
	int pin;
	int sanctions;
} User;

typedef enum Command { TIME_C, DATE_C, HOW_MUCH_C, LOGOUT_C, SANCTIONS_C, UNRECOGNIZED_C } Command;

typedef struct Users {
	User* data;
	size_t capacity;
	size_t size;
} Users;

typedef struct Status{
	error_msg errorMsg;
	int quit;
}Status;

int pin_hash(int pin);
error_msg get_date_string(char* buffer);
error_msg get_time_string(char* buffer);
error_msg load(const char* filename, Users* users);
error_msg save(const char* filename, Users* users);

error_msg register_new_user(Users* users, const char* login, int pin);
error_msg authentication_user(Users* users, const char* login, int pin);

Status auth_and_register_window(Users* users, char* login, int* pin);
Status command_window(Users* users, const char* login);