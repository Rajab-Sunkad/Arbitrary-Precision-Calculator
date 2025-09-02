#ifndef APC_H
#define APC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef struct node 
{
    struct node *prev;
    data_t data;
    struct node *next;
} Dlist;

/* Include the prototypes here */
Dlist* create_list(data_t data);
void insert_at_head(Dlist **head, Dlist **tail, data_t data);
void insert_at_tail(Dlist **head, Dlist **tail, data_t data);
void print_list(Dlist *head);
void free_list(Dlist *head);
void create_list_from_input(Dlist **head, Dlist **tail, char *input);
int compare(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);

Dlist* get_tail(Dlist *head);
int get_length(Dlist *head);
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int compare(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);

#endif