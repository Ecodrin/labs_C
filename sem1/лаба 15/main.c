#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b){
    if (a <= b) return a;
    return b;
}

int ma1in() {
    char filename[256];
    printf("%s", "Введите имя файла: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    int n, minc = INT_MAX;
    fscanf(f, "%d", &n);
    //printf("%d", n);
    int **matrix = (int**)malloc(sizeof(int*) * n);
    int *sum_column = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n;++i){
        *(matrix + i) = (int*)malloc(sizeof(int) * n);
        for(int j = 0; j < n;++j){
            fscanf(f,"%d", (*(matrix + i) + j));
            minc = min(minc, *(*(matrix + i) + j));
        }
    }
    for(int i = 0; i < n;++i){
        long sum = 0;
        for(int j = 0; j < n; ++j){
            sum += *(*(matrix + j) + i);
        }
        *(sum_column + i) = sum;
    }
    for(int i = 0;i < n;++i){
        for(int j = 0; j < n;++j){
            if(*(*(matrix + i) + j) == minc){
                *(*(matrix + i) + j) = *(sum_column + j);
            }
            printf("%d ", *(*(matrix + i) + j));
        }
        putchar('\n');
    }
    for (int i = 0; i < n; ++i) {
        free(*(matrix + i));
    }

    free(matrix);
    fclose(f);
    return 0;
}
