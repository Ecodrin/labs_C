#include "utility.h"

int main() {
	int msg_id_1;
	int msg_id_2;

	error_msg errorMsg = init(&msg_id_1, &msg_id_2);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}

	long type_input_msg = 0;

	struct MsgBuffer input_msg;

	StringVector *paths = create_string_vector(1);
	if (!paths) {
		msgctl(msg_id_1, IPC_RMID, 0);
		msgctl(msg_id_2, IPC_RMID, 0);
		return print_error((error_msg){MEMORY_ALLOCATED_ERROR, __func__, "create_string vector"});
	}

	while (1) {
		int er = msgrcv(msg_id_1, &input_msg, sizeof(input_msg.filename) + sizeof(input_msg.is_end), type_input_msg, 0);
		if (er == -1) {
			msgctl(msg_id_1, IPC_RMID, 0);
			msgctl(msg_id_2, IPC_RMID, 0);
			return print_error((error_msg){SERVER_ERROR, __func__, "msgcrv."});
		}

		if (strcmp("STOP", input_msg.filename) == 0 && input_msg.is_end == SHUT_DOWN_SERVER_PASSWORD) {
			break;
		}

		// Начинаем складывать в массив пути от одного клиента
		if (type_input_msg == 0) {
			clear_string_vector(paths);
			type_input_msg = input_msg.mtype;
		}

		// Добавляем в путь
		if (type_input_msg > 0) {
			if(access(input_msg.filename, F_OK) == 0) {
				errorMsg = push_end_string_vector(paths, input_msg.filename);
				if (errorMsg.type) {
					destroy_string_vector(paths);
					msgctl(msg_id_1, IPC_RMID, 0);
					msgctl(msg_id_2, IPC_RMID, 0);
					return print_error(errorMsg);
				}
			}
		}

		// Конец запроса от одного клиента
		if (input_msg.is_end) {
			StringVector *output;
			errorMsg = processing_paths(paths, &output);
			if (errorMsg.type) {
				destroy_string_vector(paths);
				msgctl(msg_id_1, IPC_RMID, 0);
				msgctl(msg_id_2, IPC_RMID, 0);
				return print_error(errorMsg);
			}

			for (int j = 0; j < output->size; ++j) {
				struct MsgBuffer output_msg = {.mtype = type_input_msg};
				strncpy(output_msg.filename, output->data[j], FILENAME_MAX);
				if (j == output->size - 1) {
					output_msg.is_end = 1;
				}
				er = msgsnd(msg_id_2, &output_msg, sizeof(output_msg.filename) + sizeof(output_msg.is_end), 0);
				if (er) {
					destroy_string_vector(paths);
					msgctl(msg_id_1, IPC_RMID, 0);
					msgctl(msg_id_2, IPC_RMID, 0);
					return print_error((error_msg){SERVER_ERROR, __func__, "msgsnd"});
				}
			}
			destroy_string_vector(output);
			type_input_msg = 0;
		}
	}

	destroy_string_vector(paths);
	msgctl(msg_id_1, IPC_RMID, 0);
	msgctl(msg_id_2, IPC_RMID, 0);
	return 0;
}