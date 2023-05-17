#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

ForwardList *forward_list_create() {
    ForwardList *l = (ForwardList*)malloc(1*sizeof(ForwardList));
    l->head = NULL;
    l->size = 0;
    return l;
}

void forward_list_set_value(ForwardList *f_line, ForwardList *f_col, int linha, int coluna, float val) {
    // vamos tratar primeiro onde nao existe celula ainda na linha
    Celula *c = celula_create(val, NULL, NULL, coluna, linha);
    if(f_line->head == NULL) {
        f_line->head = c;
    }
    // agora verificamos se o que queremos inserir esta antes da head, entre as celulas ou por ultimo
    else {
        Celula *c_atual_aux = f_line->head;
        Celula *c_anterior_aux = NULL;
        while(c_atual_aux != NULL) {
            if(c_atual_aux->col >= coluna) {
                break;
            }
            c_anterior_aux = c_atual_aux;
            c_atual_aux = c_atual_aux->next_col;
        }
        if(!c_anterior_aux) {
            f_line->head = c;
            c->next_col = c_atual_aux;
        }
        else if(c_atual_aux->col == coluna) { // para somar caso estejam no mesmo lugar
            c->val += val;
        }
        else {
            c_anterior_aux->next_col = c;
            c->next_col = c_atual_aux;
        }
    } // agora para a coluna
    if(f_col->head == NULL) {
        f_col->head = c;
    }
    else {
        Celula *c_atual_aux = f_col->head;
        Celula *c_anterior_aux = NULL;
        while(c_atual_aux != NULL) {
            if(c_atual_aux->line >= linha) {
                break;
            }
            c_anterior_aux = c_atual_aux;
            c_atual_aux = c_atual_aux->next_line;
        }
        if(!c_anterior_aux) {
            f_col->head = c;
            c->next_line = c_atual_aux;
        }
        else {
            c_anterior_aux->next_line = c;
            c->next_line = c_atual_aux;
        }
    }
}

float forward_list_pull_value(ForwardList* f_line, int col) {
    Celula *c = f_line->head;

    while (c != NULL)
    {
        if(c->col == col) {
            return c->val;
        }
        c = c->next_col;
    }
    return 0;
}

void forward_list_plus_by_const(ForwardList **f_new_line, ForwardList**f_new_col, ForwardList*f_line, float cte, int col) {
    Celula *c = f_line->head;
    while (c != NULL)
    {
        float valor = cte*c->val;
        forward_list_set_value(f_new_line[c->line], f_new_col[c->col], c->line, c->col, valor);
        c = c->next_col;
    }
}

void forward_list_print_dense(ForwardList *f_line, int col) {
    Celula *c = f_line->head;
    for (int i = 0; i < col; i++)
    {
        if(c != NULL && c->col == i) {
            printf("%.02f ", c->val);
            c = c->next_col;
        }
        else {
            printf("0.00 ");
        }
    }
    
}

void forward_list_print_sparse(ForwardList *f_line, int col) {
    Celula *c = f_line->head;
    for (int i = 0; i < col; i++)
    {
        if(c != NULL && c->col == i) {
            printf("%.02f", c->val);
        }
        else {
            printf("     ");
        }
    }
}

void forward_list_destroy(ForwardList* fl) {
    Celula *c = fl->head, *aux;

    while (c != NULL)
    {   
        aux = c;
        c = c->next_line;
        celula_destroy(aux);
    }
    
    free(fl);
}