#include "ex8.h"


int main(){
	char result1[100];
	error_msg error1 = AdditionManyNumbers(result1, 10, 3, "123", "456", "789");
	if (error1) {
		return print_error(error1);
	}
	printf("AdditionManyNumbers Test 1: %s\n", result1); // Ожидаемый результат: "1368"

	char result2[100];
	error_msg error2 = AdditionManyNumbers(result2, 16, 4, "1a", "2b", "3c", "4d");
	if (error2) {
		return print_error(error2);
	}
	printf("AdditionManyNumbers Test 2: %s\n", result2); // Ожидаемый результат: "ce"

	char result6[100];
	error_msg error6 = AdditionManyNumbers(result6, 10, 5, "123", "456", "789", "1011", "2345");
	if (error6) {
		return print_error(error6);
	}
	printf("AdditionManyNumbers Test 6: %s\n", result6); // Ожидаемый результат: "4724"

	char result7[100];
	error_msg error7 = AdditionManyNumbers(result7, 16, 3, "ffff", "1", "1");
	if (error7) {
		return print_error(error7);
	}
	printf("AdditionManyNumbers Test 7: %s\n", result7); // Ожидаемый результат: "10001"

	char result8[100];
	error_msg error8 = AdditionManyNumbers(result8, 8, 3, "777", "1", "1");
	if (error8) {
		return print_error(error8);
	}
	printf("AdditionManyNumbers Test 8: %s\n", result8); // Ожидаемый результат: "1001"

	char result9[100];
	error_msg error9 = AdditionManyNumbers(result9, 2, 3, "111", "1", "1");
	if (error9) {
		return print_error(error9);
	}
	printf("AdditionManyNumbers Test 9: %s\n", result9); // Ожидаемый результат: "1001"

	char result10[100];
	error_msg error10 = AdditionManyNumbers(result10, 10, 2, "000123", "000456");
	if (error10) {
		return print_error(error10);
	}
	printf("AdditionManyNumbers Test 10: %s\n", result10); // Ожидаемый результат: "579"

	char result11[100];
	error_msg error11 = AdditionManyNumbers(result11, 10, 2, "999", "1");
	if (error11) {
		return print_error(error11);
	}
	printf("AdditionManyNumbers Test 11: %s\n", result11); // Ожидаемый результат: "1000"


	return NORMAL;
}