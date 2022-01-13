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
long *sumaX, *sumaX2, sumaY, *sumaXY;
double *A, *B;
int rangos[MAX_THREADS];
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
int ret;

void * parallel_code(void * id){
    int index = (intptr_t) id;
    int i, ini, fil, col;
    int filAux = -5;
    int maxFil = 0, maxCol = 0;

    if(index == 0)
        ini = 0;
    else
        ini = rangos[index-1];

    for(i=ini; i<rangos[index]; i++){
        fil = i/nn;
        col = i%nn;
        if(fil > maxFil){
            maxFil = fil;
        }
        if(col > maxCol){
            maxCol = col;
        }
        /*printf("fil: %d \n", fil);
        printf("col: %d \n", col);*/
        sumaX[fil] += X[fil][col];
        sumaX2[fil] += X[fil][col] * X[fil][col];
        sumaXY[fil] += X[fil][col] * Y[col];

        pthread_mutex_lock(&mutex);
        if(filAux != fil){
            sumaY += Y[fil];
            filAux = fil;
            pthread_mutex_unlock(&mutex);
        }else{
            pthread_mutex_unlock(&mutex);
        }
    }
    printf("MaxFil: %d", maxFil);
    printf("MaxCol: %d", maxCol);
    pthread_exit(0);
}

int main(int np, char*p[])
{
    int i,j;
    double sA,sB;
    clock_t ta,t;
    pthread_t threads[MAX_THREADS];

    assert(np==3);

    nn = atoi(p[1]);
    assert(nn<=N);
    srand(1);

    numThreads = atoi(p[2]);
    assert(numThreads >= 2 && numThreads <= MAX_THREADS);

    printf("Dimensio dades =~ %g Mbytes\n",((double)(nn*(nn+11))*4)/(1024*1024)); 

    memset(rangos,0,numThreads*sizeof(int));

    //creacio matrius i vectors
    apX = calloc(nn*nn,sizeof(int)); assert (apX);
    Y = calloc(nn,sizeof(int)); assert (Y);
    sumaX = calloc(nn,sizeof(long long)); assert (sumaX);
    sumaX2 = calloc(nn,sizeof(long long)); assert (sumaX2);
    sumaXY = calloc(nn,sizeof(long long)); assert (sumaXY);
    A = calloc(nn,sizeof(double)); assert (A);
    B = calloc(nn,sizeof(double)); assert (B);

    // Inicialitzacio
    /*X[0] = apX;
    for (i=0;i<nn;i++) {
        for (j=0;j<nn;j+=8)            
            X[i][j]=rand()%100+1;
        Y[i]=rand()%100 - 49;
	X[i+1] = X[i] + nn;
    }*/
    X[0] = apX;
    for (i=0;i<nn;i++) {
        for (j=0;j<nn;j+=8)            
            X[i][j]=90;
        Y[i]=40;
	X[i+1] = X[i] + nn;
    }

    int porcion = nn*nn/numThreads;
    int modul = nn*nn % numThreads;

    if(modul != 0.00){
        modul = modul*numThreads;
        for(i=0; i<modul; i++){
            rangos[i] = rangos[i] + 1;
        }
    }

    rangos[0] = rangos[0] + porcion;
    for(i=1; i<numThreads; i++){
        rangos[i] += rangos[i-1] + porcion;
    }

    sumaY = 0;
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < numThreads; i++)
    {
        assert(!pthread_create(&threads[i], NULL, parallel_code, (void *) (intptr_t)i));
    }

    for(int i = 0; i < numThreads; i++)
    {
        assert(!pthread_join(threads[i], NULL ));
    }
    pthread_mutex_destroy(&mutex);
    // calcul linealitat
    for (i=0;i<nn;i++) {
	B[i] = sumaXY[i] - (sumaX[i] * sumaY)/nn;
	B[i] = B[i] / (sumaX2[i] - (sumaX[i] * sumaX[i])/nn);
	A[i] = (sumaY -B[i]*sumaX[i])/nn;
    }

    // comprovacio
    sA = 0;
    sB = 0;
    for (i=0;i<nn;i++) {
            //printf("%f, %f\n",sA,sB);
	    sA += A[i];
	    sB += B[i];
    }
    printf("Suma elements de A: %lg B:%lg\n",sA,sB);

exit(0);
}
