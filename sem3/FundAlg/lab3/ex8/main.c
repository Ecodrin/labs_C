#include "ex8.h"

int main() {
	Polynomial* polynomial;
	error_msg errorMsg;
	String s1;
	create_string(&s1, "3x^3+6x^2-12x-9");
	errorMsg = read_polynomial_from_string(&polynomial, &s1);
	if(errorMsg){
		return print_error(errorMsg);
	}
	printf("|%d|\n", polynomial->degree);
	destroy_string(&s1);
	print_LinkedList(stdout, polynomial->coefficients, " ");
	putc('\n', stdout);

	Polynomial *polynomial2;
	create_string(&s1, "2x^2+5x+6");
	errorMsg = read_polynomial_from_string(&polynomial2, &s1);
	printf("|%d|\n", polynomial2->degree);
	destroy_string(&s1);
	if (errorMsg) {
		destroy_string(&s1);
		destroy_polynomial(polynomial);
		return print_error(errorMsg);
	}
	print_LinkedList(stdout, polynomial2->coefficients, " ");
	putc('\n', stdout);

	Polynomial *p;
	errorMsg = composition_polynomials( &p, polynomial, polynomial2);
	if(errorMsg) {
		destroy_polynomial(polynomial);
		destroy_polynomial(polynomial2);
		return print_error(errorMsg);
	}
	print_polynomial(stdout, p);
	destroy_polynomial(polynomial);
	destroy_polynomial(polynomial2);
	destroy_polynomial(p);

}