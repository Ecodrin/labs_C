#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%d", &matrix[i][j]);
        }
    }
    int count = n * n - 1, p = 0, i = 0, sost = 0;
    while (count >= 0 && i < n * n){
        for(int k = 0; k <= p; ++k){
            ++i;
            printf("%d ", *(*matrix + count));
            //printf("%d %d %d\n",sost, p, *(*matrix + count));
            if(sost == 0){
                count -= n;
                p++;
                break;
            }
            if(sost == 1){
                count -= 1;
            }
            if (sost == 2){
                count += n;
            }
            if(sost == 3){
                count -= 1;
                p++;
                break;
            }
            if(sost == 4){
                count -= n;
            }
            if(sost == 5){
                count++;
            }
            if(k == p - 1) break;
        }
        sost = (sost + 1) % 6;
    }
    return 0;
}
