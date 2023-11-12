#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(){
    char filename1[256], filename2[256];
    printf("%s", "Введите имя файла с данными: ");
    scanf("%s", filename1);
    printf("%s", "Введите имя файла для вывода: ");
    scanf("%s", filename2);
    FILE *f1 = fopen(filename1, "r");
    FILE *f2 = fopen(filename2, "w");
    char c;
    int sost = 0, number;
    while ((c = fgetc(f1)) != EOF){
        if (c == 'i' && sost == 2){
            sost = 3;
        }
        else if(c == 'm' && sost == 1){
            sost = 2;
        }
        else if((c == ' ' | c == '\n' | c == ',' | c == '\t') && sost == 3){
            sost = 0;
            fprintf(f2, "%1.f%s%c", number * 1.609, "km", c);
        }
        else if(isdigit(c)) {
            if (sost == 0) {
                number = c - '0';
                sost = 1;
            }
            else{
                number = number * 10 + (c - '0');
            }
        }
        else if(sost == 1){
            sost = 0;
            fprintf(f2, "%d%c", number, c);
            number = 0;
        }
        else{
            sost = 0;
            number = 0;
            fprintf(f2, "%c", c);
        }
    }
    if(sost == 3)
        fprintf(f2, "%1.f%s", number * 1.609, "km");

    fclose(f1);
    fclose(f2);
}