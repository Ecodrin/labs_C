#include <stdio.h>
#include <string.h>

#include "person.h"
#include "person_dump_print.h"
#include "mainEx.h"

int main(int argc, char* argv[]) {
    /*
        "-f" - распечатка файла
        "-l" - загрузка файла( лучше использовать "make l")
     */

    if(argc == 3){
        if(strcmp(argv[1], "-f") == 0){
            print(argv[2]);
        }
        else if(strcmp(argv[1], "-d") == 0){
            dumps(argv[2]);
        }
        else if(strcmp(argv[1], "-p") == 0){     //// Основной абзац
            printf("Группа с максимальным количеством студентов: %d\n", group(argv[2]));

        }
        else{
            printf("Непонятный флаг\n");
        }
    }
    else{
        printf("Непонятное число агрументов(верно 3)\n");
    }
    return 0;
}
