// Based on Author: Ana Caroline Spengler
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int calc_diferenca(int **matriz,
                   int linha_maior,
                   int coluna_maior,
                   int *linha_menor,
                   int *coluna_menor,
                   int *valor_maior,
                   int *valor_menor) {
  int dif, aux_dif = INT_MIN;
  int i, j;
  for (i = linha_maior - 1; i < linha_maior + 2; i++) {
    for (j = coluna_maior - 1; j < coluna_maior + 2; j++) {
      if (!(i < 0 || i > linha_maior || j < 0 || j > coluna_maior)) {
        aux_dif = abs(matriz[linha_maior][coluna_maior] - matriz[i][j]);

        if (aux_dif > dif) {
          dif = aux_dif;
          *linha_menor = i;
          *coluna_menor = j;
          *valor_maior = matriz[linha_maior][coluna_maior];
          *valor_menor = matriz[i][j];
        }
      }
    }
  }
  return dif;
}

int main(void) {

  
  FILE *arquivo_entrada;
  arquivo_entrada = fopen("entrada.txt", "r");
  int linha_menor_aux,
      coluna_menor_aux,
      linha_maior_aux,
      coluna_maior_aux,
      valor_maior_aux,
      valor_menor_aux,
      tam,
      i,
      j = 0;

  int linha_menor,
      coluna_menor,
      linha_maior,
      coluna_maior,
      valor_maior,
      valor_menor = 0;

  fscanf(arquivo_entrada, "%d\n", &tam);

  int **matriz = ((int **)malloc(tam * sizeof(int *)));

  for (i = 0; i < tam; i++) {
    matriz[i] = ((int *)malloc(tam * sizeof(int)));
  }

  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      fscanf(arquivo_entrada, "%d\n", &(matriz[i][j]));
    }
  }

  int aux_comp;
  int diferenca = INT_MIN;
  int pos_i, pos_j;
  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      aux_comp =
          calc_diferenca(matriz,            // **matriz
                         i,                 // linha_maior
                         j,                 // coluna_maior
                         &linha_menor_aux,  // *linha_menor
                         &coluna_menor_aux, // *coluna_menor
                         &valor_maior_aux,  // *valor_maior
                         &valor_menor_aux); // *valor_menor

      if (diferenca < aux_comp) {
        diferenca = aux_comp;
        linha_maior = i;
        coluna_maior = j;
        linha_menor = linha_menor_aux;
        coluna_menor = coluna_menor_aux;
        valor_maior = valor_maior_aux;
        valor_menor = valor_menor_aux;
      }
    }
  }

  for (i = 0; i < tam; i++) {
    free(matriz[j]);
  }

  printf("M[%d,%d]=%dM[% d, % d] = % d ", linha_maior, coluna_maior, valor_maior, linha_menor, coluna_menor, valor_menor);

  free(matriz);
  fclose(arquivo_entrada);
}