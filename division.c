#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) 
{
    // Check for division by zero
    Dlist *temp = *head2;
    int is_zero = 1;
    while (temp) 
    {
        if (temp->data != 0) 
        {
            is_zero = 0;
            break;
        }
        temp = temp->next;
    }

    if (is_zero) 
    {
        printf("Error: Division by zero.\n");
        return FAILURE;
    }

    // Initialize result list
    *headR = NULL;

    // Convert first number to integer
    int dividend = 0;
    Dlist *temp1 = *head1;
    while (temp1) 
    {
        dividend = dividend * 10 + temp1->data;
        temp1 = temp1->next;
    }

    // Convert second number to integer
    int divisor = 0;
    Dlist *temp2 = *head2;
    while (temp2) 
    {
        divisor = divisor * 10 + temp2->data;
        temp2 = temp2->next;
    }

    // Perform division
    int result = dividend / divisor;

    // Convert result back to linked list
    if (result == 0) 
    {
        insert_at_head(headR, headR, 0);
        return SUCCESS;
    }

    while (result > 0) 
    {
        insert_at_head(headR, headR, result % 10);
        result /= 10;
    }

    return SUCCESS;
}