#include <check.h>

#include "ex8.h"

// Объявление тестовых функций
START_TEST(test_add_polynomials) {
	Polynomial* p1;
	Polynomial* p2;
	Polynomial* result;

	// Создание полиномов
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);
	ck_assert_int_eq(create_polynomial(&p2), SUCCESS);
	ck_assert_int_eq(create_polynomial(&result), SUCCESS);

	// Заполнение полиномов
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 2), SUCCESS);
	p1->degree = 1;

	ck_assert_int_eq(push_node_end(&(p2->coefficients), 3), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p2->coefficients), 4), SUCCESS);
	p2->degree = 1;

	// Сложение полиномов
	ck_assert_int_eq(add_polynomials(&result, p1, p2), SUCCESS);

	// Проверка результата
	ck_assert_int_eq(result->degree, 1);
	ck_assert_int_eq(result->coefficients->data, 4);
	ck_assert_int_eq(result->coefficients->next->data, 6);

	// Освобождение памяти
	destroy_polynomial(&p1);
	destroy_polynomial(&p2);
	destroy_polynomial(&result);
}
END_TEST

START_TEST(test_subtract_polynomials) {
	Polynomial* p1;
	Polynomial* p2;
	Polynomial* result;

	// Создание полиномов
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);
	ck_assert_int_eq(create_polynomial(&p2), SUCCESS);
	ck_assert_int_eq(create_polynomial(&result), SUCCESS);

	// Заполнение полиномов
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 2), SUCCESS);
	p1->degree = 1;

	ck_assert_int_eq(push_node_end(&(p2->coefficients), 3), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p2->coefficients), 4), SUCCESS);
	p2->degree = 1;

	// Вычитание полиномов
	ck_assert_int_eq(subtract_polynomials(&result, p1, p2), SUCCESS);

	// Проверка результата
	ck_assert_int_eq(result->degree, 1);
	ck_assert_int_eq(result->coefficients->data, -2);
	ck_assert_int_eq(result->coefficients->next->data, -2);

	// Освобождение памяти
	destroy_polynomial(&p1);
	destroy_polynomial(&p2);
	destroy_polynomial(&result);
}
END_TEST

START_TEST(test_product_polynomials) {
	Polynomial* p1;
	Polynomial* p2;
	Polynomial* result;

	// Создание полиномов
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);
	ck_assert_int_eq(create_polynomial(&p2), SUCCESS);
	ck_assert_int_eq(create_polynomial(&result), SUCCESS);

	// Заполнение полиномов
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 2), SUCCESS);
	p1->degree = 1;

	ck_assert_int_eq(push_node_end(&(p2->coefficients), 3), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p2->coefficients), 4), SUCCESS);
	p2->degree = 1;

	// Умножение полиномов
	ck_assert_int_eq(product_polynomials(&result, p1, p2), SUCCESS);

	// Проверка результата
	ck_assert_int_eq(result->degree, 2);
	ck_assert_int_eq(result->coefficients->data, 3);
	ck_assert_int_eq(result->coefficients->next->data, 10);
	ck_assert_int_eq(result->coefficients->next->next->data, 8);

	// Освобождение памяти
	destroy_polynomial(&p1);
	destroy_polynomial(&p2);
	destroy_polynomial(&result);
}
END_TEST

START_TEST(test_divide_polynomials) {
	Polynomial* p1;
	Polynomial* p2;
	Polynomial* quotient;
	Polynomial* remainder;

	// Создание полиномов
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);
	ck_assert_int_eq(create_polynomial(&p2), SUCCESS);
	ck_assert_int_eq(create_polynomial(&quotient), SUCCESS);
	ck_assert_int_eq(create_polynomial(&remainder), SUCCESS);

	// Заполнение полиномов
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 2), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	p1->degree = 2;

	ck_assert_int_eq(push_node_end(&(p2->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p2->coefficients), 1), SUCCESS);
	p2->degree = 1;

	// Деление полиномов
	ck_assert_int_eq(divide_polynomials(&quotient, &remainder, p1, p2), SUCCESS);

	// Проверка результата
	ck_assert_int_eq(quotient->degree, 1);
	ck_assert_int_eq(quotient->coefficients->data, 1);
	ck_assert_int_eq(quotient->coefficients->next->data, 1);

	ck_assert_int_eq(remainder->degree, 0);
	ck_assert_int_eq(remainder->coefficients->data, 0);

	// Освобождение памяти
	destroy_polynomial(&p1);
	destroy_polynomial(&p2);
	destroy_polynomial(&quotient);
	destroy_polynomial(&remainder);
}
END_TEST



