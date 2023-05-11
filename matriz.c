#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

Matriz *matriz_create() {
    Matriz *m = (Matriz*)malloc(1*sizeof(Matriz));
    int i, j;
    printf("Quantas linhas tem sua matriz? ");
    scanf("%d", &i);
    printf("Quantas colunas tem sua matriz? ");
    scanf("%d", &j);
    printf("\n");
    m->colune_head = (ForwardList**)calloc(j,sizeof(ForwardList*));
    for (int a = 0; a < j; a++)
    {
        m->colune_head[a] = forward_list_create();
    }
    m->line_head = (ForwardList**)calloc(i,sizeof(ForwardList*));
    for (int a = 0; a < i; a++)
    {
        m->line_head[a] = forward_list_create();
    }
    
    m->colune_head_size = j;
    m->line_head_size = i;
    return m;
}
/* Nesta funcao de criar a matriz externa, que armazena os vetores 
de ponteiro para as cabecas das linhas e coluna, elas nao dependem do tamanho
sendo classificado sua otimizacao como O(i+j) = O(n)
*/

Matriz *matriz_push_value(Matriz *m) {

}

float matriz_read_value(Matriz *m) {

}

Matriz *matriz_plus_by_const(Matriz *m, float cte) {
    
    return m;
}

Matriz *matriz_sum_two_matriz(Matriz *m1, Matriz *m2) {
    Matriz *m3;
    
    return m3;
}

void matriz_print_dense(Matriz *m) {
    
}

void matriz_destruct(Matriz * m) {

    for (int i = 0; i < m->colune_head_size; i++)
    {
        forward_list_destroy(m->colune_head[i]);
    }
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_destroy(m->line_head[i]);
    }

    free(m);
}