# aula-openmpi

## Instalação do OpenMPI
Seguir o tutorial deste [link](http://lsi.ugr.es/~jmantas/pdp/ayuda/datos/instalaciones/Install_OpenMPI_en.pdf)

## Execução do programa
Para isso, você deverá compilar com o compilador `mpicc`. Para executar, você deve utilizar o comando `mpirun` seguido da flag que define o número de processos a serem criados `-np <n processos>` e o nome do programa. Assim:
```bash
mpicc programa.c -o programa -Wall -Werror && mpirun -np 4 programa
```

O comando acima compila e, em seguida, roda o programa (com 4 processos) caso não haja erros de compilação.
