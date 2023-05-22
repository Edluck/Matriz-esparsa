#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

/* Foi utilizado as nomenclatura f para se referir a ForwardList, line para linha ou col para coluna
    , new para a nova matriz que sera criada e retornada, f1 ou f2 para indicar que seria o vetor da linha ou coluna
    da matriz 1 e matriz 2 respectivamente. E a partir disso, feita a juncao dessas iniciais.
*/

ForwardList *forward_list_create()
{
    ForwardList *l = (ForwardList *)malloc(1 * sizeof(ForwardList));
    l->head = NULL;
    return l;
    // como essa parte nao utliza do tamanho da matriz, o seu tempo seria O(1)
}

void forward_list_set_value(ForwardList *f_line, ForwardList *f_col, int linha, int coluna, float val)
{
    // vamos tratar primeiro onde nao existe celula ainda na linha
    Celula *c = celula_create(val, NULL, NULL, coluna, linha);
    if (f_line->head == NULL)
    {
        f_line->head = c;
    }
    // agora verificamos se o que queremos inserir esta antes da head, entre as celulas ou por ultimo
    else
    {
        Celula *c_atual_aux = f_line->head;
        Celula *c_anterior_aux = NULL;
        while (c_atual_aux != NULL)
        {
            if (c_atual_aux->col >= coluna)
            {
                break;
            }
            c_anterior_aux = c_atual_aux;
            c_atual_aux = c_atual_aux->next_col;
        }
        // o elementos a inserir esta atras da head
        if (!c_anterior_aux)
        {
            f_line->head = c;
            c->next_col = c_atual_aux;
        }
        // o elemente a inserir esta entre elementos ou por ultimo
        else
        {
            c_anterior_aux->next_col = c;
            c->next_col = c_atual_aux;
        }
    } // agora para a coluna fazemos o mesmo processo
    if (f_col->head == NULL)
    {
        f_col->head = c;
    }
    else
    {
        Celula *c_atual_aux = f_col->head;
        Celula *c_anterior_aux = NULL;
        while (c_atual_aux != NULL)
        {
            if (c_atual_aux->line >= linha)
            {
                break;
            }
            c_anterior_aux = c_atual_aux;
            c_atual_aux = c_atual_aux->next_line;
        }
        if (!c_anterior_aux)
        {
            f_col->head = c;
            c->next_line = c_atual_aux;
        }
        else
        {
            c_anterior_aux->next_line = c;
            c->next_line = c_atual_aux;
        }
    }

    /* essa funcao, dependendo de nao ser o melhor caso(o primeiro elemento a ser inserido que seria O(1)
    ,o seu tempo seria O(n) pois eh necessario fazer uma busca linear para verificar a posicao do item
    a ser inserido, antes da head, entre elementos, ou por ultimo
    */
}

float forward_list_pull_value(ForwardList *f_line, int col)
{
    Celula *c = f_line->head;

    while (c != NULL)
    {
        if (c->col == col)
        {
            return c->val;
        }
        c = c->next_col;
    }
    return 0;
    /* Esta funcao teria uma compelxidade de O(n), justamente por que caminha ao longo da linha para encontrar o valor
     */
}

void forward_list_mult_two_matriz(ForwardList **f_new_line, ForwardList **f_new_col, int linha_new, int col_new, ForwardList *f1_line, ForwardList *f2_col)
{
    Celula *c_f1 = f1_line->head;
    Celula *c_f2 = f2_col->head;
    float valor = 0.0;

    while (c_f1 != NULL && c_f2 != NULL)
    {
        if (c_f1->col > c_f2->line)
        {
            c_f2 = c_f2->next_line;
        }
        else if (c_f1->col < c_f2->line)
        {
            c_f1 = c_f1->next_col;
        }
        else if (c_f1->col == c_f2->line)
        {
            valor += c_f1->val * c_f2->val;
            c_f1 = c_f1->next_col;
            c_f2 = c_f2->next_line;
        }
    }
    forward_list_set_value(f_new_line[linha_new], f_new_col[col_new], linha_new, col_new, valor);
    /* Considerando o tempo da funcao set_value, essa funcao de multiplicacao tem a complexidade O(n)
    ,pois faz uma busca na linha do primeiro e coluna do segundo, sendo ainda linear. Alem da funcao set_value
    somar esse n.
    */
}

