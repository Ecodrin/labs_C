#include "test.h"

START_TEST(task_4_test_1_create) {
	String *s1 = create_string("Hello world");
	ck_assert_str_eq(s1->arr, "Hello world");
	destroy_string(s1);
}
END_TEST

START_TEST(task_4_test_2_copy) {
	String *s1 = create_string("Hello world");
	String *s2 = create_string("aaaaaaaaaaaaaaaaa");
	error_msg errorMsg = mstrcopy(s1, s2, 0, SizeString(s1->arr));
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(s2->arr, "Hello world");
	destroy_string(s1);
	destroy_string(s2);
}
END_TEST


START_TEST(task_4_test_3_eq_1) {
	String *s1 = create_string("Hello world");
	String *s2 = create_string("aaaaaaaaaaaaaaaaa");
	int eq = strings_equals(s1, s2);
	ck_assert_int_eq(eq, 0);
}
END_TEST

START_TEST(task_4_test_3_eq_2) {
	String *s1 = create_string("aaaaaaaaaaaaaaaaa");
	String *s2 = create_string("aaaaaaaaaaaaaaaaa");
	int eq = strings_equals(s1, s2);
	ck_assert_int_eq(eq, 1);
	destroy_string(s1);
	destroy_string(s2);
}
END_TEST

START_TEST(task_4_test_5_copy) {
	String *s1 = create_string("Hello world");
	String *s2;
	error_msg errorMsg = mstrcopynew(s1, &s2);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(s2->arr, "Hello world");
	destroy_string(s1);
	destroy_string(s2);
}
END_TEST

START_TEST(task_4_test_6_cat) {
	String *s1 = create_string("Hello world");
	String *s2 = create_string("aaaaaaaaaaaaaaaaa");
	error_msg errorMsg = mstrcat(s1, s2);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(s1->arr, "Hello worldaaaaaaaaaaaaaaaaa");
}
END_TEST

START_TEST(task_4_test_7_greater_1) {
	String *s1 = create_string("hello world");
	String *s2 = create_string("aaaaaaaaaaaaaaaaa");
	int res = string_greater(s1, s2);
	ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(task_4_test_8_greater_2) {
	String *s1 = create_string("aaaaaaaaaaaaaaaaa");
	String *s2 = create_string("hello world");
	int res = string_greater(s1, s2);
	ck_assert_int_eq(res, -1);
}
END_TEST

START_TEST(task_4_test_9_greater_3) {
	String *s1 = create_string("hello world");
	String *s2 = create_string("hello world");
	int res = string_greater(s1, s2);
	ck_assert_int_eq(res, 0);
}
END_TEST

Suite *ex4_quite() {
	Suite *s;
	s = suite_create("ex1");
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, task_4_test_1_create);
	tcase_add_test(tc_core, task_4_test_2_copy);
	tcase_add_test(tc_core, task_4_test_3_eq_1);
	tcase_add_test(tc_core, task_4_test_3_eq_2);
	tcase_add_test(tc_core, task_4_test_5_copy);
	tcase_add_test(tc_core, task_4_test_6_cat);
	tcase_add_test(tc_core, task_4_test_7_greater_1);
	tcase_add_test(tc_core, task_4_test_8_greater_2);
	tcase_add_test(tc_core, task_4_test_9_greater_3);

	suite_add_tcase(s, tc_core);
	return s;
}



int main() {
	int number_failed;
	Suite *s = ex4_quite();
	SRunner *sr;
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0 : 1;
}