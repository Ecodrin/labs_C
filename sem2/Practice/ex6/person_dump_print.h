#include "person.h"
#include <errno.h>
// Created by matvey on 3/13/24.
//

#ifndef EX2_VERSION2_PERSON_DUMP_H
#define EX2_VERSION2_PERSON_DUMP_H

int readPerson(Person *p){
    return scanf("%d %s %s %s %d %d %d %d %d %d %d %d", &p->id, p->name, p->initials, p->sex, &p->number_group,
                 &p->marks[0], &p->marks[1], &p->marks[2], &p->marks[3], &p->marks[4], &p->marks[5],
                 &p->marks[6]) == 12;
}

void dumps(const char* filename){
    FILE *f = fopen(filename, "w");
    Person per;
    while(readPerson(&per)){
        fwrite(&per, sizeof(per), 1, f);
    }
    fclose(f);
}


void print(const char* filename){
    FILE *f = fopen(filename, "r");
    if(!f){
        perror("Ошибка открытия(файла нет)");
    }
    Person p;
    while(fread(&p, sizeof(p), 1, f) == 1){
        printf("%3d %15s %15s %5s %2d %d %d %d %d %d %d %d\n", p.id, p.name, p.initials, p.sex, p.number_group,
              p.marks[0], p.marks[1], p.marks[2], p.marks[3], p.marks[4], p.marks[5],
              p.marks[6]);
    }
    fclose(f);
}
#endif //EX2_VERSION2_PERSON_DUMP_H
