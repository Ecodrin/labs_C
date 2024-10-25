#include "mail.h"

const char* MSG[] = {"Enter the command:\n",
                     "Email format:\n(city street house building apartment post_index parcel_weight mail_id "
                     "mail_create_time(%d:%d:%d %d:%d:%d) mail_create_time mail_receipt_time(%d:%d:%d %d:%d:%d))\n",
                     "You entered the wrong command\n",
                     "Unrecognized command\n",
                     "Incorrect data\n",
                     "Please, write mail_id: "};

const char* COMMANDS[] = {"Add the email\n",
                          "Help\n",
                          "Print all emails\n",
                          "Delete email\n",
                          "Find email\n",
                          "Print receipt emails\n",
                          "Print not receipt emails\n"};

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
	printf("\nIf you need help: %s\n", COMMANDS[1]);
	while (1) {
		printf("%s> ", MSG[0]);
		char* er = fgets(command, sizeof(command), stdin);
		if (!er) break;
		if (string_cmp(command, COMMANDS[0])) {
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
		} else if (string_cmp(command, COMMANDS[1])) {  // КККККККККККККККККККККККККККККККККККККККК
			printf("You should write one of these commands:\n");
			for (int i = 0; i < 7; ++i) {
				printf("%d. %s", i + 1, COMMANDS[i]);
			}
		} else if (string_cmp(command, COMMANDS[2])) {
			print_post(stdout, &post, count_mails);
		} else if (string_cmp(command, COMMANDS[3])) {
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
				printf("%s", MSG[4]);
			} else if (errorMsg) {
				destroy_post(&post, count_mails);
				return print_error(errorMsg);
			}
		} else if (string_cmp(command, COMMANDS[4])) {
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
		} else if (string_cmp(command, COMMANDS[5])) {
			errorMsg = find_received_mails(&post, count_mails);
			if (errorMsg) return print_error(errorMsg);
		} else if (string_cmp(command, COMMANDS[6])) {
			errorMsg = find_not_received_mails(&post, count_mails);
			if (errorMsg) return print_error(errorMsg);
		} else if (!string_cmp(command, "\n")) {
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