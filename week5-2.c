#include <stdio.h>
#include <string.h>
#define SIZE 5

struct Stack
{
    int data[SIZE];
    int top;
    int count;
};

int push(struct Stack *stack, int data)
{
    if(stack->count+1>SIZE)
        return 0;
    stack->data[stack->top++] = data;
    stack->count++ ;
    return 1;
}

int *pop(struct Stack *stack)
{
    if(stack->count == 0)
        return NULL;
    stack->count-- ;
    return &stack->data[--stack->top];
}

int main()
{
    int data, *temp;
    char command[50];
    struct Stack stack;
    stack.top = 0;
    stack.count = 0;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "push") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(push(&stack, data) == 1)
            {
                printf("Successfully push data %d into stack.\n", data);
            }
            else
            {
                printf("Failed to push data into stack.\n");
            }
        }
        else if(strcmp(command, "pop") == 0)
        {
            temp = pop(&stack);
            if(temp == NULL)
            {
                printf("Failed to pop a data from stack.\n");
            }
            else
            {
                printf("Pop data %d from stack.\n", *temp);
            }
        }
    }
}