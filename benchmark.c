/********************************************************
 * LISTA 5 - GUILHERME DE NEZ SILVANO			*
 *							*
 * Compilado usando o GCC 5.4.0				*
 *							*
 * O arquivo de entrada deve ter os números separados	*
 * por espaços						*
 *							*
 ********************************************************/

#include<stdio.h>
#include<sys/time.h>

#define SIZE_MAX 65535

int main(int argc,char *argv[]){
    
    /*
     * abre o arquivo por argumento na linha de comando
     */
    FILE* f=fopen(argv[1],"r");
  
    if(f==NULL){
	printf("ERRO: Inserir o arquivo de entrada como argumento!\n");
	return -1;
    }
    
    /*
     * Utlizar gettimeofday(&inicio,NULL) para disparar o cronômetro e
     * gettimeofday(&final,NULL) para parar o cronômetro.
     */
    struct timeval inicio,final; 

    int numListas,numElementos[SIZE_MAX];   //numero de listas e numero de elementos de cada um
    int milisec;			    //tempo decorrido em ms

    fscanf(f,"%d",&numListas);		    //determina o numero de listas
    int num[numListas][SIZE_MAX];	    //lista[número da lista][tamanho máximo de elementos]
    int numSwap[numListas][SIZE_MAX];	    //armazena o estado original das listas

    printf("\t___SORT BENCHMARKING___\n\n");

    /*
     * popula cada lista com seus elementos
     */
    for(int i=0;i<numListas;i++){ 
    fscanf(f,"%d",&numElementos[i]);
	for(int j=0;j<numElementos[i];j++){
	   fscanf(f,"%d",&num[i][j]);
	   numSwap[i][j]=num[i][j];
	}
    }

    /*
     * realiza todos os benchmarks para todas as listas
     * k = número da lista
     */
    for(int k=0;k<numListas;k++){
	int i,j;
	int swap;   
	int pos;    //usado na selection sort
	
	/*
	 * imprime a lista original
	 */
	printf("Lista %d: ",k+1);
	for(i=0;i<numElementos[k];i++){
	    printf("%d ",num[k][i]);
	}

	/*
	 * BUBBLE SORTING
	 */
	gettimeofday(&inicio,NULL);	    //cronômetro start
	
	for(i=0;i<(numElementos[k]-1);i++){
	    for(j=0;j<(numElementos[k]-(i+1));j++){
		if(num[k][j]>num[k][j+1]){
		    
		    swap=num[k][j];
		    num[k][j]=num[k][j+1];
		    num[k][j+1]=swap;
		}		
	    }
	}
	    
	gettimeofday(&final,NULL);	    //cronômetro stop

	printf("\nBubble Sort: ");
	for(i=0;i<numElementos[k];i++){
	    printf("%d ",num[k][i]);
	}

	/*
	 * calcula e imprime o tempo decorrido em milisegundos
	 */
	milisec=(int)(1000*(final.tv_sec-inicio.tv_sec)+(final.tv_usec-inicio.tv_usec)/1000);
	printf("\nTempo decorrido: %d ms",milisec);
	/*
	 * FIM BUBBLE SORTING
	 * 
	 * reordena a lista para seu estado original
	 */

	for(int j=0;j<numElementos[k];j++){
	    num[k][j]=numSwap[k][j];
	}
	
	/*
	 * SELECTION SORTING
	 */
	gettimeofday(&inicio,NULL);

	for(i=0;i<(numElementos[k]-1);i++){
	    pos=i;

	    for(j=(i+1);j<numElementos[k];j++){
		if(num[k][pos]>num[k][j]){
		    pos=j;
		}
	    }

	    if(pos!=j){
		swap=num[k][i];
		num[k][i]=num[k][pos];
		num[k][pos]=swap;
	    }
	}
	
	gettimeofday(&final,NULL);
	
	printf("\nSelection Sort: ");
	for(i=0;i<numElementos[k];i++){
	    printf("%d ",num[k][i]);
	}

	milisec=(int)(1000*(final.tv_sec-inicio.tv_sec)+(final.tv_usec-inicio.tv_usec)/1000);
	printf("\nTempo decorrido: %d ms",milisec);
	/*
	 * FIM SELECTION SORTING
	 */
	
	for(int j=0;j<numElementos[k];j++){
	    num[k][j]=numSwap[k][j];
	}
	
	/*
	 * INSERTION SORTING
	 */
	for(i=1;i<=numElementos[k]-1;i++){
	    j=i;

	    while(j>0 && num[k][j]<num[k][j-1]){
		swap=num[k][j];
		num[k][j]=num[k][j-1];
		num[k][j-1]=swap;

		j--;
	    }
	}

	gettimeofday(&final,NULL);

	printf("\nInsertion Sort: ");
	for(i=0;i<numElementos[k];i++){
	    printf("%d ",num[k][i]);
	}

	milisec=(int)(1000*(final.tv_sec-inicio.tv_sec)+(final.tv_usec-inicio.tv_usec)/1000);
	printf("\nTempo decorrido: %d ms",milisec);
	/*
	 * FIM INSERTION SORTING
	 */

	printf("\n\n");
    }
    
    return 0;
}
