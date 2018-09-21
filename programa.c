// 5248962 Edylson Torikai
// 4471070 Fernanda Tostes
// 8531289 Guilherme Amorim Menegali
// 9266664 Tainá Andrello Piai
// 9293007 Fernando Vinícius Gianini Silva
// 7151905 Romeu Bertho Junior

/*
Particionamento
Cada tarefa procura a maior diferença entre um elemento e seus vizinhos 

Comunicação
A comunicação acontece ao se agrupar todas as diferenças encontradas no processo principal

Aglomeração
A aglomeração depende da quantidade de processos estabelecidos e da ordem N da matriz.
O programa tenta disponibilizar um número próximo de tarefas para cada processo.

Mapeamento
O mapeamento é de acordo com o numero de processadores disponibilizados.



*/




#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <math.h>
#include <mpi.h>



void calc_diferenca(int **matriz, int linha_maior,int coluna_maior){
	int linha_menor,coluna_menor,valor_maior,valor_menor;
	int dif = INT_MIN, aux_dif = INT_MIN;
	int i, j;
	int mensagem[5];

	for (i = linha_maior - 1; i < linha_maior + 2; i++) {
		for (j = coluna_maior - 1; j < coluna_maior + 2; j++) {
		
			if (!(i < 0 || i > linha_maior || j < 0 || j > coluna_maior)){
				aux_dif = abs(matriz[linha_maior][coluna_maior] - matriz[i][j]);
				if (aux_dif > dif){
					dif = aux_dif;
					linha_menor=i;
					coluna_menor=j;
					valor_maior=matriz[linha_maior][coluna_maior];
					valor_menor=matriz[i][j];
				}
			}
		}	
	}

	
	mensagem[0] = dif;
	mensagem[1] = linha_menor;
	mensagem[2] = coluna_menor;
	mensagem[3] = valor_maior;
	mensagem[4] = valor_menor;




	MPI_Send(mensagem, 5, MPI_INT, 0, 1, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]){

FILE *arquivo_entrada;
arquivo_entrada = fopen("BCC_TB_numeros.txt", "r");
int linha_menor_aux,coluna_menor_aux,linha_maior_aux,coluna_maior_aux,valor_maior_aux,valor_menor_aux,tam,i,j=0;
int linha_menor,coluna_menor,linha_maior,coluna_maior,valor_maior,valor_menor=0;
	fscanf(arquivo_entrada, "%d\n", &tam);

int **matriz=((int**)malloc(tam*sizeof(int*)));
for(i=0;i<tam;i++){
	matriz[i]=((int*)malloc(tam*sizeof(int)));
	}
		for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
		fscanf(arquivo_entrada, "%d\n", &(matriz[i][j]));
	}
}
int mensagem[5];
int npes;
int myrank;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &npes);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);



int aux_comp = INT_MIN;
int diferenca = INT_MIN;
int pos_i, pos_j;
for (i = 0; i < tam; i++) {
	for (j = 0; j < tam; j++) {
		if(myrank == ((i*tam + j)%(npes-1)+1) ){


			calc_diferenca(matriz, i, j);
		}
		else if(myrank ==0) {
			MPI_Recv(mensagem, 5, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
			
			
			if (diferenca < mensagem[0]){
				diferenca = mensagem[0];
				linha_maior=i;
				coluna_maior=j;
				linha_menor=mensagem[1];
				coluna_menor=mensagem[2];
				valor_maior=mensagem[3];
				valor_menor=mensagem[4];


			}


		}


		
	}
}

for(i=0;i<tam;i++){
	free(matriz[j]);
}



if (myrank == 0)
	printf("M[%d,%d]=%d M[%d,%d]=%d",linha_maior,coluna_maior,valor_maior,linha_menor,coluna_menor,valor_menor);

free(matriz);
fclose(arquivo_entrada);


MPI_Finalize();
}