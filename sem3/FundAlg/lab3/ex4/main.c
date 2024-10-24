#include "mail.h"


int main(){
	int capacity_mails = 10;
	int count_mails = 0;
	Post post;
	error_msg errorMsg = create_post(&post, capacity_mails, "Moscow", "1-line", 12, "k1", 43, "123456");
	if(errorMsg) return print_error(errorMsg);

	Time t = {1,2, 3, 4, 5, 6};
	Time t2 = {1, 2, 3, 4, 5, 29};
	Mail mail;
	errorMsg = create_mail(&mail, "moscow", "1-line", 123, "1k", 1234, "123456", 12.92, "12345678901234", t, t2);
	if(errorMsg) return print_error(errorMsg);
	errorMsg = push_mail_into_post(&post, &count_mails, &capacity_mails, &mail);
	if(errorMsg) return print_error(errorMsg);
	errorMsg = find_not_received_mails(&post, count_mails);
	if(errorMsg) return errorMsg;
	destroy_post(&post, count_mails);
}














//#include "../lib/vector/charvector.h"
//
//
//int main(){
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
//}