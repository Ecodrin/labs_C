#include "overloads.h"


int main() {
	int count = overfprintf(stdout, "He %Zr l%mf\n", 25, 13243.123);
	printf("%d\n", count);
	char s[10000];
	int n = oversprintf(s, "He %Zr l%mf\n", 25,13243.123);
	printf("%s%d\n", s, n);

	printf("df %hd f\n", 12);
}