#include "table.h"

/*
    Метод простой вставки.
    Тип ключа: комбинированный (строка + целое)
    Длина ключа в байтах: 32
    Хранение данных и ключей: вмксте
    мин число: 18
*/


int main(int argc, char* argv[]) {
    Table table;
    FILE * f = std::fopen(argv[1], "r");
    table.add(f);
    table.sort();
    table.print();
    std::fclose(f);
    return 0;
}
