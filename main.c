#include "matriz.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i, j;
    printf("Quantas linhas tem sua matriz? ");
    scanf("%d", &i);
    printf("Quantas colunas tem sua matriz? ");
    scanf("%d", &j);
    Matriz *m = matriz_create(i, j);
    matriz_set_value(m, 0, 2, 1);
    matriz_set_value(m, 0, 4, 1);
    matriz_set_value(m, 2, 1, 1);
    matriz_set_value(m, 3, 3, 1);
    printf("Achado: %.02f\n\n", matriz_read_value(m, 2, 2));
    Matriz *m2 = matriz_plus_by_const(m, 5);
    Matriz *m3 = matriz_sum_two_matriz(m,m2);
    matriz_print_dense(m);
    matriz_print_dense(m2);
    matriz_print_dense(m3);
    matriz_destruct(m);
    matriz_destruct(m2);
    matriz_destruct(m3);
    return 0;
}
