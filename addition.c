/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

// Function to perform addition
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) 
{
    int carry = 0;
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    // Initialize the result list
    *headR = NULL;

    while (temp1 || temp2 || carry) 
    {
        int sum = carry; // Start with carry
        if (temp1) 
        {
            sum += temp1->data; // Add current digit from the first number
            temp1 = temp1->prev; // Move to the previous digit
        }
        if (temp2) 
        {
            sum += temp2->data; // Add current digit from the second number
            temp2 = temp2->prev; // Move to the previous digit
        }

        // Insert the last digit of sum at the head of the result list
        insert_at_head(headR, headR, sum % 10);
        carry = sum / 10; // Update carry for next iteration
    }

    return SUCCESS;
}