void forward_list_mult_by_const(ForwardList **f_new_line, ForwardList **f_new_col, ForwardList *f_line, float cte)
{
    Celula *c = f_line->head;
    while (c != NULL)
    {
        float valor = cte * c->val;
        forward_list_set_value(f_new_line[c->line], f_new_col[c->col], c->line, c->col, valor);
        c = c->next_col;
    }
    // essa funcao tem a complexidade O(n^2), pois alem do set_value, ele faz tambem a busca linear na determinada linha
}

void forward_list_transposta(ForwardList **f_new_line, ForwardList **f_new_col, ForwardList *f_line)
{
    Celula *c = f_line->head;
    while (c != NULL)
    {
        float valor = c->val;
        forward_list_set_value(f_new_line[c->col], f_new_col[c->line], c->col, c->line, valor);
        c = c->next_col;
    }
    // essa funcao tem a complexidade O(n^2), pois temos o set_value dentro da funcao de busca
}

void forward_list_mult_point_to_point(ForwardList **f_new_line, ForwardList **f_new_col, ForwardList *f1_line, ForwardList *f2_line)
{
    Celula *c_f1 = f1_line->head;
    Celula *c_f2 = f2_line->head;
    float valor = 0.0;
    while (c_f1 != NULL && c_f2 != NULL)
    {
        if (c_f1->col > c_f2->col)
        {
            c_f2 = c_f2->next_line;
        }
        else if (c_f1->col < c_f2->col)
        {
            c_f1 = c_f1->next_col;
        }
        else if (c_f1->col == c_f2->col)
        {
            valor = c_f1->val * c_f2->val;
            forward_list_set_value(f_new_line[c_f1->line], f_new_col[c_f1->col], c_f1->line, c_f1->col, valor);
            c_f1 = c_f1->next_col;
            c_f2 = c_f2->next_col;
        }
    }
    // essa funcao tem a complexidade O(n^2), pois dentro da busca linear nas linhas das matrizes, temos a funcao set_value
}

void forward_list_slice(ForwardList **f_new_line, ForwardList **f_new_col, ForwardList *f1_line, int lin1, int col1, int lin2, int col2, int tam_max_col)
{
    Celula *c_f1 = f1_line->head;

    while (c_f1 != NULL && c_f1->col <= col2)
    {
        if (c_f1->col >= col1)
        {
            forward_list_set_value(f_new_line[c_f1->line - lin1], f_new_col[c_f1->col - col1], c_f1->line - lin1, c_f1->col - col1, c_f1->val);
        }
        c_f1 = c_f1->next_col;
    }
    /*
    Essa funcao tem a complexidade O(n^2), pois dentro da busca linear, existe o set_value
    */
}

void forward_list_swap_line(ForwardList **f_new_line, ForwardList **f_new_col, ForwardList *f_line, int lin_atual)
{
    Celula *c = f_line->head;

    while (c != NULL)
    {
        forward_list_set_value(f_new_line[lin_atual], f_new_col[c->col], lin_atual, c->col, c->val);
        c = c->next_col;
    }
    // complexidade O(n^2), assim como algumas funcoes acima. Esta acontecendo uma busca linear, dentro dela um set_value
}

void forward_list_swap_col(ForwardList **f_new_line, ForwardList **f_new_col, ForwardList *f_col, int col_atual)
{
    Celula *c = f_col->head;

    while (c != NULL)
    {
        forward_list_set_value(f_new_line[c->line], f_new_col[col_atual], c->line, col_atual, c->val);
        c = c->next_line;
    }
    // A mesma da swap_line
}

void forward_list_print_dense(ForwardList *f_line, int col)
{
    Celula *c = f_line->head;
    for (int i = 0; i < col; i++)
    {
        if (c != NULL && c->col == i)
        {
            printf("%.02f ", c->val);
            c = c->next_col;
        }
        else
        {
            printf("0.00 ");
        }
    }
    /* Essa funcao de print no formato denso possui O(n) de complexidade, pois estamos caminhando de 0 a col
     */
}

void forward_list_print_sparse(ForwardList *f_line, int col)
{
    Celula *c = f_line->head;
    for (int i = 0; i < col; i++)
    {
        if (c != NULL && c->col == i)
        {
            printf("%.02f ", c->val);
            c = c->next_col;
        }
        else
        {
            printf("     ");
        }
    }
    // Esta funcao possui complexidade O(n), pelo mesmo motivo da print_dense
}

void forward_list_destroy(ForwardList *fl)
{
    Celula *c = fl->head, *aux;

    while (c != NULL)
    {
        aux = c;
        c = c->next_line;
        celula_destroy(aux);
    }
    /* A funcao que desaloca espaco tem complexidade O(n), pois
    pela linha vai desalocando as celulas, ou seja, eh linear
    */
    free(fl);
}