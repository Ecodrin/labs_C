
#ifndef EX9_TABLE_H
#define EX9_TABLE_H

#include <iostream>

struct Key{
    char key_1[16];
    unsigned long key_2;
    char data[50];
};


class Table{
private:
    static void swap(Key *, Key*);
    static int better_string(char *, char *);
public:
    Key *keys;
    int depth;
    int len;
    Table();
    ~Table();
    void add(FILE *);
    void print() const;
    void sort();
};



#endif


