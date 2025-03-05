#include "utility.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		return print_error((error_msg){INCORRECT_ARG_FUNCTION, __func__, "should be file with instructions"});
	}
	int key_msg1, key_msg2;
	error_msg errorMsg = create_queues_msgs(&key_msg1, &key_msg2);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}

	if(string_cmp(argv[1], "STOP") && argc == 3){
		int password;
		password = str_to_int(argv[2]);
		CommandMsg request = {.mtype = getpid(), .command = SHUT_DOWN, .user_id = password};
		int er = msgsnd(key_msg1, &request, sizeof(request) - sizeof(long), 0);
		if (er == -1) {
			return print_error((error_msg){TOKEN_ERROR, __func__, "msgsnd"});
		}
		return 0;
	}

	FILE* file_with_instructions = fopen(argv[1], "r");
	if (file_with_instructions == NULL) {
		return print_error((error_msg){INPUT_FILE_ERROR, __func__, "input file didn't open"});
	}

	while (!feof(file_with_instructions)) {
		CommandMsg request = {.mtype = getpid(), .command = TAKE, .user_id = getpid()};


		errorMsg = processing_file_with_instructions(file_with_instructions, &request);
		if (errorMsg.type) {
			fclose(file_with_instructions);
			return print_error(errorMsg);
		}

		int er = msgsnd(key_msg1, &request, sizeof(request) - sizeof(long), 0);
		if (er == -1) {
			return print_error((error_msg){TOKEN_ERROR, __func__, "msgsnd"});
		}

		ResponseMsg answer;

		er = msgrcv(key_msg2, &answer, sizeof(answer) - sizeof(long), request.mtype, 0);
		if (er == -1) {
			return print_error((error_msg){TOKEN_ERROR, __func__, "msgrcv"});
		}

		switch (answer.code) {
			case INCORRECT_COMMAND:
				printf("Incorrect command: %s\n", answer.result);
				break;
			case VICTORY:
				printf("%s\n", answer.result);
				break;

			case FAILED:
				printf("FAILED. %s\n",  answer.result);
				break;
		}
	}

	fclose(file_with_instructions);
	return 0;
}