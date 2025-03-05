
#include "utility.h"

error_msg create_queues_msgs(int* msg_id1, int* msg_id2) {
	if (msg_id1 == NULL || msg_id2 == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	key_t tmp_key1 = ftok(FILE_TOKEN, PROJECT_ID_KEY_1);
	if (tmp_key1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}

	key_t tmp_key2 = ftok(FILE_TOKEN, PROJECT_ID_KEY_2);
	if (tmp_key2 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}

	if (tmp_key1 == tmp_key2) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "project keys aren't different"};
	}

	int tmp_msg_1 = msgget(tmp_key1, 0666);
	if (tmp_msg_1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	int tmp_msg_2 = msgget(tmp_key2, 0666);
	if (tmp_msg_2 == -1) {
		msgctl(tmp_msg_1, IPC_RMID, 0);
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	*msg_id1 = tmp_msg_1;
	*msg_id2 = tmp_msg_2;
	return (error_msg){SUCCESS, "", ""};
}

error_msg processing_file_with_instructions(FILE* f, CommandMsg* commandMsg) {
	if (f == NULL || commandMsg == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	String command;
	error_msg errorMsg = create_string(&command, "");
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = safe_read_string(f, &command);
	if (errorMsg.type) {
		destroy_string(&command);
		return errorMsg;
	}

	if (string_cmp(command.arr, "put")) {
		commandMsg->command = PUT;
	} else if (string_cmp(command.arr, "move")) {
		commandMsg->command = MOVE;
	} else if (string_cmp(command.arr, "take")) {
		clear_string(&command);
		commandMsg->command = TAKE;
		errorMsg = safe_read_string(f, &command);
		if (errorMsg.type) {
			destroy_string(&command);
			return errorMsg;
		}
		if (string_cmp(command.arr, "wolf")) {
			commandMsg->object_boat = WOLF;
		} else if (string_cmp(command.arr, "goat")) {
			commandMsg->object_boat = GOAT;
		} else if (string_cmp(command.arr, "cabbage")) {
			commandMsg->object_boat = CABBAGE;
		} else {
			destroy_string(&command);
			return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "incorrect command"};
		}
	} else {
		destroy_string(&command);
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "incorrect command"};
	}

	destroy_string(&command);
	return (error_msg){SUCCESS, "", ""};
}