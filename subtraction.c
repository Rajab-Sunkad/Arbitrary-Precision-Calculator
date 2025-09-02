#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) 
{
    if (!head1 || !tail1 || !head2 || !tail2 || !headR) 
    {
        printf("Error: Invalid input pointers\n");
        return FAILURE;
    }

    if (!*head1 || !*tail1) 
    {
        printf("Error: First number is empty\n");
        return FAILURE;
    }

    // Check if head1 is greater than or equal to head2
    int comparison = compare(*head1, *tail1, *head2, *tail2);
    
    // If head1 < head2, swap the operands
    if (comparison < 0) 
    {
        // Swap the heads and tails
        Dlist *tempHead = *head1;
        Dlist *tempTail = *tail1;
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = tempHead;
        *tail2 = tempTail;

        printf("-"); // Indicate that the result will be negative
    } 
    else if (comparison == 0) 
    {
        // If they are equal, the result is zero
        *headR = create_list(0);
        return SUCCESS;
    }

    int borrow = 0;
    Dlist *temp1 = *tail1; // Start from the end of the first number
    Dlist *temp2 = *tail2; // Start from the end of the second number
    *headR = NULL;  // Initialize result list to empty

    // Perform subtraction digit by digit from right to left
    while (temp1 != NULL) 
    {
        int digit1 = temp1->data; // Current digit from first number
        int digit2 = (temp2 != NULL) ? temp2->data : 0; // Current digit from second number

        // Apply previous borrow if any
        digit1 -= borrow;

        // Reset borrow
        borrow = 0;

        // If digit1 is less than digit2, we need to borrow from the next digit
        if (digit1 < digit2) 
        {
            digit1 += 10; // Borrow from the next digit
            borrow = 1;   // Set borrow for the next iteration
        }

        // Calculate the difference
        int diff = digit1 - digit2;

        // Insert at the beginning of result list
        insert_at_head(headR, headR, diff);

        // Move to the next digits
        temp1 = temp1->prev;
        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    // Remove leading zeros from the result
    while (*headR != NULL && (*headR)->data == 0 && (*headR)->next != NULL) 
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}