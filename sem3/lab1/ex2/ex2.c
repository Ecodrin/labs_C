#include "ex2.h"

#include <stdio.h>
#include <math.h>

double fac(int num){
    double f = 1;
    for(int i = 2; i <= num; ++i){
        f *= i;
    }
    return f;
}


// Общий метод поиска предeла
double calculate_limit(void(*func)(int *, double *), double value, double last_value, double eps, int first_n){
    int i = first_n;  
    do{
        last_value = value;
        // Ищем предел для конкретного значения i
        func(&i, &value);
        // printf("value: %f last value: %f\n", value, last_value);
    }while(fabs(value - last_value)>= eps);
    return value;
}

// Общий метод вычисления ряда
double calculate_sequence(double(*func)(int n), double value, double eps, int n){
    double precision = 1.0;
    while(fabs(precision) >= eps){
        precision = func(n);
        // printf("%f %\n", value);
        value += precision;
        n += 1;
    }
    return value;
}

// Общий метод дихотомии
double calculate_dichotomy(double(*func)(double x), double a, double b, double eps){
    while (fabsl(a - b) >= eps){
        if(func(a) * func((a + b) / 2) > 0){
            a = (a + b) / 2;
        }
        else if(func(b) * func((a + b) / 2) > 0){
            b = (a + b) / 2;
        }
    }
    return (a + b) / 2;
    return (a + b) / 2;
}

// Общий метод итерации
double calculate_simple_iteration(double(*func)(double x), double(*func_eqvivalent)(double x, double lambda), double a, double b,double lambda, double eps){
    double last_value = (a + b) / 2;
    double value = func_eqvivalent(last_value, lambda);
    while(fabs(func(value)) >= eps / 10000){
        last_value = value;
        value = func_eqvivalent(last_value, lambda);   
    }
    return value;
}

// Вычисление предела e
void limit_e(int* n, double* value){
    *value = (1 + 1.0 / *n);
    for(int j = 2; j <= *n; ++j){
        *value *= (1 + 1.0 / *n);
    }
    *n *= 2;
}


double calculate_e_limit(double eps) {
    return calculate_limit(limit_e, 2, 2, eps, 2);
}

// Вычисление значения функции ln(x) = 1
double ln1(double x){
    return log(x) - 1;
}

double calculate_e_dichotomy(double eps){
    return calculate_dichotomy(ln1, 1, 4, eps);
}

double e_sequence(int n){
    return 1.0 / fac(n);
}

double calculate_e_sequence(double eps){
    return calculate_sequence(e_sequence, 0, eps, 0);
}




void lim_pi(int *n, double * value){
    double pow24 = 2;
    for(int i = 2; i <= *n *4; ++i){
        pow24 *= 2;
    }
    double num = fac(*n) * fac(*n) * pow24;
    // printf("Num:%f\n", num);
    double den = *n;
    for(int i = *n + 1; i <= (*n) * 2; ++i){
        den *= i * i;
    }
    *value = num / den;
    
    // printf("%f\n", *value);
    *n += 1;
}

double calculate_pi_limit(double eps){
    return calculate_limit(lim_pi, 0, 0, eps, 1);
}

double seq_pi(int n){
    return (4.0 * (((n - 1) % 2 == 0) ? 1.0 : -1.0) / (2.0 * n - 1.0));
}

double calculate_pi_sequence(double eps){
    return calculate_sequence(seq_pi, 0, eps, 1);
}

double eqv_simple_it_pi(double x, double lambda){
    return x + lambda * (cos(x) + 1);
}

double simple_it_pi(double x){
    return cos(x) + 1; 
}

double calculate_pi_simple_iteration(double eps){
    return calculate_simple_iteration(simple_it_pi, eqv_simple_it_pi, 1, 5, 0.5, eps);
}
