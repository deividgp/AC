#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <stdint.h>

#define N 2000
#define NUM_THREADS 128

int A[N][N],B[N][N],C[N][N];
int nn, numThreads;
int rangos[NUM_THREADS];

void * parallel_code(void * indexp){
    int i, k, ini, fil, col;
    int index = (uintptr_t) indexp;
    if(index == 0)
        ini = 0;
    else
        ini = rangos[index-1];
    for(i=ini; i<rangos[index]; i++){
        fil = i/nn;
        col = i%nn;
        for(k=0; k<nn; k++)
            C[fil][col] += A[fil][k] * B[k][col];
    }
    
    pthread_exit(0);
}


int main(int np, char*p[])
{
    int i,j,k,result_code,index;
    long long s;
    pthread_t threads[NUM_THREADS];

    assert(np==3);

    nn = atoi(p[1]);
    assert(nn<=N);

    numThreads = atoi(p[2]);
    assert(numThreads >= 2 && numThreads <= NUM_THREADS);

    srand(1);

    printf("Dimensio matrius %d\n",nn);
    printf("Num threads %d\n", numThreads);

    memset(C,0,nn*nn*sizeof(int));
    memset(rangos,0,numThreads*sizeof(int));

/**
    Inicialización
**/
    for (i=0;i<nn;i++) {
        for (j=0;j<nn;j++)            
            A[i][j]=(rand()%10 <= 8? rand()%100+1:0);
        for (j=0;j<nn;j++)            
            B[i][j]=rand()%100 +1 ;
    }

/**
    Cálculo de celdas por thread
**/
    float numCeldasf = (float)(nn*nn)/(float)numThreads;  //celdas por Thread
    int numCeldas = numCeldasf;           //parte entera
    float resto = numCeldasf - numCeldas; //parte decimal

    if(resto != 0.00){
        resto = resto*numThreads;   
        for(i=0; i<resto; i++){
            rangos[i] = rangos[i] + 1;
        }
    }

    rangos[0] = rangos[0] + numCeldas;
    for(i=1; i<numThreads; i++){
        rangos[i] += rangos[i-1] + numCeldas;
    }

/**
    Cálculo del producto escalar
**/
    for(index = 0; index < numThreads; index++)
    {
        result_code = pthread_create(&threads[index], NULL, parallel_code, (void *) (uintptr_t) index);
        assert(!result_code);
    }

    for(index = 0; index < numThreads; index++)
    {
        // block until thread 'index' completes
        result_code = pthread_join(threads[index], NULL );
        assert(!result_code);
    }

/**
    Comprobación
**/
    s=0;
    for (i=0;i<nn;i++)
        for (j=0;j<nn;j++) s+= C[i][j];
    
    printf("Suma elements de C:  %lld\n",s);

    exit(0);
}
