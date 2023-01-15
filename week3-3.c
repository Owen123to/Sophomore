#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *prev, *next;
};
void initLinkList(struct Node **head)
{
    (*head) = NULL;
}
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
void deleteDatas(struct Node **head, int data, int n)
{
    while(n--)
        deleteData(head,data);
}
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
void push(struct Node **stack, int data)
{
    addToTail(stack,data);
}
int pop(struct Node **stack)
{
    if(*stack == NULL)
    return ;
    struct Node *temp = *stack;
    while(temp->next!=NULL)
    temp = temp->next;
    if(temp->prev == NULL)
        *stack = NULL;
    if(temp->prev!=NULL)
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    return temp->data;
}
int top(struct Node *stack)
{
    struct Node *temp = stack;
    while(temp->next!=NULL)
    temp = temp->next;
    return temp->data;
}
int isEmpty(struct Node *stack)
{
    if(stack == NULL)
    return 1;
    return 0;
}
int size(struct Node *stack)
{
    struct Node *temp = stack;
    int i = 0;
    while(temp!=NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}