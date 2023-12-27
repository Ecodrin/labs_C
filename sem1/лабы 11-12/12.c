#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int mod(int a, int b){
    return a - a / b * b;
}


int max_step(long a){
    int k = 0;
    while (a / 10 > 0){
        ++k;
        a = a / 10;
    }
    if (mod(a, 10) > 0)
        ++k;
    return k;
}


long step_10(int a, int b){
    long x = 1;
    for(int j = 0; j < a; ++j){
        x *= 10;
    }
    return x;
}

int main(){
    fflush(stdin);
    char s;
    int fl = 0, fld = 0;
    int number;
    printf("%s", "Введите числа, раздленные разделителями: ");
    while((s = getchar()) != EOF){
        if((s == ' ' | s == '\n' | s == '\t') && fl > 0){

            int step = max_step(number);
            number = number / (step_10(step - 1, 10)) * (step_10(step - 2, 10)) + mod(number, step_10(step - 2, 10));
            if (abs(number) >= 1000)
                number = number / 1000 * 100 + mod(number, 100);
            else
                number = number / 100 * 10 + mod(number, 10);
            if(fld == 0)
                printf("%d%c", number, s);
            else
                printf("%d%c", -number, s);
            if (s == '\n')
                printf("%s", "Введите числа, раздленные разделителями: ");
            fld = 0;
            fl = 0;
        }
        else if(isdigit(s)){
            if(fl == 0){
                fl = 1;
                number = s - '0';
            }
            else if(fl == 1){
                number = number * 10 + (s - '0');
            }
        }
        else if(s == '-' && fl == 0)
            fld = 1;
        else if(s == '\n')
            printf("\n%s", "Введите числа, раздленные разделителями: ");
    }
}