#include "utils.h"


int main(){
	Users users = {NULL, 2, 0};
	User* tmp = (User*)malloc(users.capacity * sizeof(User));
	if(tmp == NULL) {
		return print_error((error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated"});
	}
	users.data = tmp;

	while (1){
		char login[MAX_LOGIN_LEN + 1];
		int pin;
		error_msg errorMsg = auth_and_register_window(&users, login, &pin);
		if (errorMsg.type){
			free(users.data);
			return print_error(errorMsg);
		}
		Status status = command_window(&users, login);
		if(status.errorMsg.type){
			return print_error(status.errorMsg);
		}
		if(status.quit){
			break;
		}
	}
	free(users.data);
	return 0;
}