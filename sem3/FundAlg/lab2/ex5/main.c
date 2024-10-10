#include "overloads.h"


int main() {
	// TODO fprintf основные функции написаны/ надо дописать доп
	int count = overfprintf(stdout, "Hello%04df%xriend%*\n", 12, 12, 23);
	printf("%d\n", count);
	int n = fprintf(stdout,"Hello%04dfrie%xnd%*\n", 12, 12, 23);
	printf("%d\n", n);
}