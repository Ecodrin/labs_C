#pragma once

#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../libs/CustomErrors/errors.h"
#include "../../libs/mstring/mstring.h"
#include "../../libs/vector/stringvector.h"
#include "../tokens.h"

struct MsgBuffer {
	long mtype;
	char filename[FILENAME_MAX];
	int is_end;
};

typedef struct {
	char dir[FILENAME_MAX];
	StringVector* files;
} DirEntry;

error_msg init(int* msg_id_1, int* msg_id_2);

error_msg processing_paths(StringVector* input, StringVector** output);