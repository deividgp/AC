#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define N 2000

int A[N][N],B[N][N],C[N][N];
int nn;

int main(int np, char*p[])
{
    int i,j,k;
    long long s;
    float total;
    clock_t start_t, end_t, total_t;
    assert(np==2);

    nn = atoi(p[1]);
    assert(nn<=N);
    srand(1);

    printf("Dimensio matrius %d\n",nn);
    memset(C,0,nn*nn*sizeof(int));
    
    start_t = clock();

    for (i=0;i<nn;i++) {
        for (j=0;j<nn;j++)            
            A[i][j]=(rand()%10 <= 8? rand()%100+1:0);
        for (j=0;j<nn;j++)            
            B[i][j]=rand()%100 +1 ;
    }

    end_t = clock();
    total_t = (end_t - start_t);
    total = (float)total_t/1000000;
    printf("\nTiempo primer bucle: %f\n", total  );

    start_t = clock();

#pragma omp parallel for private(j,k)
    for (i=0;i<nn;i++)
        for (j=0;j<nn;j++)
            for (k=0;k<nn;k++)
            	C[i][j] += A[i][k] * B[k][j];

    end_t = clock();
    total_t = end_t - start_t;
    total = (float)total_t/1000000;
    printf("\nTiempo segundo bucle: %f\n", total  );

    start_t = clock();

    s=0;
    for (i=0;i<nn;i++)
        for (j=0;j<nn;j++) s+= C[i][j];
    
    end_t = clock();
    total_t = end_t - start_t;
    total = (float)total_t/1000000;
    printf("\nTiempo tercer bucle: %f\n", total  );

    printf("Suma elements de C:  %lld\n",s);

exit(0);
}
