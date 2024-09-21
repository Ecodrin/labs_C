#include "ex6.h"


int main(int argc, char ** argv){
    double eps;
    double x;
    int mistake = get_value(argc, argv, &eps, &x);
    switch (mistake)
    {
    case 1:    
        printf("Incorrect count work args\n");
        return 1;
    case 2:    
        printf("Mistake in Eps\n");
        return 1;
    default:
        break;
    }
    printf("Интеграл a: %f\n", integral_a(eps));
    printf("Интеграл b: %f\n", integral_b(eps));
    printf("Интеграл c: %f\n", integral_c(eps));
    printf("Интеграл d: %f\n", integral_d(eps));
}