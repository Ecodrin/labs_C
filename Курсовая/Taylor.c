#include <stdio.h>
#include <math.h>

int main() {
    
    double a = 0.1, b = 0.6, epsilon = 1.0;
    int n, k;
    long double x = a;
    printf("%s", "Введите количество разбиений n и значение k, нужное для определения точности ");
    scanf("%d %d", &n, &k);
    while (1.0 + epsilon / 2 > 1.0){
        epsilon = epsilon / 2.0;
    }
    printf("\nМашинное эпсилон равно: %.20f \n\n", epsilon);
    printf("======================================================================================================\n");
    printf("|  x  |   \t Значение ряда\t    |\t   Значение функции\t  | IT |  \t Разница\t     |\n");
    printf("======================================================================================================\n");
    for(int i = 0; i <= n; ++i){
        int count_iteration = 1;
        long double sum = expl(2.0 * x), sum_r = 1.0, sum_last = 1.0;
        while(count_iteration < 100 && fabsl(sum - sum_r) >= epsilon * k){
            sum_r = sum_r + sum_last * (2 * x) / count_iteration;
            sum_last = sum_last * (2 * x) / count_iteration;
            ++count_iteration;
        }
        printf("|%.2Lf | %.25Lf | %.25Lf | %d | %.25Lf |\n", x, sum_r, sum, count_iteration, sum - sum_r);
        x += (b - a) / n;
    }

    printf("======================================================================================================\n");
    return 0;
}

