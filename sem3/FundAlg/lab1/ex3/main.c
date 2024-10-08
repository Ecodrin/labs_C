
#include <stdio.h>

#include "ex3.h"

int main(int argc, char** argv) {
	kOpts opt = 0;
	double numbers[4];
	void (*handlers[3])() = {HandlerOptQ, HandlerOptM, HandlerOptT};
	int mistake = GetOpts(argc, argv, &opt, numbers);
	switch (mistake) {
		case 1:
			printf("%s", "Incorrect option\n");
			return 1;
		case 2:
			printf("Неверное кол-во аргументов рабочей строки\n");
			return 1;

		default:
			break;
	}
	handlers[opt](numbers);

	return 0;
}