#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../libs/CustomErrors/errors.h"
#include "../libs/mstring/mstring.h"
#include "../libs/vector/charvector.h"

#define MAX_MSG_SIZE 4096

typedef enum Flags { XOR_F, MASK_F, COPY_F, FIND_F, UNRECOGNIZED_F } Flags;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

typedef struct {
	long mtype;
	char mtext[MAX_MSG_SIZE];
} Message;


error_msg get_32bit(char *mask, int32_t *res);
error_msg generate_filename(char *filename, int j, char *res);
Flags recognize_command(char *s, int *n);
error_msg KMPSearch(char *substring, FILE *f, int *res);

error_msg xor_n(FILE *file, int n, size_t *result);
error_msg find_sum_hex(FILE *file, char *mask, int *res);
error_msg copy_file(const char *src, const char *dst);