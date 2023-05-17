#ifndef MATRIZ_H
#define MATRIZ_H
#include "forward_list.h"

typedef struct
{
    ForwardList **line_head;
    ForwardList **colune_head;
    int line_head_size;
    int colune_head_size;
}Matriz;

Matriz *matriz_create(int i, int j);
void matriz_set_value(Matriz *m, int linha, int coluna, float val);
float matriz_read_value(Matriz *m, int linha, int coluna);
Matriz *matriz_plus_by_const(Matriz *m, float cte);
Matriz *matriz_sum_two_matriz(Matriz *m1, Matriz *m2);
Matriz *matriz_transposta(Matriz *m);
Matriz *matriz_mult_two_matriz(Matriz *m1, Matriz *m2);
void matriz_print_dense(Matriz *m);
void matriz_print_esparsa(Matriz *m);
void matriz_destruct(Matriz *m);

#endif