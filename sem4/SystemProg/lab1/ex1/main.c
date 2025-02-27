#include "utility.h"

int main(){
	Users users = {NULL, 2, 0};
	User* tmp = (User*)calloc(users.capacity, sizeof(User));
	if(tmp == NULL) {
		return print_error((error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated"});
	}
	users.data = tmp;

	error_msg errorMsg = load("storage.bin", &users);
	if(errorMsg.type){
		free(users.data);
		return print_error(errorMsg);
	}

	while (1){
		printf("------------------------------------------------------------------------------\n");
		char login[MAX_LOGIN_LEN + 1];
		int pin;
		Status status = auth_and_register_window(&users, login, &pin);
		if (status.errorMsg.type){
			free(users.data);
			return print_error(status.errorMsg);
		}
		if(status.quit){
			break;
		}

		status = command_window(&users, login);
		if(status.errorMsg.type){
			free(users.data);
			return print_error(status.errorMsg);
		}
		if(status.quit){
			break;
		}
	}

	errorMsg = save("storage.bin", &users);
	if(errorMsg.type){
		free(users.data);
		return print_error(errorMsg);
	}
	free(users.data);
	return 0;
}