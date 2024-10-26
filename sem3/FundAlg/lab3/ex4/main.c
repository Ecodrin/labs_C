#include "mail.h"

const char* MSG[] = {"Enter the command:\n",
                     "Email format:\n(city street house building apartment post_index parcel_weight mail_id "
                     "mail_create_time(%d:%d:%d %d:%d:%d) mail_receipt_time(%d:%d:%d %d:%d:%d))\n",
                     "You entered the wrong command\n",
                     "Unrecognized command\n",
                     "Incorrect data\n",
                     "Please, write mail_id: "};

const char* COMMANDS[] = {"add the email\n",
                          "help\n",
                          "print all emails\n",
                          "delete email\n",
                          "find email\n",
                          "print receipt emails\n",
                          "print not receipt emails\n"};

int main() {
	int capacity_mails = 10;
	int count_mails = 0;
	Post post;
	error_msg errorMsg = create_post(&post, capacity_mails, "Moscow", "1-line", 12, "k1", 43, "123456");
	if (errorMsg) {
		destroy_post(&post, count_mails);
		return print_error(errorMsg);
	}
	print_post(stdout, &post, count_mails);
	char command[1000];
	command[0] = '\0';
	printf("\nIf you need help: %s\n", COMMANDS[1]);
	while (1) {
		if(!string_cmp(command, "\n")) printf("%s> ", MSG[0]);
		char* er = fgets(command, sizeof(command), stdin);
		if (!er) break;
//		Добавление письма
		if (string_cmp(command, COMMANDS[0]) || string_cmp(command, "1\n")) {
			printf("%s", MSG[1]);
			Mail mail;
			errorMsg = scan_email(&mail);
			if (errorMsg == INCORRECT_OPTIONS_ERROR) {
				printf("%s", MSG[4]);
				continue;
			} else if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			}
			errorMsg = push_mail_into_post(&post, &count_mails, &capacity_mails, &mail);
			if (errorMsg == INCORRECT_OPTIONS_ERROR) {
				printf("%s", MSG[4]);
				continue;
			} else if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			}
//			Печать всех команд
		} else if (string_cmp(command, COMMANDS[1]) || string_cmp(command, "2\n")) {  // КККККККККККККККККККККККККККККККККККККККК
			printf("You should write one of these commands:\n");
			for (int i = 0; i < 7; ++i) {
				printf("%d. %s", i + 1, COMMANDS[i]);
			}
			printf("Program can get command with indices\n");
//			Печать всех писем
		} else if (string_cmp(command, COMMANDS[2]) || string_cmp(command, "3\n")) {
			print_post(stdout, &post, count_mails);
//			Удаление письма
		} else if (string_cmp(command, COMMANDS[3]) || string_cmp(command, "4\n")) {
			printf("%s", MSG[5]);
			char id[100];
			scanf("%s", id);
			String mail_id;
			errorMsg = create_string(&mail_id, id);
			if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			}
			errorMsg = delete_mail_in_post(&post, &mail_id, &count_mails);
			destroy_string(&mail_id);
			if (errorMsg == INCORRECT_OPTIONS_ERROR) {
				clear_buffer();
				printf("%s", MSG[4]);
			} else if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			}
//			Поиск письма
		} else if (string_cmp(command, COMMANDS[4]) || string_cmp(command, "5\n")) {
			printf("%s", MSG[5]);
			char id[100];
			scanf("%s", id);
			Mail mail;
			String mail_id;
			errorMsg = create_string(&mail_id, id);
			if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			}
			int index;
			errorMsg = find_mail_in_post(&post, &mail, &mail_id, count_mails, &index);
			destroy_string(&mail_id);
			if (errorMsg == INCORRECT_OPTIONS_ERROR) {
				printf("%s", MSG[4]);
			} else if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			} else {
				clear_buffer();
				print_mail(stdout, &mail);
			}
//			Поиск доставленных писем
		} else if (string_cmp(command, COMMANDS[5]) || string_cmp(command, "6\n")) {
			errorMsg = find_received_mails(&post, count_mails);
			if (errorMsg) return print_error(errorMsg);
//			Поиск не доставленных писем
		} else if (string_cmp(command, COMMANDS[6]) || string_cmp(command, "7\n")) {
			errorMsg = find_not_received_mails(&post, count_mails);
			if (errorMsg) return print_error(errorMsg);
//			Неверная команда
		} else if (!string_cmp(er, "\n")) {
			printf("%s", MSG[3]);
		}
	}

	destroy_post(&post, count_mails);
}

// #include "../lib/vector/charvector.h"
//
//
// int main(){
//	String s1;
//	String s2;
//	create_string(&s1, "Hello world");
//	create_string(&s2, "aaaaaaaaaaaaaaaaa");
//	printf("%d\n", s1.size);
//	error_msg errorMsg = mstrcopy(&s1, &s2, 0, SizeString(s1.arr));
//	printf("%d %d\n", errorMsg, s2.size);
//	print_string(stdout, &s2, "");
//
//	destroy_string(&s1);
//	destroy_string(&s2);
//
//	create_string(&s1, "Hello world");
//	create_string(&s2, "aaaaaaaaaaaaaaaaa");
//	int eq = strings_equals(&s1, &s2);
//	printf("%d\n", eq);
//	destroy_string(&s1);
//	destroy_string(&s2);
//
//
//	create_string(&s1, "Hello world");
//	printf("|%s|\n", s1.arr);
//	errorMsg = mstrcopynew(&s1, &s2);
//	if(errorMsg) print_error(errorMsg);
//	printf("|%s|\n", s2.arr);
//	destroy_string(&s1);
//	destroy_string(&s2);
//
//
//	create_string(&s1, "Hello world");
//	create_string(&s2, "aaaaaaaaaaaaaaaaa");
//	errorMsg = mstrcat(&s1, &(s2));
//	printf("%d\n", errorMsg);
//	printf("%s\n", s1.arr);
//	destroy_string(&s1);
//	destroy_string(&s2);
//
//
//	return 0;
// }