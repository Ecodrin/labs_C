#include "test.h"


START_TEST(test_task2_1){
	error_msg errorMsg;
	int n = 3;
	Vector v1 = {n, (double[]){1.0, 2.0, 3.0}};
	Vector v2 = {n, (double[]){4.0, 5.0, 6.0}};
	Vector v3 = {n, (double[]){7.0, 8.0, 9.0}};
	double A[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = (i == j) ? 1.0 : 0.0;  // Пример единичной матрицы
		}
	}
	int count_vectors = 3;
	int count_norms = 3;
    int p = 2;
	ArrayVectors ** vectors = NULL;
	errorMsg = MaxVectors(vectors, n, count_vectors, count_norms, v1, v2, v3, norm1, norm2, p, norm3, A);
	ck_assert_int_eq(errorMsg, SUCCESS);
    for(int i = 0; i < count_norms; ++i){
		destroy_array_vector(vectors[i]);
	}
	free(vectors);

}
END_TEST

Suite *ex2_quite() {
    Suite *s;
    s = suite_create("ex2");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_task2_1);

    suite_add_tcase(s, tc_core);
    return s;
}


#include "test.h"


int main(){
	int number_failed;
	Suite * s = ex2_quite();
	SRunner *sr;
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0 : 1;
}
