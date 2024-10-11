#include "overloads.h"


int main() {
	int count = overfprintf(stdout, "He %x l%mf\n", "J50", 25, 13243.123);
	printf("%d\n", count);
	char s[10000];
	int n = oversprintf(s, "He %x l%mf\n", "J50", 25,13243.123);
	printf("%s%d\n", s, n);

	printf("df %hd f\n", 12);
}