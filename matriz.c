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

void matriz_set_value(Matriz *m, int linha, int coluna, float val, Tipo_op_colisao op) {

    if(coluna < 0 || coluna >= m->colune_head_size || linha < 0 || linha >= m->line_head_size) {
        printf("Posicao invalida!\n");
        return;
    }
    /* Nao irei tratar o caso em que o usuario 0, pois se ele 
       quisesse 0 nessa posicao, ele inicialmente nao colocaria
       valor nela
    */
    // primeiro verificar se as cordenadas sao iguais ao que ja existe
    if(forward_list_pull_value(m->line_head[linha], coluna) != 0 && op == ATUALIZAR) {
        m->line_head[linha]->head->val = val;
        return;
    }
    else if(forward_list_pull_value(m->line_head[linha], coluna) != 0 && op == SOMAR) {
        Celula *c = m->line_head[linha]->head;
        while (c != NULL)
        {
            if(c->col == coluna) {
                c->val += val;
                return;
            }
            c = c->next_col;
        }
        
        return;
    }
    forward_list_set_value(m->line_head[linha], m->colune_head[coluna], linha, coluna, val);
    /*
    Essa funcao de inserir valores na matriz esparsa possui complexidade O(n), pois nao eh feito
    uma busca dentro de outra, apenas somamos buscas feitas dentro da matriz, continuando sendo linear
    */
}

float matriz_read_value(Matriz *m, int linha, int coluna) { 

    float valor_lido = forward_list_pull_value(m->line_head[linha], coluna);
    return valor_lido;
    // ela possui a complexidade igual da pull_value, O(n)
}

Matriz *matriz_mult_by_const(Matriz *m, float cte) {
    Matriz *m_new = matriz_create(m->line_head_size, m->colune_head_size);
    if(cte == 0) {
        return m_new;
    }
    // Caso ocorra da constante ser 0, retornamos a matriz, gerando um tempo dessa parte de O(1)
    // Considerando a criacao da matriz, seu tempo sera de O(i+j) = O(n)
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_mult_by_const(m_new->line_head, m_new->colune_head,m->line_head[i], cte);
    }
    /* Como aqui foi utilizado um for para fazer a busca nas linhas e dentro dela possui outra busca nessa linha, 
    ainda dentro dessa busca na linha, utiliza-se o set_value, gerando o maximo de O(n^3)
    */
    return m_new;
}

Matriz *matriz_sum_two_matriz(Matriz *m1, Matriz *m2) {
    Matriz *m_new = matriz_create(m1->line_head_size, m1->colune_head_size);;
    
    for (int i = 0; i < m_new->line_head_size; i++)
    {
        Celula *c = m1->line_head[i]->head;
        while (c != NULL)
        {
            matriz_set_value(m_new, c->line, c->col, c->val, SOMAR);
            c = c->next_col;
        }
        
    }
    for (int i = 0; i < m_new->line_head_size; i++)
    {
        Celula *c = m2->line_head[i]->head;
        while (c != NULL)
        {
            matriz_set_value(m_new, c->line, c->col, c->val, SOMAR);
            c = c->next_col;
        }
    }
    /* para fazer a soma, realizamos duas vezes a operacao de setar valor na funcao nova
    e como temos um for, e dentro um while e tambem a set_value, se nao considerar constante
    a complexidade seria O(n^3)
    */

    return m_new;
}
Matriz *matriz_mult_two_matriz(Matriz *m1, Matriz *m2) {
    Matriz *m_new = matriz_create(m1->line_head_size, m2->colune_head_size);

    if(m1->colune_head_size != m2->line_head_size){
        printf("Nao eh possivel multiplicar essas matrizes!\n");
        return m_new;
    }

    for (int i = 0; i < m1->colune_head_size; i++)
    {
        
        for (int j = 0; j < m2->line_head_size; j++)
        {
            forward_list_mult_two_matriz(m_new->line_head, m_new->colune_head,i, j, m1->line_head[i], m2->colune_head[j]);
        }
        
    }
    /* A funcao mult_two_matriz possui complexidade O(n), como ela esta dentro de dois for,
    a resultante dessa complexidade seria O(n^3)
    */

    
    return m_new;
}

Matriz *matriz_mult_point_to_point(Matriz *m1, Matriz *m2) {
    Matriz *m_new = matriz_create(m1->line_head_size, m2->colune_head_size);
    if((m1->colune_head_size != m2->colune_head_size) || (m1->line_head_size != m2->line_head_size)) {
        printf("Nao eh possivel realiza multiplicacao ponto a ponto, tamanhos diferentes!\n");
        return m_new;
    }
    for (int i = 0; i < m_new->line_head_size; i++)
    {
        forward_list_mult_point_to_point(m_new->line_head, m_new->colune_head, m1->line_head[i], m2->line_head[i]);
    }
    /*
    Considerando o caso em que os elementos vao coincidir suas posicoes para fazer a multiplicacao 
    e o set_value, como a funcao de complexidade O(n^2) esta dentro desse for, entao seria O(n^3)
    */
    return m_new;
}

