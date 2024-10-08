#include "ex10.h"

int main() {
	int error = ex();
	switch (error) {
		case ERROR_NUMERAL_SYSTEM:
			printf("Число не в данной сс\n");
			return 1;
		case MEMORY_ERROR:
			printf("Ошибка выделения памяти\n");
			return 1;
		case INDEX_VECTOR_ERROR:
			printf("Обращение к несуществующему элементу массива\n");
			return 1;
		case NOT_SERVICED_NUMERAL_SYSTEM:
			printf("Необслуживамая система счисления.\n");
			return 1;

		case EMPTY_ERROR:
			printf("Дана только сс, нужны числа в данной сс\n");
			return 1;
		default:
			break;
	}

	return 0;
}