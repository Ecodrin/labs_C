

#pragma once

#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../libs/CustomErrors/errors.h"
#include "../tokens.h"

struct MsgBuffer {
	long mtype;
	char filename[FILENAME_MAX];
	int is_end;
};

error_msg init(int* msg_id_1, int* msg_id_2);