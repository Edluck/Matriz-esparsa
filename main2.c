/*
Apos o teste da main.c, utilizar essa main2.c para finalizar os testes
*/

#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int i = 5, j = 5;
    printf("Este programa ira testar todas as funcoes de manipulacoes para a matriz de tamanho 5x5:\n\n");
    // apos os teste dessa main2, utilize Make main3.c para realizar a ultima funcao da convolucao
    //primeiro, criacao e atribuicao de valores
    Matriz *m1 = matriz_create(i, j);
    matriz_set_value(m1, 0, 1 , 1, ATUALIZAR);
    matriz_set_value(m1, 0, 3 , 1, ATUALIZAR);
    matriz_set_value(m1, 2, 3 , 1, ATUALIZAR);
    matriz_set_value(m1, 2, 4 , 1, ATUALIZAR);
    matriz_set_value(m1, 1, 2 , 1, ATUALIZAR);
    matriz_set_value(m1, 4, 0 , 1, ATUALIZAR);
    matriz_set_value(m1, 3, 0 , 1, ATUALIZAR);
    //printamos densamente a matriz para vizualizar-la
    printf("Matriz principal m1 em formato denso:\n");
    matriz_print_dense(m1);
    /* A proximas funcoes se relacionam a manipulacao dessa matriz principal
    , a funcao swap tanto de linha quanto de coluna, eh esperado que se troque
    as linhas originais pelas desejadas, ou seja, a primeira com a ultima ao 
    utilizar o swap_line e as determinadas colunas com swap_col
    */
    Matriz *m2 = matriz_swap_lin(m1, 0, 4);
    Matriz *m3 = matriz_swap_col(m1, 1, 3);

    //agora mostra o resultado dessa troca
    printf("Resultado da troca das linhas 0 e 4 da matriz 1:\n");
    matriz_print_dense(m2);
    printf("Resultado da troca das colunas 1 e 3 da matriz 1:\n");
    matriz_print_dense(m3);

    //teste da transposta agora, o esperado eh a troca de linhas com colunas
    Matriz *m4 = matriz_transposta(m1);
    printf("Matriz transposta da matriz 1:\n");
    matriz_print_dense(m4);

    //teste da matriz recortada da matriz 1
    Matriz *m5 = matriz_slice(m1, 1, 2, 3, 4);
    printf("Matriz recortada em 1,2 ate 3,4 da matriz 1:\n");
    matriz_print_dense(m5);
    // desaloca os espacos alocados
    matriz_destruct(m1);
    matriz_destruct(m2);
    matriz_destruct(m3);
    matriz_destruct(m4);
    matriz_destruct(m5);
    return 0;
}

/*
Teste feitos:
-Trocar (swap) duas linhas.
-Trocar (swap) duas colunas.
-Slice: retornar a submatriz retangular definida por um ponto esquerdo superior (início)
e um ponto direito inferior (fim). A Figura 2 ilustra a operação.
-Transpor uma matriz.

*/