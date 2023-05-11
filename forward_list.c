#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

ForwardList *forward_list_create() {
    ForwardList *l = (ForwardList*)malloc(1*sizeof(ForwardList));
    l->head = NULL;
    l->size = 0;
    return l;
}
void forward_list_destroy(ForwardList* fl) {
    free(fl);
}