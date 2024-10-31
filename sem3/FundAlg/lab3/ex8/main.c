#include "ex8.h"


int main(){
	Polynomial* polynomial;
	error_msg errorMsg = create_polynomial(&polynomial);
	if(errorMsg){
		return print_error(errorMsg);
	}
	String s;
	create_string(&s, "x^2 - 2x + 3x^4 - 123x^7 + 7 - 9 +123x^8");
	errorMsg = read_polynomial_from_string(polynomial, &s);
	if(errorMsg){
		destroy_string(&s);
		return print_error(errorMsg);
	}
	print_LinkedList(stdout, polynomial->coefficients, " ");
	destroy_polynomial(polynomial);
	destroy_string(&s);
}