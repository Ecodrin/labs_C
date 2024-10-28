#include "test.h"

int main(){
	double *res;
	error_msg errorMsg = DecompositionPolynomial(1e-4, 3, &res, 4, -2.0, 1.0, -3.0, 0.0, 1.0);
	if(errorMsg) return print_error(errorMsg);
	for(int i = 0; i < 5;++i){
		printf("%f ", res[i]);
	}

}