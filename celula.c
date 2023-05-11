#include <stdio.h>
#include <stdlib.h>
#include "celula.h"

Celula *celula_create(float val, Celula* next_col, Celula* next_line, int col, int line) {
    Celula *c = (Celula*)malloc(1*sizeof(Celula));
    c->val = val;
    c->next_col = next_col;
    c->next_line = next_line;
    c->col = col;
    c->line = line;
    return c;
}
void celula_destroy(Celula *c) {
    free(c);
}