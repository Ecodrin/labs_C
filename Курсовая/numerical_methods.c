#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double machine_epsilon(){
    double epsilon = 1;
    while(1 + epsilon / 2 > 1){
        epsilon /= 2;
    }
    return epsilon;
}

///Функция 20 вариант
long double func1(long double x){
    return 0.1 * x * x - x * logl(x);
}

long double func1_equivalent(long double x){
    return 0.1 * x * x - x * logl(x) + x;
}

long double func1_equivalent_derivative(long double x){
    return 0.2 * x - logl(x);
}

long double derivative1_func1(long double x){
    return 0.2 * x - logl(x) - 1;
}

long double derivative2_func1(long double x){
    return 0.2 - 1 / x;
}
//функция 21 вариант
long double func2(long double x){
    return tanl(x) - 1.0/3.0 * tanl(x) * tanl(x) * tanl(x) + 1.0/5.0 * tanl(x) * tanl(x) * tanl(x) * tanl(x) * tanl(x) - 1.0/3.0;
}

long double func2_equivalent(long double x){
    return tanl(x) - 1.0/3.0 * tanl(x) * tanl(x) * tanl(x) + 1.0/5.0 * tanl(x) * tanl(x) * tanl(x) * tanl(x) * tanl(x) - 1.0/3.0 + x;
}

long double func2_equivalent_derivative(long double x){
    return (cosl(2 * x) * cosl(x) * cosl(x) + sinl(x) * sinl(x) * sinl(x) * sinl(x) + cosl(x) *  cosl(x) *  cosl(x) *  cosl(x) *  cosl(x) *  cosl(x)) /
            (cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x));
}

long double derivative1_func2(long double x){
    return (cosl(2 * x) * cosl(x) * cosl(x) + sinl(x) * sinl(x) * sinl(x) * sinl(x)) /
           (cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x)) ;
}

long double derivative2_func2(long double x){
    return (-2 * cosl(x) * cosl(x) * cosl(x) * sinl(2*x) + 4* cosl(x) * cosl(x) * cosl(2*x)* sinl(x)
    + 4 * sinl(x) * sinl(x) * sinl(x) + 2 * sinl(x) * sinl(x) * sinl(x) * sinl(x) * sinl(x)) /
            (cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x) * cosl(x));
}

void method_dichotomii(long double a, long double b, long double(*func)(long double x)){
    printf("\n\n%s\n", "---------------- Метод дихотомии ----------------");
    long double epsilon = machine_epsilon();
    while (fabsl(a - b) >= epsilon){
        if(func(a) * func((a + b) / 2) > 0){
            a = (a + b) / 2;
        }
        else if(func(b) * func((a + b) / 2) > 0){
            b = (a + b) / 2;
        }
    }
    printf("root:  %.20LF\n", (a + b) / 2);
    printf("value: %.20Lf\n\n", func((a + b) / 2));

}

void method_iterations(long double a, long double b, long double(*func)(long double x),
                       long double(*func_equivalent)(long double x),
                       long double(*func_equivalent_derivative)(long double x)){
    long double x_last, x, p;
    long double epsilon = machine_epsilon();
    x_last = (a + b) / 2;
    x = func_equivalent(x_last);
    printf("\n\n%s\n", "---------------- Метод итераций -----------------");
    if (fabsl(func_equivalent_derivative(x)) >= 1)

        printf("%s", "Ошибка, метод не может быть выполнен\n");
    else{
        while(1) {
            x = func_equivalent(x_last);
            if(fabsl(x - x_last) < epsilon) break;
            x_last = x;
        }
        printf("root:  %.20LF\n", x);
        printf("value: %.20Lf\n\n", func(x));
    }

}


void method_newton(long double a, long double b, long double(*func)(long double x),
                   long double(*derivative1_func)(long double x),
                   long double(*derivative2_func)(long double x)){
    long double x_last, x, p;
    long double epsilon = machine_epsilon();
    printf("\n\n%s\n", "---------------- Метод Ньютона -----------------");
    x_last = (a + b) / 2;
    if (fabsl(func(x_last) * derivative2_func(x_last)) >= (derivative1_func(x_last) * derivative1_func(x_last)))
        printf("%s", "Ошибка, метод не может быть выполнен\n");
    else{
        while(1) {
            x = x_last - func(x_last) / derivative1_func(x_last);
            if(fabsl(x - x_last) < epsilon) break;
            x_last = x;
        }
        printf("root:  %.20LF\n", x);
        printf("value: %.20Lf\n\n", func(x));
    }

}

int main(){
    long double a, b;
    printf("%s", "20 вариант\n");
    printf("%s", "Введите границы отрезка через пробел: ");
    scanf("%Lf %Lf", &a, &b);
    long double epsilon = machine_epsilon(), root = 1.1183;
    printf("\n\n%s\n", "function 0.1x^2 - x * lnx = 0");
    printf("\n\n%s %.20LF\n", "Machine Epsilon: ", epsilon);
    method_dichotomii(1, 2, func1);
    method_iterations(1, 2, func1, func1_equivalent, func1_equivalent_derivative);
    method_newton(1, 2, func1, derivative1_func1, derivative2_func1);
    printf("%s", "21 вариант\n");
    printf("%s", "Введите границы отрезка через пробел: ");
    scanf("%Lf %Lf", &a, &b);
    printf("\n\n%s\n", "tgx - 1/3(tgx)^3 + 1/5(tgx)^5 - 1/3 = 0");
    method_dichotomii(a, b, func2);
    method_iterations(a, b, func2, func2_equivalent, func2_equivalent_derivative);
    method_newton(a, b, func2, derivative1_func2, derivative2_func2);
    return 0;
}