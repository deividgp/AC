#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#define N 50000
#define MAX_THREADS 256

int nn, numThreads;
int *X[N+1],*apX, *Y;
long long *sumaX, *sumaX2, sumaY, *sumaXY;
double *A, *B;
int rang[MAX_THREADS];
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
// Versió lenta
//int visitedRows[N];

void * parallel_code(void * args){
    int index = (*(int*)args);
    int i, j, ini;
    // Versió lenta
    int row, col;

    if(index == 0)
        ini = 0;
    else
        ini = rang[index-1];
    
    for(i=ini; i<rang[index]; i++){
        // Versió ràpida
        for (j=0;j<nn;j++) {
            sumaX[i] += X[i][j];
            sumaX2[i] += X[i][j] * X[i][j];
            sumaXY[i] += X[i][j] * Y[j];
        }
        pthread_mutex_lock(&mutex);
        sumaY += Y[i];
        pthread_mutex_unlock(&mutex);

        // Versió lenta
        /*row = i/nn;
        col = i%nn;
        sumaX[row] += X[row][col];
        sumaX2[row] += X[row][col] * X[row][col];
        sumaXY[row] += X[row][col] * Y[col];
        
        pthread_mutex_lock(&mutex);
        if(visitedRows[row] == 0){
            visitedRows[row] = 1;
            sumaY += Y[row];
            pthread_mutex_unlock(&mutex);
        }else{
            pthread_mutex_unlock(&mutex);
        }*/
    }
    pthread_exit(0);
}

int main(int np, char*p[])
{
    int i,j,index;
    double sA,sB;
    unsigned int thread_args[MAX_THREADS];
    pthread_t threads[MAX_THREADS];

    assert(np==3);

    nn = atoi(p[1]);
    assert(nn<=N);
    srand(1);

    numThreads = atoi(p[2]);
    assert(numThreads >= 2 && numThreads <= MAX_THREADS);

    printf("Dimensio dades =~ %g Mbytes\n",((double)(nn*(nn+11))*4)/(1024*1024)); 

    memset(rang,0,numThreads*sizeof(int));
    // Versió lenta
    //memset(visitedRows,0,nn*sizeof(int));

    apX = calloc(nn*nn,sizeof(int)); assert (apX);
    Y = calloc(nn,sizeof(int)); assert (Y);
    sumaX = calloc(nn,sizeof(long long)); assert (sumaX);
    sumaX2 = calloc(nn,sizeof(long long)); assert (sumaX2);
    sumaXY = calloc(nn,sizeof(long long)); assert (sumaXY);
    A = calloc(nn,sizeof(double)); assert (A);
    B = calloc(nn,sizeof(double)); assert (B);
    // Inicialitzacio
    X[0] = apX;
    for (i=0;i<nn;i++) {
        for (j=0;j<nn;j+=8)            
            X[i][j]=rand()%100+1;
        Y[i]=rand()%100 - 49;
	X[i+1] = X[i] + nn;
    }

    // Versió ràpida
    int porcio = nn/numThreads;
    int mod = nn % numThreads;

    // Versió lenta
    //int porcio = nn*nn/numThreads;
    //int mod = nn*nn % numThreads;
    
    for(i=0; i<numThreads; i++){
        rang[i] = porcio;
        if (i != 0) rang[i] += rang[i-1];
        if (i < mod) rang[i]++;
    }
    
    sumaY = 0;
    pthread_mutex_init(&mutex, NULL);
    for (index = 0; index < numThreads; index++)
    {
        thread_args[index] = index;
        assert(!pthread_create(&threads[index], NULL, parallel_code, &thread_args[index]));
    }

    for(index = 0; index < numThreads; index++)
    {
        assert(!pthread_join(threads[index], NULL ));
    }
    pthread_mutex_destroy(&mutex);

    for (i=0;i<nn;i++) {
	B[i] = sumaXY[i] - (sumaX[i] * sumaY)/nn;
	B[i] = B[i] / (sumaX2[i] - (sumaX[i] * sumaX[i])/nn);
	A[i] = (sumaY -B[i]*sumaX[i])/nn;
    }

    // check
    sA = sB = 0;
    for (i=0;i<nn;i++) {
            //printf("%f, %f\n",sA,sB);
	    sA += A[i];
	    sB += B[i];
    }
    printf("Suma elements de A: %lg B:%lg\n",sA,sB);

exit(0);
}
