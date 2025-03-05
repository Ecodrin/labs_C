

#include "utility.h"

int main() {
	UserStates users;
	error_msg errorMsg = create_user_states(&users);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}

	int msg_key1, msg_key2;
	errorMsg = create_queues_msgs(&msg_key1, &msg_key2);
	if (errorMsg.type) {
		free(users.data);
		return print_error(errorMsg);
	}

	CommandMsg input_msg;
	while (1) {
		int er = msgrcv(msg_key1, &input_msg, sizeof(input_msg) - sizeof(input_msg.mtype), 0, 0);
		if (er == -1) {
			printf("Error in msgrcv");
			continue;
		}

		// Сервер прекращает работу
		if (input_msg.command == SHUT_DOWN && input_msg.user_id == PASSWORD_ADMIN) {
			printf("Server was stopped.\n");
			break;
		}

		ResponseMsg output_msg = {.mtype = input_msg.mtype};

		errorMsg = requests_processing(&users, &input_msg, &output_msg);
		if (errorMsg.type) {
			msgctl(msg_key1, IPC_RMID, NULL);
			msgctl(msg_key2, IPC_RMID, NULL);
			free(users.data);
			return print_error(errorMsg);
		}

		er = msgsnd(msg_key2, &output_msg, sizeof(output_msg) - sizeof(output_msg.mtype), 0);
		if (er == -1) {
			printf("Error in msgsnd");
			continue;
		}

	}

	msgctl(msg_key1, IPC_RMID, NULL);
	msgctl(msg_key2, IPC_RMID, NULL);
	free(users.data);
	return 0;
}