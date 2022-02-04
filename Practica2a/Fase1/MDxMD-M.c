#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#define N 10000L
#define ND N*N/100
#define MAX_THREADS 256

int A[N][N],B[N][N],C[N][N],C1[N][N],C2[N][N];
struct {
    int i,j,v;
}AD[ND],BD[ND];
int rang[MAX_THREADS];
int nn,nnD, numThreads;
long long Sum;

void * parallel_code1(void * args){
    int index = (*(int*)args);
    int i, j, ini, k;
    int j_ini, j_fin;

    if(index == 0)
        ini = 0;
    else
        ini = rang[index-1];

    int fin = rang[index];
    int i_ini = ini / nnD;
    int k_ini = ini % nnD;

    int i_fin = fin / nnD;
    int k_fin = fin % nnD;

    //Sparce Matrix X Dense Matrix -> Dense Matrix
    for (i = i_ini; i <= i_fin; i++){
        //Si estoy en la primera fila empiezo en la columna k_ini
        if(i == i_ini) j_ini = k_ini;
        else j_ini = 0;
        //Si estoy en la última fila acabo en la columna K_fin
        if(i == i_fin) j_fin = k_fin;
        else j_fin = nnD;

        for (int aux = j_ini; aux < j_fin; aux++){
            C1[AD[aux].i][i] += AD[aux].v * B[AD[aux].j][i];
        }
    }
    /*if(index == 0)
        ini = 0;
    else
        ini = rang[index-1];

    for(i=ini; i<rang[index]; i++){
        for (k=0;k<nnD;k++){
            C1[AD[k].i][i] += AD[k].v * B[AD[k].j][i];
        }
    }*/
}

void * parallel_code2(void * args){
    int VBcol[N];
    int index = (*(int*)args);
    int i, j, ini, k;

    memset(VBcol,0,sizeof(int)*nn);

    if(index == 0)
        ini = 0;
    else
        ini = rang[index-1];

    for(i=ini;i<rang[index];i++)
    {
        // Column expansion of B[*][i]
        for (k=0;k<nnD;k++)
            if (BD[k].j == i)
                VBcol[BD[k].i] = BD[k].v;
        // Full column C computation
        for (k=0;k<nnD;k++)
            C2[AD[k].i][i] += AD[k].v * VBcol[AD[k].j];
        // Clear of  B[*][i]
        for (j=0;j<nn;j++)
            VBcol[j] = 0;
    }
}

int main(int np, char *p[])
{
    int i,j,k,neleC,index;
    unsigned int thread_args[MAX_THREADS];
    pthread_t threads[MAX_THREADS];

    assert(np==3);

    nn = atoi(p[1]);
    assert(nn<=N);
    srand(1);

    numThreads = atoi(p[2]);
    assert(numThreads >= 2 && numThreads <= MAX_THREADS);

    nnD = nn*nn/100;

    memset(A,0,sizeof(int)*(nn*nn));
    memset(B,0,sizeof(int)*(nn*nn));
    memset(C,0,sizeof(int)*(nn*nn));
    memset(C1,0,sizeof(int)*(nn*nn));
    memset(C2,0,sizeof(int)*(nn*nn));
     
    for(k=0;k<nnD;k++)
    {
        AD[k].i=rand()%(nn-1);
        AD[k].j=rand()%(nn-1);
        AD[k].v=rand()%100;
        while (A[AD[k].i][AD[k].j]) {
            if(AD[k].i < AD[k].j)
                AD[k].i = (AD[k].i + 1)%nn;
            else 
                AD[k].j = (AD[k].j + 1)%nn;
        }
        A[AD[k].i][AD[k].j] = AD[k].v;
    }

    for(k=0;k<nnD;k++)
    {
        BD[k].i=rand()%(nn-1);
        BD[k].j=rand()%(nn-1);
        BD[k].v=rand()%100;
        while (B[BD[k].i][BD[k].j]) {
            if(BD[k].i < BD[k].j)
                BD[k].i = (BD[k].i + 1)%nn;
            else 
                BD[k].j = (BD[k].j + 1)%nn;
        }
        B[BD[k].i][BD[k].j] = BD[k].v;
    }

    //int porcio = nn/numThreads;
    //int mod = nn % numThreads;
    int porcio = nn*nnD/numThreads;
    int mod = nn*nnD % numThreads;

    for(i=0; i<numThreads; i++){
        rang[i] = porcio;
        if (i != 0) rang[i] += rang[i-1];
        if (i < mod) rang[i]++;
    }

    for (index = 0; index < numThreads; index++)
    {
        thread_args[index] = index;
        assert(!pthread_create(&threads[index], NULL, parallel_code1, &thread_args[index]));
    }

    for(index = 0; index < numThreads; index++)
    {
        assert(!pthread_join(threads[index], NULL ));
    }
    
    porcio = nn/numThreads;
    mod = nn % numThreads;

    for(i=0; i<numThreads; i++){
        rang[i] = porcio;
        if (i != 0) rang[i] += rang[i-1];
        if (i < mod) rang[i]++;
    }

    for (index = 0; index < numThreads; index++)
    {
        thread_args[index] = index;
        assert(!pthread_create(&threads[index], NULL, parallel_code2, &thread_args[index]));
    }

    for(index = 0; index < numThreads; index++)
    {
        assert(!pthread_join(threads[index], NULL ));
    }

    //Sparce Matrix X Sparce Matrix -> Dense Matrix
    //for (j=0;j<nn;j++)
    //    VBcol[j] = 0;

    //for(i=0;i<nn;i++)
    //  {
    //    // Column expansion of B[*][i]
    //    for (k=0;k<nnD;k++)
    //        if (BD[k].j == i)
    //            VBcol[BD[k].i] = BD[k].v;
    //    // Full column C computation
    //    for (k=0;k<nnD;k++)
    //        C2[AD[k].i][i] += AD[k].v * VBcol[AD[k].j];
    //    // Clear of  B[*][i]
    //    for (j=0;j<nn;j++)
    //        VBcol[j] = 0;
    //  }
                
    // Check (MD x M -> M) vs (MD x MD -> M)
    neleC = 0;
    Sum = 0;
    for (i=0;i<nn;i++)
        for(j=0;j<nn;j++)
	  {
            if (C2[i][j] != C1[i][j])
                printf("Not-Equal C1 & C2 pos %d,%d: %d != %d\n",i,j,C1[i][j],C2[i][j]);
	    if (C1[i][j])  // Some Value
	      {
		Sum += C1[i][j];
		neleC++;
	      }
	  }

    printf ("\nNumber of elements in C %d\n",neleC);   
    printf("Checksum of C %lld \n",Sum);
}
