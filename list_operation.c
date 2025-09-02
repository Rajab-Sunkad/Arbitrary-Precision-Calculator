#include "apc.h"

// Function to create a new node
Dlist* create_list(data_t data) 
{
    Dlist *newNode = (Dlist*) malloc(sizeof(Dlist));
    if (!newNode) 
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insert_at_head(Dlist **head, Dlist **tail, data_t data) 
{
    Dlist *new_node = create_list(data);
    if (!*head) 
    {
        *head = new_node;
        *tail = new_node;
    } 
    else 
    {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    }
}

void insert_at_tail(Dlist **head, Dlist **tail, data_t data) 
{
    Dlist *new_node = create_list(data);
    if (!*head) 
    {
        *head = new_node;
        *tail = new_node;
    } 
    else 
    {
        new_node->prev = *tail;
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

// Function to free list
void free_list(Dlist *head) 
{
    while (head) 
    {
        Dlist *temp = head;
        head = head->next;
        free(temp);
    }
}


// Function to create list from input
void create_list_from_input(Dlist **head, Dlist **tail, char *input) 
{
    int len = strlen(input);
    for (int i = 0; i < len; i++) 
    {
        insert_at_tail(head, tail, input[i] - '0');
    }
}

int compare(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2) 
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;
    
    // Count the length of both numbers
    while (temp1) 
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2) 
    {
        len2++;
        temp2 = temp2->next;
    }
    
    // If lengths are different, we can immediately determine which is larger
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    
    // If lengths are equal, compare digit by digit from left to right
    temp1 = head1;
    temp2 = head2;
    while (temp1 && temp2) 
    {
        if (temp1->data > temp2->data) return 1;
        if (temp1->data < temp2->data) return -1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    
    // If we've made it here, the numbers are equal
    return 0;
}
