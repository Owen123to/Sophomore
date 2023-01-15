#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *prev, *next;
};
/*
    function initLinkList will initialize the head of a linked list.
    parameter head represent the head of a linked list.
*/
void initLinkList(struct Node **head)
{
    (*head) = NULL;
}
/*
    function addToHead will insert a node which hold data into linked list from head of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
void addToHead(struct Node **head, int data)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    if(*head == NULL)
    {
        newNode->next = NULL;
        *head = newNode;
        return ;
    }
    (*head)->prev = newNode;
    newNode->next = *head;
    *head = newNode;
}
/*
    function addToHead will insert a node which hold data into linked list from tail of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
void addToTail(struct Node **head, int data)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    if(*head == NULL)
    {
        *head = newNode;
        newNode->prev = NULL;
        return;
    }
    struct Node *temp = *head;
    while(temp->next!=NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return ;
}
/*
    function deleteData will search from head to find the first node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
*/
void deleteData(struct Node **head, int data)
{
    struct Node *temp = *head;
    if(temp == NULL)
        return;
    if(temp->prev == NULL && temp->next == NULL)
        *head = NULL;
    while(temp->data!=data)
    {
        if(temp->next == NULL&&temp->data!=data)
            return ;
         temp = temp->next;
    }
     if(temp->prev == NULL && temp->next!=NULL)
    {
        temp->next->prev = NULL;
        (*head) = temp->next;
        temp->next = NULL;
    }
    else if(temp->prev!=NULL && temp->next == NULL)
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    else if(temp->prev!=NULL && temp->next!=NULL)
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = NULL;
        temp->prev = NULL;
    }
    free(temp);
    return ;
}
/*
    function deleteData will search from head to find the first n node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
    parameter n represent the max number of node to be removed.
*/
void deleteDatas(struct Node **head, int data, int n)
{
    while(n--)
        deleteData(head,data);
}
/*
    function display will print out all the data in the linked list from the head
    there is a \n in the end of each print
    output example:
    if your linked list data is 5, 4, 3, 2, 1
    then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
    parameter head represent the head of a linked list.
*/
void display(struct Node *head)
{
    if(head == NULL)
        return ;
    printf("(");
    struct Node *temp = head;
    while(1)
    {
        if(temp->next == NULL)
        {
            printf("%d)",temp->data);
            printf("\n");
            return;
        }
        else
        {
            printf("%d, ",temp->data);
            temp = temp->next;
        }
    }
}