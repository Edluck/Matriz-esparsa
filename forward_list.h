#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include "celula.h"

typedef struct
{
    int size;
    int allocated;
    Celula *head;
}ForwardList;

ForwardList *forward_list_create();
void forward_list_destroy(ForwardList* fl);


#endif