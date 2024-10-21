#include "../lib/vector/charvector.h"


int main(){
	String *s1 = create_string("Hello world");
	String *s2 = create_string("aaaaaaaaaaaaaaaaa");
	printf("%d\n", s1->size);
	error_msg errorMsg = mstrcopy(s1, s2, 0, SizeString(s1->arr));
	printf("%d %d\n", errorMsg, s2->size);
	print_string(stdout, s2, "");

	destroy_string(s1);
	destroy_string(s2);

	s1 = create_string("aaaaaaaaaaaaaaaaa");
	s2 = create_string("aaaaaaaaaaaaaaaaa");
	int eq = strings_equals(s1, s2);
	printf("%d\n", eq);
	destroy_string(s1);
	destroy_string(s2);


	s1 = create_string("Hello world");
	errorMsg = mstrcopynew(s1, &s2);
	printf("%s\n", s2->arr);
	destroy_string(s1);
	destroy_string(s2);

	s1 = create_string("Hello world");
	s2 = create_string("aaaaaaaaaaaaaaaaa");
	errorMsg = mstrcat(s1, s2);
	printf("%d\n", errorMsg);
	printf("%s\n", s1->arr);
	destroy_string(s1);
	destroy_string(s2);
	return 0;
}