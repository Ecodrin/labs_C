#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../libs/CustomErrors/errors.h"
#include "../../libs/vector/charvector.h"
#include "../tokens.h"

enum Command { TAKE, PUT, MOVE, SHUT_DOWN };

enum ObjectBoat {EMPTY, WOLF, GOAT, CABBAGE };

enum ResponseCode { FAILED, VICTORY, INCORRECT_COMMAND };

typedef struct CommandMsg {
	long mtype;
	int user_id;
	enum Command command;
	enum ObjectBoat object_boat;

} CommandMsg;

typedef struct ResponseMsg {
	long mtype;
	char result[256];
	enum ResponseCode code;
} ResponseMsg;

typedef struct UserState {
	int peasant_shore;   // где лодка 0, 1 - левый, правый
	int boat_has;        // 0, 1, 2, 3 - пусто, волк, коза, капуста
	int shores[2][3]; // {[волк, коза, капуста], [волк, коза, капуста]} - левый правый
	int id;
} UserState;

typedef struct UserStates {
	size_t size;
	size_t capacity;
	UserState* data;
} UserStates;

error_msg create_queues_msgs(int* msg_id1, int* msg_id2);

error_msg create_user_states(UserStates* users);
error_msg add_user_states(UserStates* users, UserState* user);
error_msg find_user_state(UserStates* users, int id, UserState** user);

error_msg requests_processing(UserStates* users, CommandMsg* input_msg, ResponseMsg* output_msg);