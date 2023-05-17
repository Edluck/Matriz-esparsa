#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include "celula.h"

typedef struct
{
    int size;
    Celula *head;
}ForwardList;

ForwardList *forward_list_create();
float forward_list_pull_value(ForwardList* f_line, int col);
void forward_list_mult_by_const(ForwardList **, ForwardList**, ForwardList*, float);
void forward_list_mult_two_matriz(ForwardList **f_new_line, ForwardList**f_new_col,int linha_new, int col_new, ForwardList*f1_line, ForwardList *f2_col);
void forward_list_set_value(ForwardList *f_line, ForwardList *f_col, int linha, int coluna, float val);
void forward_list_transposta(ForwardList **f_new_line, ForwardList**f_new_col, ForwardList*f_line);
void forward_list_print_dense(ForwardList *f_line, int col);
void forward_list_print_sparse(ForwardList *f_line, int col);
void forward_list_destroy(ForwardList* fl);


#endif