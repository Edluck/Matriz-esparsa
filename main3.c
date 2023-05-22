/*
Apos o teste da main2.c, utilizar essa main3.c para finalizar o ultimo teste de operacoes e manipulacoes
*/

#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int i = 5, j = 5;
    printf("Este programa ira testar todas as funcoes de manipulacoes para a matriz de tamanho 5x5:\n\n");
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
    /* o utlimo teste eh a convolucao da matriz principal por
    outra submatriz de kernel. O resultado esperado seria a
    multiplicacao ponto a ponto do slice gerado para ser igual
    a matriz de kernel, somar essa matriz multiplicada e a aplicar
    ele na matriz resultante
    */
    Matriz *kernel = matriz_create(3, 3);
    for (int a = 0; a < 3; a++)
    {
        for (int b = 0; b < 3; b++)
        {
            matriz_set_value(kernel, a, b, 1, ATUALIZAR);
        }
    }

    printf("Matriz kernel:\n");
    matriz_print_dense(kernel);

    // agora o teste da convolucao da matriz 1 pela matriz kernel
    Matriz *m2 = matriz_convolution(m1, kernel);
    /* No caso desse kernel, todos os elementos que possuirem algum
    1 a sua adjacencia, sera somado ao numero central
    */
    printf("Resultando da convolucao da matriz1:\n");
    matriz_print_dense(m2);
    // desaloca os espacos alocados
    matriz_destruct(m1);
    matriz_destruct(kernel);
    matriz_destruct(m2);
    return 0;
}

/*
Teste feito:

Realizar a convolução de uma matriz por outra matriz chamada de kernel. Vamos
implementar uma versão da operação de convolução que gera como saída uma matriz
do mesmo tamanho da entrada. O valor da célula (i, j) na matriz de saída será obtida
fazendo:
o Passo 1: a multiplicação ponto a ponto do kernel pela submatriz da entrada
centrada na posição (i, j) e de mesmo tamanho do kernel;
o Passo 2: a soma dos itens resultantes da operação anterior.
As Figuras 3 e 4 ilustram como as células de saída (0, 0) e (0, 3) seriam calculadas,
respectivamente. Importante: Nestas figuras, a matriz de saída está perdendo tantas
linhas e colunas quanto a metade do tamanho do kernel. Como indicado na Figura 5,
para prevenir este efeito, vamos realizar um tratamento de borda e assumir que os
índices das células fora da matriz possuem valor zero. Note que não é necessário de
fato adicionar a borda na matriz, mas apenas assumir que se os índices da célula
estiverem fora dos limites da matriz, deve ser retornado valor zero.
*/