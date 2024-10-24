#include "test.h"

START_TEST(test_from10to_1) {
    error_msg errorMsg;
    char result[100];
    errorMsg = From10To(123, 10, result);
    ck_assert_int_eq(errorMsg, INCORRECT_OPTIONS_ERROR);
}

END_TEST

START_TEST(test_from10to_2) {
    error_msg errorMsg;
    char result[100];

    errorMsg = From10To(1234, -2, result);
    ck_assert_int_eq(errorMsg, INCORRECT_OPTIONS_ERROR);

    errorMsg = From10To(1234, 8, result);
    ck_assert_int_eq(errorMsg, SUCCESS);
    ck_assert_str_eq(result, "2322");
}

START_TEST(test_from10to_3) {
    error_msg errorMsg;
    char result[100];
    errorMsg = From10To(1234, 8, result);
    ck_assert_int_eq(errorMsg, SUCCESS);
    ck_assert_str_eq(result, "2322");
}

END_TEST

START_TEST(test_from10to_4) {
    error_msg errorMsg;
    char result[100];
    errorMsg = From10To(1234, 16, result);
    ck_assert_int_eq(errorMsg, SUCCESS);
    ck_assert_str_eq(result, "4d2");
}

END_TEST


START_TEST(test_from10to_5) {
    error_msg errorMsg;
    char result[100];
    errorMsg = From10To(-1234, 16, result);
    ck_assert_int_eq(errorMsg, SUCCESS);
    ck_assert_str_eq(result, "-4d2");
}

END_TEST


START_TEST(test_from10to_6) {
    error_msg errorMsg;
    char result[100];
    errorMsg = From10To(2321454, 32, result);
    ck_assert_int_eq(errorMsg, SUCCESS);
    ck_assert_str_eq(result, "26r1e");
}

END_TEST

Suite *ex1_quite() {
    Suite *s;
    s = suite_create("ex1");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from10to_1);

    tcase_add_test(tc_core, test_from10to_2);

    tcase_add_test(tc_core, test_from10to_3);

    tcase_add_test(tc_core, test_from10to_4);

    tcase_add_test(tc_core, test_from10to_5);

    tcase_add_test(tc_core, test_from10to_6);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(){
	int number_failed;
	Suite * s = ex1_quite();
	SRunner *sr;
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0 : 1;
}