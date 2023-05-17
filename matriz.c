#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

Matriz *matriz_create(int i, int j) {
    Matriz *m = (Matriz*)malloc(1*sizeof(Matriz));
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

void matriz_set_value(Matriz *m, int linha, int coluna, float val) {

    if(coluna < 0 || coluna >= m->colune_head_size || linha < 0 || linha >= m->line_head_size) {
        printf("Posicao invalida!\n");
        return;
    }
    /* Nao irei tratar o caso em que o usuario 0, pois se ele 
       quisesse 0 nessa posicao, ele inicialmente nao colocaria
       valor nela
    */
    // primeiro verificar se as cordenadas sao iguais ao que ja existe
    if(forward_list_pull_value(m->line_head[linha], coluna) != 0) {
        m->line_head[linha]->head->val = val;
        return;
    }
    forward_list_set_value(m->line_head[linha], m->colune_head[coluna], linha, coluna, val);
}

float matriz_read_value(Matriz *m, int linha, int coluna) { 

    float valor_lido = forward_list_pull_value(m->line_head[linha], coluna);
    return valor_lido;
}

Matriz *matriz_plus_by_const(Matriz *m, float cte) {
    Matriz *m_new = matriz_create(m->line_head_size, m->colune_head_size);
    if(cte == 0) {
        return m_new;
    }
    
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_plus_by_const(m_new->line_head, m_new->colune_head,m->line_head[i], cte, m->colune_head_size);
    }
    
    return m_new;
}

Matriz *matriz_sum_two_matriz(Matriz *m1, Matriz *m2) {
    Matriz *m3 = matriz_create(m1->line_head_size, m1->colune_head_size);;
    
    for (int i = 0; i < m3->line_head_size; i++)
    {
        Celula *c = m1->line_head[i]->head;
        while (c != NULL)
        {
            forward_list_set_value(m3->line_head[c->line], m3->colune_head[c->col], c->line, c->col, c->val);
            c = c->next_col;
        }
        
    }
    for (int i = 0; i < m3->line_head_size; i++)
    {
        Celula *c = m2->line_head[i]->head;
        while (c != NULL)
        {
            forward_list_set_value(m3->line_head[c->line], m3->colune_head[c->col], c->line, c->col, c->val);
            c = c->next_col;
        }
    }
    

    return m3;
}
Matriz *matriz_mult_two_matriz(Matriz *m1, Matriz *m2) {
    if(m1->colune_head_size != m2->line_head_size){
        printf("Nao eh possivel multiplicar essas matrizes!\n");
        return NULL;
    }
    Matriz *m3 = matriz_create(m1->line_head_size, m2->colune_head_size);
    
    return m3;
}

Matriz *matriz_transposta(Matriz *m) {
    Matriz *m_new = matriz_create(m->colune_head_size, m->line_head_size);
    
    
    return m_new;
}

void matriz_print_dense(Matriz *m) {
    
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_print_dense(m->line_head[i], m->colune_head_size);
        printf("\n");
    }
    printf("\n");
}

void matriz_print_esparsa(Matriz *m) {
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_print_sparse(m->line_head[i], m->colune_head_size);
        printf("\n");
    }
}

void matriz_destruct(Matriz * m) {

    for (int i = 0; i < m->colune_head_size; i++)
    {
        forward_list_destroy(m->colune_head[i]);
    }
    free(m->colune_head);
    for (int i = 0; i < m->line_head_size; i++)
    {
        free(m->line_head[i]);
    }
    free(m->line_head);
    free(m);
}