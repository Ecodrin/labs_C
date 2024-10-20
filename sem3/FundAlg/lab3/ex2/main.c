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
