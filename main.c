#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int i = 5, j = 5;
    printf("Este programa ira testar todas as funcoes de operacoes para a matriz de tamanho 5x5:\n\n");
    // Esta main realiza a primeira parte de teste, a main2.c realizara o restante
    // utilize o comando do makefile, apos ter feito 'Make clean', o comando 'Make main2' para compilar a segunda main
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
    printf("Matriz principal em formato esparso: \n");
    matriz_print_esparsa(m1);

    //leitura de algum valor, esperado achar o 1 da posicao 2,3 e 0 da posicao 0,0
    printf("Valor achado: pos(2,3) '%.02f' e pos(0,0) '%.02f'\n\n", matriz_read_value(m1, 2, 3), matriz_read_value(m1,0, 0));

    /* teste de operacoes com matrizes, para a multiplicacao
    eh esperado a matriz 1 multiplicada seus elementos por 2, resultando em 2 seus elementos
    , ja a matriz 3 eh esperado a soma da matriz 1 e 2, gerando 3 para todos seus elementos
    e a matriz 4 eh esperado a matriz final 5x5 com valores da multiplicacao de 2 por 3, gerando 6
    na maioria dos valores nao nulos e um 12 na primeira coluna e terceira linha
    */
    Matriz *m2 = matriz_mult_by_const(m1, 2);
    Matriz *m3 = matriz_sum_two_matriz(m1,m2);
    Matriz *m4 = matriz_mult_two_matriz(m2,m3);
    // esta multiplicacao ponto a ponto eh esperado os elementos todos 6
    Matriz *m5 = matriz_mult_point_to_point(m2,m3);
    
    printf("Teste da soma, multiplicacao e multiplicacao por escalar de matrizes:\n");
    printf("\nMultiplicacao da matriz 1(original) por escalar 2:\n");
    matriz_print_dense(m2);
    printf("Soma da matriz 1 com a matriz 2(multiplicada por 2):\n");
    matriz_print_dense(m3);
    printf("Multiplicacao da matriz 2 e 3:\n");
    matriz_print_dense(m4);
    printf("Multiplicacao ponto a ponto de 2 por 3:\n");
    matriz_print_dense(m5);
    //desalocamos todos os espacos alocados
    matriz_destruct(m1);
    matriz_destruct(m2);
    matriz_destruct(m3);
    matriz_destruct(m4);
    matriz_destruct(m5);
    return 0;
}
/*
Teste feitos:
- Criar matriz e destruir matriz.
- Atribuir valores à uma célula a partir da linha e coluna.
- Ler valores de uma célula a partir da linha e coluna.
- Somar matrizes.
- Multiplicar matrizes por um escalar.
- Multiplicar matrizes.
- Multiplicação ponto a ponto entre matrizes: dadas duas matrizes M1 e M2, com as
mesmas dimensões, a operação gera como saída uma matriz M3 com as mesmas
dimensões das entradas e tal que M3(i, j) = M1(i, j) * M2(i, j).

- Mostrar uma matriz na tela em formato esparso (apenas os itens diferentes de zero).
- Mostrar uma matriz na tela em formato denso
*/
