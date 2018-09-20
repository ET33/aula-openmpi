// 5248962 Edylson Torikai
// 4471070 Fernanda Tostes
// 8531289 Guilherme Amorim Menegali
// 9266664 Tainá Andrello Piai
// 9293007 Fernando Vinícius Gianini Silva
// 7151905 Romeu Bertho Junior

#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <math.h>
#include <mpi.h>

#define n_processos 2

void calc_diferenca(int **matriz, int linha_maior,int coluna_maior,int *linha_menor,int
	*coluna_menor,int *valor_maior,int *valor_menor){
	int dif, aux_dif = INT_MIN;
	int i, j;
	for (i = linha_maior - 1; i < linha_maior + 2; i++) {
		for (j = coluna_maior - 1; j < coluna_maior + 2; j++) {
		
			if (!(i < 0 || i > linha_maior || j < 0 || j > coluna_maior)){
				aux_dif = abs(matriz[linha_maior][coluna_maior] - matriz[i][j]);
			if (aux_dif > dif){
				dif = aux_dif;
				*linha_menor=i;
				*coluna_menor=j;
				*valor_maior=matriz[linha_maior][coluna_maior];
				*valor_menor=matriz[i][j];
			}
		}
	}

		MPI_Send(&dif, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		MPI_Send(linha_menor, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(coluna_menor, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
		MPI_Send(valor_maior, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		MPI_Send(valor_menor, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);
	}
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
int a[10], b[10];
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
		if(myrank != 0){
			calc_diferenca(matriz, i, j,&linha_menor_aux,&coluna_menor_aux,&valor_maior_aux,&valor_menor_aux);
		}
		else if(myrank ==0) {
			MPI_Recv(&aux_comp, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&linha_menor, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&coluna_menor, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
			MPI_Recv(&valor_maior, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);
			MPI_Recv(&valor_menor, 1, MPI_INT, MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);

			if (diferenca < aux_comp){
				diferenca = aux_comp;
				linha_maior=i;
				coluna_maior=j;
			}


		}


		
	}
}

for(i=0;i<tam;i++){
	free(matriz[j]);
}

if (myrank == 0)
	printf("M[%d,%d]=%d M[%d,%d]=%d\n",linha_maior,coluna_maior,valor_maior,linha_menor,coluna_menor,valor_menor);

free(matriz);
fclose(arquivo_entrada);

MPI_Finalize();
}