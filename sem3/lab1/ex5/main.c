#include "ex5.h"


int main(int argc, char ** argv){
    double eps;
    double x;
    if(get_value(argc, argv, &eps, &x)){
        printf("Incorrect count of work arguments\n");
        return 1;
    }
    printf("Сумма a: %f\n", sum_a(eps, x));
    printf("Сумма b: %f\n", sum_b(eps, x));
    printf("Сумма c: %f\n", sum_c(eps, x));
    printf("Сумма d: %f\n", sum_d(eps, x));
}