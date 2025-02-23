#include "utility.h"

int pin_hash(int pin) {
	const short a = 21;
	const short c = 123;
	return (a * pin + c) % 100000;
}

error_msg get_time_string(char* buffer) {
	if (buffer == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	time_t raw_time;
	struct tm* time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);

	strftime(buffer, 9, "%H:%M:%S", time_info);
	return (error_msg){SUCCESS, "", ""};
}

error_msg get_date_string(char* buffer) {
	if (buffer == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	time_t raw_time;
	struct tm* time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);

	strftime(buffer, 11, "%d:%m:%Y", time_info);
	return (error_msg){SUCCESS, "", ""};
}

error_msg howmuch_time(const char* date_str, const char* flag, double* res) {
	struct tm user_date = {0};
	time_t user_time, current_time;
	double diff_seconds, result = -1;

	if (sscanf(date_str, "%d:%d:%d", &user_date.tm_mday, &user_date.tm_mon, &user_date.tm_year) != 3 ||
	    (user_date.tm_mon > 12 || user_date.tm_mon < 0) || user_date.tm_year < 0 || user_date.tm_mday < 0 || user_date.tm_mday > 30) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Bad params"};
	}
	user_date.tm_mon -= 1;
	user_date.tm_year -= 1900;

	user_time = mktime(&user_date);
	if (user_time == -1) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Bad params"};
	}

	time(&current_time);

	diff_seconds = difftime(current_time, user_time);
	if (diff_seconds < 0) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Bad params"};
	}

	if (strcmp(flag, "-s") == 0) {
		result = diff_seconds;
	} else if (strcmp(flag, "-m") == 0) {
		result = diff_seconds / 60;
	} else if (strcmp(flag, "-h") == 0) {
		result = diff_seconds / 3600;
	} else if (strcmp(flag, "-y") == 0) {
		result = diff_seconds / 31536000.0;
	} else {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Bad params"};
	}

	*res = result;
	return (error_msg){SUCCESS, "", ""};
}

int check_correct_login(const char* login) {
	if (login == NULL) {
		return 0;
	}
	for (int i = 0; login[i]; i++) {
		if (i >= 6 || ((login[i] > '9' || login[i] < '0') && (login[i] < 'a' || login[i] > 'z') &&
		               (login[i] < 'A' || login[i] > 'Z'))) {
			return 0;
		}
	}
	return 1;
}

void clear_buffer() {
	char c;
	while ((c = getc(stdin)) != EOF && c != '\n')
		;
}

error_msg register_new_user(Users* users, const char* login, int pin) {
	if (users == NULL || login == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	if (users->capacity == users->size) {
		User* tmp = (User*)realloc(users->data, users->capacity * 2 * sizeof(User));
		users->capacity *= 2;
		if (tmp == NULL) {
			return (error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated in resize"};
		}
		users->data = tmp;
	}

	if (pin < 0 || pin > 100000 || !check_correct_login(login)) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "incorrect login or pin"};
	}
	for(int i = 0; i < users->size; i++){
		if(strcmp(login, users->data[i].login) == 0) {
			return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "this login already exists"};
		}
	}
	strcpy(users->data[users->size].login, login);
	users->data[users->size].pin = pin_hash(pin);
	users->data[users->size].sanctions = -1;
	users->size += 1;
	return (error_msg){SUCCESS, "", ""};
}

error_msg authentication_user(Users* users, const char* login, int pin) {
	if (users == NULL || login == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	for (size_t i = 0; i < users->size; i++) {
		if (strcmp(users->data[i].login, login) == 0) {
			if (pin_hash(pin) == users->data[i].pin) {
				return (error_msg){SUCCESS, "", ""};
			} else {
				return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "incorrect login or pin"};
			}
		}
	}
	return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "account doesn't exist"};
}

