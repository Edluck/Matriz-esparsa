#ifndef CELULA_H
#define CELULA_H

typedef struct Celula
{
    int line;
    int col;
    Celula *next_line;
    Celula *next_col;
    float val;
}Celula;

Celula *celula_create(float val, Celula* next_col, Celula* next_line,  int col, int line);
void celula_destroy(Celula *c);

#endif