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
// Para guardar valores si dos thread comparten la misma fila
long sumaXAux[N][MAX_THREADS], sumaX2Aux[N][MAX_THREADS], sumaXYAux[N][MAX_THREADS];
double *A, *B;
int rangos[MAX_THREADS];

void * parallel_code(void * args){
    int index = *((int *) args);
    
    int ini_elem = rangos[index];
    int fin_elem = rangos[index+1] - 1;
    int nElems = fin_elem - ini_elem;

    int iAux_ini = ini_elem/nn;
    int jAux_ini = ini_elem % nn; // 0

    int iAux_fin = fin_elem/nn;
    int jAux_fin = fin_elem % nn; // 3

    if (iAux_ini == iAux_fin){
        int i = iAux_ini;
        for(int j = jAux_ini; j <= jAux_fin; j++){
            sumaXAux[i][index] += X[i][j];
            sumaX2Aux[i][index] += X[i][j] * X[i][j];
            sumaXYAux[i][index] += X[i][j] * Y[j];
        }
    } else{
        //Primera fila
        int i = iAux_ini;
        for(int j = jAux_ini; j <= nn; j++){
            //calculas para i = iAux_ini
            sumaXAux[i][index] += X[i][j];
            sumaX2Aux[i][index] += X[i][j] * X[i][j];
            sumaXYAux[i][index] += X[i][j] * Y[j];
        }

        for(int i = iAux_ini + 1; i < iAux_fin; i++){
            for(int j = 0; j <= nn; j++){
                //calculas
                // No hace falta usar las variables auxiliares porque se calcula la fila entera
                sumaX[i] += X[i][j];
                sumaX2[i] += X[i][j] * X[i][j];
                sumaXY[i] += X[i][j] * Y[j];
            }
        }
        i = iAux_fin;
        //ultima fila
        for(int j = 0; j <= jAux_fin; j++){
            //calculas para i = iAux_fin
            sumaXAux[i][index] += X[i][j];
            sumaX2Aux[i][index] += X[i][j] * X[i][j];
            sumaXYAux[i][index] += X[i][j] * Y[j];
        }
    }

    pthread_exit(0);
}

int main(int np, char*p[])
{
    int i,j;
    double sA,sB;
    clock_t ta,t;
    int porcion, resto, result_code;
    pthread_t threads[MAX_THREADS];

    assert(np==3);

    nn = atoi(p[1]);
    assert(nn<=N);
    srand(1);

    numThreads = atoi(p[2]);
    assert(numThreads >= 2 && numThreads <= MAX_THREADS);

    printf("Dimensio dades =~ %g Mbytes\n",((double)(nn*(nn+11))*4)/(1024*1024)); 

    memset(rangos,0,numThreads*sizeof(int));
    memset(sumaXAux,0,MAX_THREADS*N*sizeof(int));
    memset(sumaX2Aux,0,MAX_THREADS*N*sizeof(int));
    memset(sumaXYAux,0,MAX_THREADS*N*sizeof(int));

    //creacio matrius i vectors
    apX = calloc(nn*nn,sizeof(int)); assert (apX);
    Y = calloc(nn,sizeof(int)); assert (Y);
    sumaX = calloc(nn,sizeof(long)); assert (sumaX);
    sumaX2 = calloc(nn,sizeof(long)); assert (sumaX2);
    sumaXY = calloc(nn,sizeof(long)); assert (sumaXY);
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
    
    // Càlcul de la porció
    porcion = nn*nn/numThreads;
    // Resto sobra dels primers
    resto = nn*nn % numThreads;

    if(resto != 0){
        for (int i = 0; i < numThreads; i++)
        {
            rangos[i] = rangos[i-1] + porcion;
            if(i < resto){
                rangos[i]++;
            }
        }
    }else{
        for (int i = 1; i < numThreads; i++)
        {
            rangos[i] = rangos[i-1] + porcion;
        }
    }

    // calcul de sumatoris
    /*sumaY = 0;
    for (i=0;i<nn;i++) {
	sumaX[i] = sumaX2[i] = sumaXY[i] = 0;
        for (j=0;j<nn;j++) {
		sumaX[i] += X[i][j];
		sumaX2[i] += X[i][j] * X[i][j];
		sumaXY[i] += X[i][j] * Y[j];
	}
	sumaY += Y[i];
    }*/
    sumaY = 0;

    for (int i = 0; i < nn; i++)
    {
        sumaX[i] = sumaX2[i] = sumaXY[i] = 0;
    }

    int indexArray[MAX_THREADS];

    for (int i = 0; i < numThreads; i++)
    {
        indexArray[i] = i;
        result_code = pthread_create(&threads[i], NULL, parallel_code, (void *) &indexArray[i]);
        assert(!result_code);
    }

    for (int i = 0; i < nn; i++)
    {
        sumaY += Y[i];
    }

    for(int i = 0; i < numThreads; i++)
    {
        result_code = pthread_join(threads[i], NULL );
        assert(!result_code);
    }
    
    for (int i = 0; i < nn; i++)
    {
        for (int j = 0; j < numThreads; j++)
        {
            sumaX[i] += sumaXAux[i][j];
            sumaX2[i] += sumaX2Aux[i][j];
            sumaXY[i] += sumaXYAux[i][j];
        }
    }
    for (int i = 0; i < nn; i++){
        printf("%d, ", sumaX[i]);
    }
    printf("\n");
    for (int i = 0; i < nn; i++){
        printf("%d, ", Y[i]);
    }
    printf("\n");
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
            printf("%f, %f\n",sA,sB);
	    sA += A[i];
	    sB += B[i];
    }
    for (int i = 0; i < nn; i++){
        printf("%d, ", A[i]);
    }
    printf("\n");
    for (int i = 0; i < nn; i++){
        printf("%d, ", B[i]);
    }
    printf("Suma elements de A: %lg B:%lg\n",sA,sB);

exit(0);
}