Matriz *matriz_slice(Matriz *m, int lin1, int col1, int lin2, int col2) {
    Matriz *m_new = matriz_create(lin2-lin1+1, col2-col1+1);
    int lin_atual = lin1;

    for (int i = 0; i <= lin2-lin1; i++)
    {   
        if(!(lin_atual < 0 || lin_atual >= m->line_head_size)) {
            forward_list_slice(m_new->line_head, m_new->colune_head, m->line_head[lin_atual],lin1, col1, lin2, col2, m->colune_head_size);
        }
        lin_atual++;
    }
    
    // Seguindo a mesma ideia de funcoes anteriores, temos a funcao de complexidade O(n^2), estando dentro do for seria O(n^3)
    return m_new;
}

Matriz *matriz_transposta(Matriz *m) {
    Matriz *m_new = matriz_create(m->colune_head_size, m->line_head_size);
    
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_transposta(m_new->line_head, m_new->colune_head, m->line_head[i]);
    }
    
    // Seguindo a mesma ideia de funcoes anteriores, temos a funcao de complexidade O(n^2), estando dentro do for seria O(n^3)
    return m_new;
}

Matriz *matriz_swap_lin(Matriz *m, int lin1, int lin2) {
    Matriz *m_new = matriz_create(m->line_head_size, m->colune_head_size);

    for (int i = 0; i < m->line_head_size; i++)
    {
        if(i != lin1 && i != lin2) {
            forward_list_swap_line(m_new->line_head, m_new->colune_head, m->line_head[i], i);
        }
        else if(i == lin1) {
            forward_list_swap_line(m_new->line_head, m_new->colune_head, m->line_head[lin2], i);
        }
        else if(i == lin2) {
            forward_list_swap_line(m_new->line_head, m_new->colune_head, m->line_head[lin1], i);
        }
    }
    // Seguindo a mesma ideia de funcoes anteriores, temos a funcao de complexidade O(n^2), nesses tres ifs e estando dentro do for seria O(n^3)
    return m_new;
}

Matriz *matriz_swap_col(Matriz *m, int col1, int col2) {
    Matriz *m_new = matriz_create(m->line_head_size, m->colune_head_size);

    for (int i = 0; i < m->colune_head_size; i++)
    {
        if(i != col1 && i != col2) {
            forward_list_swap_col(m_new->line_head, m_new->colune_head, m->colune_head[i], i);
        }
        else if(i == col1) {
            forward_list_swap_col(m_new->line_head, m_new->colune_head, m->colune_head[col2], i);
        }
        else if(i == col2) {
            forward_list_swap_col(m_new->line_head, m_new->colune_head, m->colune_head[col1], i);
        }
    }
    // segue a mesma complexidade da swap_line
    return m_new;
}

float _matriz_plus_all_elements(Matriz *m) {
    float total = 0.0;

    for (int i = 0; i < m->line_head_size; i++)
    {
        Celula *c = m->line_head[i]->head;
        while (c != NULL)
        {
            total += c->val;
            c = c->next_col;
        }
    }
    /*
    Essa funcao possui complexidade O(n^2) pois possui uma busca no vetor de linha dentro de outra varredura das linhas
    */
    return total;
}

Matriz *matriz_convolution(Matriz *m, Matriz* kernel) {
    Matriz *m_new = matriz_create(m->line_head_size, m->colune_head_size);

    int tam_linha = kernel->line_head_size/2;
    int tam_col = kernel->colune_head_size/2;
    for (int i = 0; i < m->line_head_size; i++)
    {
        for (int j = 0; j < m->colune_head_size; j++)
        {
            Matriz *mult_por_kernel = matriz_slice(m,i-tam_linha, j-tam_col, i+tam_linha, j+tam_col);
            
            Matriz *m_resultado = matriz_mult_point_to_point(mult_por_kernel, kernel);
            
            float val = _matriz_plus_all_elements(m_resultado);
            matriz_set_value(m_new, i, j, val, ATUALIZAR);
            matriz_destruct(mult_por_kernel);
            matriz_destruct(m_resultado);
        }
    }
    /*
    Ja na convolucao, existe dois for para varrer elemento a elemento da matriz para
    realizar a multiplicacao pela matriz kernel, e como utiliza-se a matriz_slice, mult_point_to_point
    e a plus_all_elemenst em sequencias, ela possuira entao uma complexidade de O(n^4), pois essas funcoes
    sao O(n^2)
    */
    return m_new;
}

void matriz_print_dense(Matriz *m) {
    
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_print_dense(m->line_head[i], m->colune_head_size);
        printf("\n");
    }
    printf("\n");
    // Esta funcao de print na forma densa, como tempos complexidade O(n) na funcao dentro do for, resulta em O(n^2)
}

void matriz_print_esparsa(Matriz *m) {
    for (int i = 0; i < m->line_head_size; i++)
    {
        forward_list_print_sparse(m->line_head[i], m->colune_head_size);
        printf("\n");
    }
    // Esta funcao de print na forma esparsa, como tempos complexidade O(n) na funcao dentro do for, resulta em O(n^2)
     printf("\n");
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
    /*
    Nesta funcao e feita duas varredura em linha e em colunas, a funcao chamada dentro delas
    possui complexidade O(n), logo essa funcao de desalocar tudo seria O(n^2)
    */
}