START_TEST(test_composition_polynomials)
{
	Polynomial* p1;
	Polynomial* p2;
	Polynomial* result;

	// Создание полиномов
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);
	ck_assert_int_eq(create_polynomial(&p2), SUCCESS);
	ck_assert_int_eq(create_polynomial(&result), SUCCESS);

	// Заполнение полиномов
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 3), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 4), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 5), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 6), SUCCESS);
	p1->degree = 3;

	ck_assert_int_eq(push_node_end(&(p2->coefficients), 3), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p2->coefficients), 4), SUCCESS);
	p2->degree = 1;

	// Композиция полиномов
	ck_assert_int_eq(composition_polynomials(&result, p1, p2), SUCCESS);

	// Проверка результата
	ck_assert_int_eq(result->degree, 3);
	ck_assert_int_eq(result->coefficients->data, 81);
	ck_assert_int_eq(result->coefficients->next->data, 360);
	ck_assert_int_eq(result->coefficients->next->next->data, 543);
	ck_assert_int_eq(result->coefficients->next->next->next->data, 282);

	// Освобождение памяти
	destroy_polynomial(&p1);
	destroy_polynomial(&p2);
	destroy_polynomial(&result);
}
END_TEST

START_TEST(test_diff_polynomial)
{
	Polynomial* p1;
	Polynomial* result;

	// Создание полинома
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);
	ck_assert_int_eq(create_polynomial(&result), SUCCESS);

	// Заполнение полинома
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 2), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	p1->degree = 2;

	// Дифференцирование полинома
	ck_assert_int_eq(diff_polynomial(&result, p1, 1), SUCCESS);

	// Проверка результата
	ck_assert_int_eq(result->degree, 1);
	ck_assert_int_eq(result->coefficients->data, 2);
	ck_assert_int_eq(result->coefficients->next->data, 2);

	// Освобождение памяти
	destroy_polynomial(&p1);
	destroy_polynomial(&result);
}
END_TEST


START_TEST(test_eval_polynomial)
{
	Polynomial* p1;

	// Создание полинома
	ck_assert_int_eq(create_polynomial(&p1), SUCCESS);

	// Заполнение полинома
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 2), SUCCESS);
	ck_assert_int_eq(push_node_end(&(p1->coefficients), 1), SUCCESS);
	p1->degree = 2;

	// Вычисление значения полинома
	int value = eval_polynomial(p1, 2);

	// Проверка результата
	ck_assert_int_eq(value, 9);

	// Освобождение памяти
	destroy_polynomial(&p1);
}
END_TEST

// Создание набора тестов
Suite* polynomial_suite(void) {
	Suite* s;
	TCase* tc_core;

	s = suite_create("Polynomial");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_add_polynomials);
	tcase_add_test(tc_core, test_subtract_polynomials);
	tcase_add_test(tc_core, test_product_polynomials);
	tcase_add_test(tc_core, test_divide_polynomials);
	tcase_add_test(tc_core, test_composition_polynomials);
	tcase_add_test(tc_core, test_diff_polynomial);
	tcase_add_test(tc_core, test_eval_polynomial);



	suite_add_tcase(s, tc_core);

	return s;
}

// Основная функция для запуска тестов
int main(void) {
	int number_failed;
	Suite* s;
	SRunner* sr;

	s = polynomial_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}