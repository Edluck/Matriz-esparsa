/*
Apos o teste da main3.c, utilizar essa main4.c para verificar a correta leitura do arquivo binario
*/

#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int i = 5, j = 5;
    printf("Este programa ira testar a leitura de uma matriz a partir do arquivo binario:\n\n");
    // apos os teste dessa main2, utilize Make main3.c para realizar a ultima funcao da convolucao
    // primeiro, criacao e atribuicao de valores
    Matriz *m1 = matriz_create(i, j);
    matriz_set_value(m1, 0, 1, 1, ATUALIZAR);
    matriz_set_value(m1, 0, 3, 1, ATUALIZAR);
    matriz_set_value(m1, 2, 3, 1, ATUALIZAR);
    matriz_set_value(m1, 2, 4, 1, ATUALIZAR);
    matriz_set_value(m1, 1, 2, 1, ATUALIZAR);
    matriz_set_value(m1, 3, 1, 1, ATUALIZAR);
    matriz_set_value(m1, 3, 0, 1, ATUALIZAR);
    // printamos densamente a matriz para vizualizar-la
    printf("Matriz principal m1 em formato denso:\n");
    matriz_print_dense(m1);
    matriz_create_bynarie_arq(m1);
    /*
    O esperado seja que o print na tela seja igual a matriz principal
    */
    Matriz *m_bin = matriz_read_bynarie_arq();
    printf("Matriz lida a partir do arquivo binario da matriz m1:\n");
    matriz_print_dense(m_bin);
    // desaloca os espacos alocados
    matriz_destruct(m1);
    matriz_destruct(m_bin);
    return 0;
}

/*
Teste feito:

• Salvar matriz esparsa em um arquivo binário. Apenas os valores não nulos devem ser
salvos.
• Ler matriz esparsa de um arquivo binário.

*/