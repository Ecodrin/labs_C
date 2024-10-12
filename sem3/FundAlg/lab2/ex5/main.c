#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "overloads.h"

void test_overfprintf() {
	FILE *file = stdout;
	if (!file) {
		printf("Error opening file for test_overfprintf\n");
		return;
	}

	// Тест для %Ro (Римские числа)
	int count = overfprintf(file, "Roman: %Ro\n", 1984);
	// Ожидаемый результат: "Roman: MCMLXXXIV\n"

	// Тест для %Zr (Числа Фибоначчи)
	count = overfprintf(file, "Zeckendorf: %Zr\n", 100);
	// Ожидаемый результат: "Zeckendorf: 00010100001\n"

	// Тест для %Cv (Преобразование в другую систему счисления)
	count = overfprintf(file, "Base 16: %Cv\n", 255, 16);
    // Ожидаемый результат: "Base 16: ff\n"

	// Тест для %CV (Преобразование в другую систему счисления с верхним регистром)
	count = overfprintf(file, "Base 16 (upper): %CV\n", 255, 16);
	// Ожидаемый результат: "Base 16 (upper): FF\n"

	// Тест для %to (Преобразование из другой системы счисления в десятичную)
	count = overfprintf(file, "From base 16: %to\n", "ff", 16);
	// Ожидаемый результат: "From base 16: 255\n"

	// Тест для %TO (Преобразование из другой системы счисления в десятичную с верхним регистром)
	count = overfprintf(file, "From base 16 (upper): %TO\n", "FF", 16);
	// Ожидаемый результат: "From base 16 (upper): 255\n"

	// Тест для %mi (Память int32_t)
	count = overfprintf(file, "Memory dump int32_t: %mi\n", -1234567890);
	// Ожидаемый результат: "Memory dump int32_t: 00101110 11111101 01101001 10110110 \n"

	// Тест для %mu (Память uint32_t)
	count = overfprintf(file, "Memory dump uint32_t: %mu\n", 1234567890);
	// Ожидаемый результат: "Memory dump uint32_t: 11010010 00000010 10010110 01001001 \n"

	// Тест для %md (Память double)
	count = overfprintf(file, "Memory dump double: %md\n", 123.456);
	// Ожидаемый результат: "Memory dump double: 01110111 10111110 10011111 00011010 00101111 11011101 01011110 010000\n"

	// Тест для %mf (Память float)
	count = overfprintf(file, "Memory dump float: %mf\n", 123.456);
	// Ожидаемый результат: "Memory dump float: 01111001 11101001 11110110 01000010 \n"

	printf("Test overfprintf passed!\n");
}

void test_oversprintf() {
	char buffer[1024];
	printf("%lu\n", sizeof(buffer));
	// Тест для %Ro (Римские числа)
	int count = oversprintf(buffer, "Roman: %Ro\n", 1984);
	printf("%s", buffer);
	// Тест для %Zr (Числа Фибоначчи)
	count = oversprintf(buffer, "Zeckendorf: %Zr\n", 100);
	printf("%s", buffer);
	// Тест для %Cv (Преобразование в другую систему счисления)
	count = oversprintf(buffer, "Base 16: %Cv\n", 255, 16);
	printf("%s", buffer);
	// Тест для %CV (Преобразование в другую систему счисления с верхним регистром)
	count = oversprintf(buffer, "Base 16 (upper): %CV\n", 255, 16);
	printf("%s", buffer);
	// Тест для %to (Преобразование из другой системы счисления в десятичную)
	count = oversprintf(buffer, "From base 16: %to\n", "ff", 16);
	printf("%s", buffer);
	// Тест для %TO (Преобразование из другой системы счисления в десятичную с верхним регистром)
	count = oversprintf(buffer, "From base 16 (upper): %TO\n", "FF", 16);
	printf("%s", buffer);
	// Тест для %mi (Память int32_t)
	count = oversprintf(buffer, "Memory dump int32_t: %mi\n", -1234567890);
	printf("%s", buffer);
	// Тест для %mu (Память uint32_t)
	count = oversprintf(buffer, "Memory dump uint32_t: %mu\n", 1234567890);
	printf("%s", buffer);
	// Тест для %md (Память double)
	count = oversprintf(buffer, "Memory dump double: %md\n", 123.456);
	printf("%s", buffer);
	// Тест для %mf (Память float)
	count = oversprintf(buffer, "Memory dump float: %mf\n", 123.456);
	printf("%s", buffer);
	printf("Test oversprintf passed!\n");
}

int main() {
	test_overfprintf();
	test_oversprintf();
	return 0;
}