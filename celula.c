#include <stdio.h>
#include <stdlib.h>
#include "celula.h"

Celula *celula_create(float val, Celula *next_col, Celula *next_line, int col, int line)
{
    Celula *c = (Celula *)malloc(1 * sizeof(Celula));
    c->val = val;
    c->next_col = next_col;
    c->next_line = next_line;
    c->col = col;
    c->line = line;
    return c;
    /*
    a funcao de criacao de celular eh constante O(1), nao eh influenciada por tamanho
    */
}
void celula_destroy(Celula *c)
{
    free(c);
    // funcao que so desaloca, eh complexidade O(1)
}