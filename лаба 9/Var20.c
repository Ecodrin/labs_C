#include <stdio.h>

int mod(int a, int b){
    return a - ((a / b) * b);
}

int abs(int n){
    if (n >= 0) return n;
    else return -n;
}

int min(int a, int b){
    if (a <= b) return a;
    else return b;
}
int max(int a, int b){
    if (a >= b) return a;
    else return b;
}
int sign(int a){
    if (a > 0) return 1;
    if (a < 0 ) return -1;
    else return 0;
}
int main(){
    int i0 = -25, j0 = -9, l0 = -14, k = 1, J, I, L;
    while (k <= 51){
        I = mod((abs(i0 - j0) * l0 - abs(j0 - l0) * i0 + abs(i0 - l0) % j0), 20) - k;
        J = mod(min(i0, j0) * max(j0, l0) * min(i0, l0), 25) + 5 * sign(i0) + k;
        L = abs(l0) * sign(i0 - j0) - abs(i0) * sign(j0 - l0) + abs(j0) * sign(i0 - l0);
        i0 = I;
        j0 = J;
        l0 = L;
        if (I + J + 10 <= 0 && I + J + 20 >= 0) {
            printf("Точка попала в нужнуюю область на шаге %d, "
                   "ее координаты (%d%d), параметр движения: %d\n", k, I, J, L);
            break;
        }
        else
            printf("Координаты %d,%d,  параметр движения %d\n", I, J, L);
        ++k;
    }
    return 0;
}