#include "person.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#ifndef EX2_VERSION2_MAINEX_H
#define EX2_VERSION2_MAINEX_H

#define max(a, b)  a > b ? a : b
#define sr(per) (per.marks[0] + per.marks[1] + per.marks[2] + per.marks[3] + per.marks[4] + per.marks[5] + per.marks[6]) / 7

double maxMeanMark(const char * filename){
    FILE *f = fopen(filename, "r");
    Person per;
    double MAxMeanMark = 0;
    while(fread(&per, sizeof(per), 1, f)){
        MAxMeanMark = max(MAxMeanMark, sr(per));
    }
    fclose(f);
    return MAxMeanMark;
}


int group(const char * filename){
    FILE *f = fopen(filename, "r");
    double maxMark = maxMeanMark(filename);
    Person per;
    int group[16] = {0};
    while(fread(&per, sizeof(per), 1, f)){
        if(strcmp(per.sex, "woman") && sr(per) == maxMark){
            group[per.number_group -= 1] += 1;
        }
    }
    fclose(f);
    int gr = -1, maxm = INT_MIN;
    for(int  i = 0; i < 16; ++i){
        printf("%d ", group[i]);
        if(group[i] > maxm){
            gr = i + 1;
            maxm = group[i];
        }
    }
    putchar('\n');
    return gr;

}
#endif //EX2_VERSION2_MAINEX_H
