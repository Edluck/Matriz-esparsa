#ifndef CELULA_H
#define CELULA_H

typedef struct celula
{
    int line;
    int col;
    struct celula *next_line;
    struct celula *next_col;
    float val;
}Celula;

Celula *celula_create(float val, Celula* next_col, Celula* next_line,  int col, int line);
void celula_destroy(Celula *c);

#endif