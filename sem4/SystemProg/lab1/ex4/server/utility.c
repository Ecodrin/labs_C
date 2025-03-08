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

	int tmp_msg_1 = msgget(tmp_key1, IPC_CREAT | 0666);
	if (tmp_msg_1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	int tmp_msg_2 = msgget(tmp_key2, IPC_CREAT | 0666);
	if (tmp_msg_2 == -1) {
		msgctl(tmp_msg_1, IPC_RMID, 0);
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}
	*msg_id1 = tmp_msg_1;
	*msg_id2 = tmp_msg_2;

	return (error_msg){SUCCESS, "", ""};
}

error_msg create_user_states(UserStates* users) {
	if (users == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	UserState* tmp = (UserState*)calloc(2, sizeof(UserState));
	if (tmp == NULL) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated"};
	}
	users->size = 0;
	users->capacity = 2;
	users->data = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg add_user_states(UserStates* users, UserState* user) {
	if (users == NULL || user == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	if (users->capacity == users->size) {
		UserState* tmp = (UserState*)realloc(users->data, 2 * users->capacity * sizeof(UserState));
		if (tmp == NULL) {
			return (error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated error"};
		}
		users->data = tmp;
		users->capacity *= 2;
	}
	users->data[users->size] = *user;

	users->size += 1;
	return (error_msg){SUCCESS, "", ""};
}

error_msg find_user_state(UserStates* users, int id, UserState** user) {
	if (users == NULL || user == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	for (int i = 0; i < users->size; ++i) {
		if (users->data[i].id == id) {
			*user = &users->data[i];
			return (error_msg){SUCCESS, "", ""};
		}
	}
	return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "this id doesn't exist"};
}

void clear_user(UserState * user) {
	user->boat_has = 0;
	user->peasant_shore = 1;
	user->shores[0][0] = 0;
	user->shores[0][1] = 0;
	user->shores[0][2] = 0;
	user->shores[1][0] = 1;
	user->shores[1][1] = 1;
	user->shores[1][2] = 1;
}

error_msg requests_processing(UserStates* users, CommandMsg* input_msg, ResponseMsg* output_msg) {
	if (users == NULL || input_msg == NULL || output_msg == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	// Ищем или создаем юзера
	UserState tmp = {.id = 0, .peasant_shore = 1, .boat_has = 0, .shores = {{0, 0, 0}, {1, 1, 1}}};
	UserState * user;
	error_msg errorMsg = find_user_state(users, input_msg->user_id, &user);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		
		tmp.id = input_msg->user_id;
		errorMsg = add_user_states(users, &tmp);
		if(errorMsg.type){
			return errorMsg;
		}
		find_user_state(users, input_msg->user_id, &user);
	}
	else if (errorMsg.type) {
		return errorMsg;
	}

	switch (input_msg->command) {
		case PUT:
			if (user->boat_has) {
				user->shores[user->peasant_shore][user->boat_has - 1] = 1;
				user->boat_has = EMPTY;
			} else {
				output_msg->code = INCORRECT_COMMAND;
				strcpy(output_msg->result, "boat is empty");
				return (error_msg){SUCCESS, "", ""};
			}
			break;
		case MOVE:
			user->peasant_shore = (user->peasant_shore + 1) % 2;
			break;
		case TAKE:
			if(user->boat_has || user->shores[user->peasant_shore][input_msg->object_boat - 1] == 0) {
				output_msg->code = INCORRECT_COMMAND;
				strcpy(output_msg->result, "boat is busy or object on another shore");
				return (error_msg){SUCCESS, "", ""};
			} else {
				user->shores[user->peasant_shore][input_msg->object_boat - 1] = 0;
				user->boat_has = input_msg->object_boat;
			}
			break;
		default:
			break;
	}

	if(user->shores[0][0] == 1 && user->shores[0][1] == 1 && user->shores[0][2] == 1){
		strcpy(output_msg->result, "You win.");
		clear_user(user);
		output_msg->code = VICTORY;
	}
	else if(user->shores[(user->peasant_shore + 1) % 2][0] == 1 && user->shores[(user->peasant_shore + 1) % 2][1] == 1 ||
	    user->shores[(user->peasant_shore + 1) % 2][1] == 1 && user->shores[(user->peasant_shore + 1) % 2][2] == 1) {
		output_msg->code = FAILED;
		strcpy(output_msg->result, "bag command. You'll start playing again.");
		clear_user(user);
	} else {
		output_msg->code = VICTORY;

		strcpy(output_msg->result, "The command has been issued.");
	}

	return (error_msg){SUCCESS, "", ""};
}
