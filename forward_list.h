#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include "celula.h"

typedef struct
{
    int size;
    Celula *head;
}ForwardList;

// A definicao do que as funcoes baaixo fazem sao as mesma que as descritas em 'matriz.h'
// Utilizdas apenas para dividir o programa tornando mais facil de trabalhar o algoritmo
ForwardList *forward_list_create();
float forward_list_pull_value(ForwardList* f_line, int col);
void forward_list_mult_by_const(ForwardList **, ForwardList**, ForwardList*, float);
void forward_list_mult_two_matriz(ForwardList **f_new_line, ForwardList**f_new_col,int linha_new, int col_new, ForwardList*f1_line, ForwardList *f2_col);
void forward_list_set_value(ForwardList *f_line, ForwardList *f_col, int linha, int coluna, float val);
void forward_list_mult_point_to_point(ForwardList **, ForwardList**, ForwardList*, ForwardList *);
void forward_list_slice(ForwardList**f_new_line, ForwardList**f_new_col, ForwardList*f1_line, int lin1, int col1, int lin2, int col2, int tam_max_col);
void forward_list_transposta(ForwardList **f_new_line, ForwardList**f_new_col, ForwardList*f_line);
void forward_list_swap_line(ForwardList **f_new_line, ForwardList**f_new_col, ForwardList*f_line, int lin_atual);
void forward_list_swap_col(ForwardList **f_new_line, ForwardList**f_new_col, ForwardList*f_col, int col_atual);
//void forward_list_convolution(ForwardList **f_new_line, ForwardList**f_new_col, )
void forward_list_print_dense(ForwardList *f_line, int col);
void forward_list_print_sparse(ForwardList *f_line, int col);
void forward_list_destroy(ForwardList* fl);


#endif