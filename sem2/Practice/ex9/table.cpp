#include "table.h"

/*
    Метод простой вставки.
    Тип ключа: комбинированный (строка + целое)
    Длина ключа в байтах: 32
    Хранение данных и ключей: вмeсте
    мин число: 18
*/


Table::~Table() {
    delete [] keys;
}

Table::Table() {
    this->len = 10;
    this->depth = 0;
    keys = new Key[10];
}


void Table::add(FILE * f) {
    Key key;
    while(fscanf(f, "%s %lu %50[^\n]", key.key_1, &key.key_2, key.data) == 3){
        if (depth == len){
            Key * new_keys = new Key[len + 10];
            len += 10;
            for (int i = 0; i < depth; ++i){
                new_keys[i] = keys[i];
            }
            delete []keys;
            keys = new_keys;
        }
        keys[depth] = key;
        depth += 1;
    }
}




void Table::print() const {
    for (int i = 0; i < depth; ++i){
        std::cout << keys[i].key_1 << ' ' << keys[i].key_2 << ' ' << keys[i].data << '\n';
    }
}

void Table::swap(Key *a, Key *b) {
    Key *c = a;
    a = b;
    b = c;
}

void Table::sort() {
    int i, j;
    Key x;
    for(i = 1; i < depth; ++i){
       x = keys[i];
       j = i;
       while(better_string(keys[j - 1].data, x.data) && j > 0 ){
           keys[j] = keys[j-1];
           j--;
       }
       keys[j] = x;
    }
}

int Table::better_string(char * s1, char * s2) {
    for(int i = 0; s1[i] != '\0' && s2[i] != '\0'; ++i){
        if (s1[i] > s2[i])
            return 1;
        if(s1[i] < s2[i])
            return 0;
    }
    return 0;
}


