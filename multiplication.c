#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) 
{
    if (!head1 || !tail1 || !head2 || !tail2 || !headR) 
    {
        return FAILURE;
    }

    // Handle multiplication by zero
    if (*head1 == NULL || *head2 == NULL) 
    {
        insert_at_head(headR, headR, 0);
        return SUCCESS;
    }

    *headR = NULL; // Initialize result list

    Dlist *temp2 = *tail2;
    int shift = 0;

    while (temp2) 
    {
        Dlist *temp1 = *tail1;
        Dlist *current_result = NULL;
        Dlist *current_tail = NULL;
        int carry = 0;

        // Multiply current digit of second number with all digits of first number
        while (temp1 || carry) 
        {
            long long product = carry; // Use long long to prevent overflow
            if (temp1) 
            {
                product += (long long)temp1->data * (long long)temp2->data;
                temp1 = temp1->prev;
            }

            // Insert digit at head of current result
            insert_at_head(&current_result, &current_tail, product % 10);
            carry = product / 10;
        }

        // Add leading zeros for place value
        for (int i = 0; i < shift; i++) 
        {
            insert_at_head(&current_result, &current_tail, 0);
        }

        // Add this partial result to the total result
        if (*headR == NULL) 
        {
            *headR = current_result; // First result
        } 
        else 
        {
            Dlist *temp_result = NULL;
            Dlist *temp_tail = NULL;
            int add_carry = 0;
            Dlist *res_temp = *headR; // Start from the head of the result
            Dlist *curr_temp = current_tail; // Start from the tail of the current result

            // Add current result to existing result
            while (res_temp || curr_temp || add_carry) 
            {
                long long sum = add_carry; // Use long long to prevent overflow
                if (res_temp) 
                {
                    sum += res_temp->data;
                    res_temp = res_temp->next; // Move to the next digit
                }
                if (curr_temp) 
                {
                    sum += curr_temp->data;
                    curr_temp = curr_temp->next; // Move to the next digit
                }

                insert_at_head(headR, headR, sum % 10);
                add_carry = sum / 10;
            }
        }

        temp2 = temp2->prev; // Move to the next digit in the second number
        shift++;
    }

    // Remove leading zeros
    while (*headR && (*headR)->data == 0 && (*headR)->next) 
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}