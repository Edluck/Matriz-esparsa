#ifndef MATRIZ_H
#define MATRIZ_H
#include "forward_list.h"

/* Este enum sera utilzado para caso haja colisao nas cordenadas
, e ai precisamos ver se a operacao eh de substituir ou somar
*/
typedef enum
{
    ATUALIZAR = 1,
    SOMAR = 2
} Tipo_op_colisao;

// a tad matriz mais externa, ela guarda o vetor de ponteiros das linhas e colunas
typedef struct
{
    ForwardList **line_head;
    ForwardList **colune_head;
    int line_head_size;   // de cada linha
    int colune_head_size; // de cada coluna
} Matriz;

// funcao que aloca espaco para a matriz e inicia cada i linhas e j colunas dos ponteiro
Matriz *matriz_create(int i, int j);

// funcao que, apos enviado a coluna, linha e o valor da celular, eh colocado na matriz esparsa(soma se vier da funcao de somar)
void matriz_set_value(Matriz *m, int linha, int coluna, float val, Tipo_op_colisao);

// funcao que le um determinado valor apos enviado suas coordenadas
float matriz_read_value(Matriz *m, int linha, int coluna);

// funcao que multiplica todos os elementos nao nulos por uma constante
Matriz *matriz_mult_by_const(Matriz *m, float cte);

// funcao que soma duas matrizes
Matriz *matriz_sum_two_matriz(Matriz *m1, Matriz *m2);

// funcao que retorna a transposta da matriz enviada, ou seja, trocar as linhas e colunas
Matriz *matriz_transposta(Matriz *m);

// esta funcao multiplica duas matrizes
Matriz *matriz_mult_two_matriz(Matriz *m1, Matriz *m2);

// esta funcao faz a multiplicacao ponto a ponto, ou seja, elemento por elemento
Matriz *matriz_mult_point_to_point(Matriz *m1, Matriz *m2);

// funcao que recorta uma parte desejada da matriz enviada
Matriz *matriz_slice(Matriz *m, int lin1, int col1, int lin2, int col2);

// funcao que troca duas determinadas linhas
Matriz *matriz_swap_lin(Matriz *m, int lin1, int lin2);

// funcao que troca duas determinadas colunas
Matriz *matriz_swap_col(Matriz *m, int col1, int col2);

/*funcao que faz a convolucao da matriz, multiplicando por outra chamada kernel
 nelas utilizamos duas matrizes a mais auxiliares para fazer o slice e a multiplicacao ponto a ponto
colocando o resultado na matriz de saida
*/
Matriz *matriz_convolution(Matriz *m, Matriz *kernel);

// funcao que cria o arquivo binario das informacoes da matriz
void matriz_create_bynarie_arq(Matriz *m);

// funcao que faz a leitura das informacoes da matriz no arquivo binario
Matriz *matriz_read_bynarie_arq();

// esta funcao mostra na tela a matriz esparsa como se fosse densa
void matriz_print_dense(Matriz *m);

// funcao que mostra na tela a matriz no formato esparso
void matriz_print_esparsa(Matriz *m);

// funcao que libera todo espaco alocado no programa
void matriz_destruct(Matriz *m);

#endif