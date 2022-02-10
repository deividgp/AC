#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <assert.h>
#include <pthread.h>		//Incloem llibreria pthreads.

#define N 10000L
#define ND N*N/100

int A[N][N],B[N][N],C[N][N],C1[N][N],C2[N][N],VBcol[N];
struct {
    int i,j,v;
}AD[ND],BD[ND];

int nn,nnD,num_thread;
long long Sum;

void* funcio_fil(void* args);

int main(int np, char *p[])
{
    int i,j,k,neleC;

    assert(np==3);					//Comprovem si el nombre de paràmetres passats a l'executable és 2. 

	//Llegim els paràmetres referents a la dimensió de les matrius i nombre de threads, indicats per l'usuari.
    nn = atoi(p[1]);				
    num_thread = atoi(p[2]);

    //Comprovem que els paràmetres indicats estan dins del seu rang esperat.
    assert(nn<=N);					//dimensió matrius no podrà ser major o igual a la constant N.

    assert(num_thread>0);			//nombre threads no podrà ser menor a 0.

    pthread_t identificadors_threads[num_thread];	//En aquesta var guardarem els identificadors dels diferents fils creats pel programa.

    //Inicialitzem llavor nombres aleatoris.			
    srand(1);						

    nnD = nn*nn/100;

    bzero(A,sizeof(int)*(nn*nn));	//Per les següents matrius definides, inicialitzar les seves posicions de memòria a 0.
    bzero(B,sizeof(int)*(nn*nn));
    bzero(C,sizeof(int)*(nn*nn));
    bzero(C1,sizeof(int)*(nn*nn));
    bzero(C2,sizeof(int)*(nn*nn));
     
     //Inicialitzem vector A mitjançant AD.
    for(k=0;k<nnD;k++)
    {
        AD[k].i=rand()%(nn-1);
        AD[k].j=rand()%(nn-1);
        AD[k].v=rand()%100;
        while (A[AD[k].i][AD[k].j]) {
            if(AD[k].i < AD[k].j)			// Si AD[k].i < AD[k].j
                AD[k].i = (AD[k].i + 1)%nn;
            else 							//sinó,
                AD[k].j = (AD[k].j + 1)%nn;
        }
        A[AD[k].i][AD[k].j] = AD[k].v;
    }

	//Inicialitzem vector B mitjançant BD.
    for(k=0;k<nnD;k++)
    {
        BD[k].i=rand()%(nn-1);
        BD[k].j=rand()%(nn-1);
        BD[k].v=rand()%100;
        while (B[BD[k].i][BD[k].j]) {	//Mentre la posició de la matriu B indexada per .i i .j sigui diferent de 0:
            if(BD[k].i < BD[k].j)
                BD[k].i = (BD[k].i + 1)%nn;	//Modificarem .i o .j (depenent de l'if), per tal d' indexar a la següent
            else 
                BD[k].j = (BD[k].j + 1)%nn; //iteració del bucle una altra posició de la matriu B.
        }
        B[BD[k].i][BD[k].j] = BD[k].v;		//Un cop al haver trobat posicio de la matriu buida, la inicalitzem amb valor random (<100).
    }
 
 	// ------------------------------------- PARAL·LELITZACIÓ -------------------------------------

    int thread;
    //Matriu escassa X Matriu densa -> Matriu densa.
    for(thread=0;thread<num_thread;thread++){

    	if(pthread_create(&identificadors_threads[thread],NULL,funcio_fil,(void*)(intptr_t) thread) != 0){
    		fprintf(stderr, "Error creació thread %d\n",thread);
			return 1;
    	}
    }

    for(thread=0;thread<num_thread;thread++)
    	pthread_join(identificadors_threads[thread],NULL);


    // --------------------------------------------------------------------------------------------
                
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

void* funcio_fil(void* args){

	int i,k,inici,fi,identificador,VBcol_thread[N];
	
    identificador = (intptr_t) args;
	inici = identificador * nn/num_thread;
	fi = inici + nn/num_thread;

    for(i=inici;i<fi;i++)
        for (k=0;k<nnD;k++)
            C1[AD[k].i][i] += AD[k].v * B[AD[k].j][i];

    for (k=0;k<nn;k++)
        VBcol_thread[k] = 0;

    for(i=inici;i<fi;i++)
      {
        for (k=0;k<nnD;k++)
            if (BD[k].j == i) VBcol_thread[BD[k].i] = BD[k].v;                  // Column expansion of B[*][i]
                                    
        for (k=0;k<nnD;k++) C2[AD[k].i][i] += AD[k].v * VBcol_thread[AD[k].j];  // Full column C computation
                  
        for (k=0;k<nn;k++) VBcol_thread[k] = 0;                                 // Clear of  B[*][i]
                                                
      }

	return NULL;
}