Status auth_and_register_window(Users* users, char* login, int* pin) {
	if (login == NULL || pin == NULL || users == NULL) {
		return (Status){{INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"}, 0};
	}

	error_msg (*commands[2])(Users* users, const char* login, int pin) = {
	    authentication_user,
	    register_new_user,
	};

	while (1) {
		printf("You can:\n1. Sign in\n2. Sign up\n");

		int com;
		char com_str[10];
		char * c = fgets(com_str, 10, stdin);
		if(c == 0) {
			return (Status){{SUCCESS, "", ""}, 1};
		}
		if (strcmp("Sign in\n", com_str) == 0 || strcmp("1\n", com_str) == 0) {
			com = 1;
		} else if (strcmp("Sign up\n", com_str) == 0 || strcmp("2\n", com_str) == 0) {
			com = 2;
		} else {
			clear_buffer();
			continue;
		}

		printf("Write login: ");
		while (scanf("%s", login) == 0 || !check_correct_login(login)) {
			printf("incorrect login.\n");
			clear_buffer();
			printf("Write login: ");
		}

		printf("Write pin: ");
		while (scanf("%d", pin) == 0 || *pin < 0 || *pin > 100000) {
			printf("Incorrect pin.\n");
			clear_buffer();
			printf("Write pin: ");
		}

		error_msg errorMsg = commands[com - 1](users, login, *pin);
		switch (errorMsg.type) {
			case INCORRECT_OPTIONS_ERROR:
				printf("%s\n", errorMsg.msg);
				clear_buffer();
				break;
			case SUCCESS:
				return (Status){{SUCCESS, "", ""}, 0};
			default:
				return (Status){errorMsg, 0};
		}
	}
}

Command recognize_command(const char* com) {
	char tmp[30];
	int i = 0;
	for (; com[i] && i < 30; i++) {
		if (com[i] == ' ') {
			break;
		}
	}
	if (i == -1) {
		return UNRECOGNIZED_C;
	}
	strcopy(com, tmp, 0, i);
	tmp[i] = '\0';
	if (strcmp(tmp, "Time\n") == 0 || strcmp(tmp, "1\n") == 0) {
		return TIME_C;
	} else if (strcmp(tmp, "Date\n") == 0 || strcmp(tmp, "2\n") == 0) {
		return DATE_C;
	} else if (strcmp(tmp, "Howmuch") == 0 || strcmp(tmp, "3\n") == 0) {
		return HOW_MUCH_C;
	} else if (strcmp(tmp, "Logout\n") == 0 || strcmp(tmp, "4\n") == 0) {
		return LOGOUT_C;
	} else if (strcmp(tmp, "Sanctions") == 0 || strcmp(tmp, "5\n") == 0) {
		return SANCTIONS_C;
	} else {
		return UNRECOGNIZED_C;
	}
}

error_msg parse_string_to_buffer2(String* src, String* buf, String* buf2) {
	if (src == NULL || buf == NULL || buf2 == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	strip(src);
	int index_first_namespace = -1, index_last_name_space = -1;
	for (int i = 0; src->arr[i]; i++) {
		if (src->arr[i] == ' ') {
			index_first_namespace = i;
			break;
		}
	}

	for (int i = src->size - 1; i >= 0; i--) {
		if (src->arr[i] == ' ') {
			index_last_name_space = i;
			break;
		}
	}
	if (index_last_name_space == -1 || index_first_namespace == -1) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Bad params"};
	}

	error_msg errorMsg = mstrcopy(src, buf, index_first_namespace, index_last_name_space);
	if (errorMsg.type) {
		return errorMsg;
	}

	strip(buf);

	errorMsg = mstrcopy(src, buf2, index_last_name_space, src->size);
	if (errorMsg.type) {
		return errorMsg;
	}

	strip(buf2);

	return (error_msg){SUCCESS, "", ""};
}

error_msg sanctions_func(Users* users, String* login, String* num) {
	if (login == NULL || num == NULL || users == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	int x;
	error_msg errorMsg = string_to_int(num, &x);
	if (errorMsg.type) {
		return errorMsg;
	}
	int password;
	printf("if you want to change selection you should write special code: ");
	scanf("%d", &password);
	if (password == SECRET_PASSWORD) {
		int i = -1;
		for (int j = 0; j < users->size; j++) {
			if (strcmp(users->data[j].login, login->arr) == 0) {
				i = j;
			}
		}
		if (i == -1) {
			return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Login doesn't exist"};
		}
		users->data[i].sanctions = x;
	} else {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "Not correct special key"};
	}

	return (error_msg){SUCCESS, "", ""};
}

Status command_window(Users* users, const char* login) {
	if (users == NULL || login == NULL) {
		return (Status){{INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"}, 0};
	}

	int i = 0, j = -1;
	for (; i < users->size; i++) {
		if (strcmp(users->data[i].login, login) == 0) {
			j = i;
			break;
		}
	}
	if(j == -1){
		return (Status){{INCORRECT_ARG_FUNCTION, __func__, "login doesn't exist"}, 0};
	}
	String command;
	error_msg errorMsg = create_string(&command, "");
	if (errorMsg.type) {
		return (Status){errorMsg, 0};
	}

	String buf1;
	errorMsg = create_string(&buf1, "");
	if (errorMsg.type) {
		destroy_string(&command);
		return (Status){errorMsg, 0};
	}

	String buf2;
	errorMsg = create_string(&buf2, "");
	if (errorMsg.type) {
		destroy_string(&command);
		destroy_string(&buf1);
		return (Status){errorMsg, 0};
	}

	int n = 0;
	printf("You can:\n1.Time\n2.Date\n3.Howmuch <time> flag\n4.Logout\n5.Sanctions username <number>\n");
	while (n < users->data[i].sanctions || users->data[i].sanctions == -1) {
		clear_string(&command);
		clear_string(&buf1);
		clear_string(&buf2);
		int r = read_line(stdin, &command);
		if(r == 0){
			break;
		}
		if(strcmp(command.arr, "\n") == 0) {
			continue;
		}
		Command com = recognize_command(command.arr);

		char buf[11];
		switch (com) {
			case TIME_C: {
			}
				strcpy(buf, command.arr);
				get_time_string(buf);
				printf("%s\n", buf);
				break;

			case DATE_C:
				strcpy(buf, command.arr);
				get_date_string(buf);
				printf("%s\n", buf);
				break;

			case HOW_MUCH_C: {
			}
				errorMsg = parse_string_to_buffer2(&command, &buf1, &buf2);
				if (errorMsg.type) {
					if (errorMsg.type == MEMORY_ALLOCATED_ERROR) {
						clear_string(&command);
						clear_string(&buf1);
						clear_string(&buf2);
						return (Status){errorMsg, 0};
					}
					printf("%s\n", errorMsg.msg);
					break;
				}
				double res = 0;
				errorMsg = howmuch_time(buf1.arr, buf2.arr, &res);
				if (errorMsg.type) {
					printf("%s\n", errorMsg.msg);
					break;
				}
				printf("Time difference: %f\n", res);
				break;

			case LOGOUT_C:
				destroy_string(&command);
				destroy_string(&buf1);
				destroy_string(&buf2);
				return (Status){{SUCCESS, "", ""}, 0};

			case SANCTIONS_C:
				errorMsg = parse_string_to_buffer2(&command, &buf1, &buf2);
				if (errorMsg.type) {
					if (errorMsg.type == MEMORY_ALLOCATED_ERROR) {
						clear_string(&command);
						clear_string(&buf1);
						clear_string(&buf2);
						return (Status){errorMsg, 0};
					}
					printf("%s\n", errorMsg.msg);
					break;
				}
				errorMsg = sanctions_func(users, &buf1, &buf2);
				if (errorMsg.type) {
					printf("%s\n", errorMsg.msg);
					break;
				}
				break;
			default:
				printf("Unrecognized command\n");
		}
		n++;

		printf("You can:\n1.Time\n2.Date\n3.Howmuch <time> flag\n4.Logout\n5.Sanctions username <number>\n");
	}
	if (n == users->data[i].sanctions) {
		printf("You have exceeded your request limit.\n");
		destroy_string(&command);
		destroy_string(&buf1);
		destroy_string(&buf2);
		return (Status){{SUCCESS, "", ""}, 0};
	}

	destroy_string(&command);
	destroy_string(&buf1);
	destroy_string(&buf2);
	return (Status){{SUCCESS, "", ""}, 1};
}