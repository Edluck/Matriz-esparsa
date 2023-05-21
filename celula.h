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

//funcao que cria um celula da matriz esparsa
Celula *celula_create(float val, Celula* next_col, Celula* next_line,  int col, int line);

//funcao que desaloca o espaco de uma celula
void celula_destroy(Celula *c);

#endif