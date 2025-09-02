
#include "apc.h"

void print_list(Dlist *head) 
{
    if (head == NULL) 
    {
        printf("0\n");
        return;
    }

    Dlist *current = head;
    while (current) 
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}