#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int **matrix = (int**)(malloc(sizeof(int*) * n));
    for(int i = 0; i < n; ++i){
        *(matrix + i) = (int*)(malloc(sizeof(int) * n));
        for(int j = 0; j < n; ++j){
            scanf("%d", (*(matrix + i) + j));
        }
    }
    int column = n - 1, row = n - 1, p = 1, sost = 0, count = n * n;
    while(count > 0){
        printf("%d ", *(*(matrix + row) + column));
        if (sost == 0) {
            ++sost;
            --row;
        }
        else if (sost == 1) {
            column--;
            if(row == column) ++sost;
        }
        else if (sost == 2) {
            ++row;
            if(row == n - 1) ++sost;
        }
        else if (sost == 3) {
            sost++;
            column--;
        }
        else if (sost == 4) {
            --row;
            if(row == column) ++sost;
        }
        else if (sost == 5) {
            ++column;
            if (column == n - 1) sost = 0;
        }


        count--;
    }
    for (int i = 0; i < n; ++i) {
        free(*(matrix + i));
    }

    free(matrix);
    return 0;
}
