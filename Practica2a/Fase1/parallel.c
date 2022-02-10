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

int getIni(int index){
    if(index == 0)
        return 0;
    else
        return rang[index-1];
}

void * parallel_code1(void * args){
    int index = (*(int*)args);
    int i, j, ini, k;

    for(i=getIni(index); i<rang[index]; i++){
        for (k=0;k<nnD;k++){
            C1[AD[k].i][i] += AD[k].v * B[AD[k].j][i];
        }
    }
}

void * parallel_code2(void * args){
    int VBcol[N];
    int index = (*(int*)args);
    int i, j, ini, k;

    memset(VBcol,0,sizeof(int)*nn);

    for(i=getIni(index);i<rang[index];i++)
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

    bzero(A,sizeof(int)*(nn*nn));
    bzero(B,sizeof(int)*(nn*nn));
    bzero(C,sizeof(int)*(nn*nn));
    bzero(C1,sizeof(int)*(nn*nn));
    bzero(C2,sizeof(int)*(nn*nn));
     
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

    int porcio = nn/numThreads;
    int mod = nn % numThreads;

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

    for (index = 0; index < numThreads; index++)
    {
        thread_args[index] = index;
        assert(!pthread_create(&threads[index], NULL, parallel_code2, &thread_args[index]));
    }

    for(index = 0; index < numThreads; index++)
    {
        assert(!pthread_join(threads[index], NULL ));
    }
                
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
