#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../libs/CustomErrors/errors.h"
#include "../../libs/vector/charvector.h"
#include "../tokens.h"

enum Command { TAKE, PUT, MOVE, SHUT_DOWN };

enum ResponseCode { FAILED, VICTORY, INCORRECT_COMMAND };

enum ObjectBoat {
	EMPTY,
	WOLF,
	GOAT,
	CABBAGE,
};

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

error_msg create_queues_msgs(int* msg_id1, int* msg_id2);

error_msg processing_file_with_instructions(FILE* f, CommandMsg* commandMsg);