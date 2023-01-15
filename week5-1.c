#include<stdio.h>
#include<string.h>

#define SIZE 5

struct Queue
{
    int data[SIZE];
    int top, bot,count;
};

int enqueue(struct Queue *queue, int data)
{
    if(queue->count+1>SIZE) return 0;
    if(queue->bot != queue->top||queue->count!=0)
        queue->bot = (queue->bot+1)%SIZE;
    queue->data[queue->bot] = data;
    queue->count++;
    return 1;
}

int *dequeue(struct Queue *queue)
{
    if(queue->count == 0)
    return NULL;
    int temp = queue->top;
    queue->top = (queue->top+1)%SIZE;
    queue->count--;
    return &queue->data[temp];
}

int main()
{
    int data, *temp;
    char command[50];
    struct Queue queue;
    queue.top = 0;
    queue.bot = 0;
    queue.count = 0;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(enqueue(&queue, data) == 1)
            {
                printf("Successfully enqueue data %d into queue.\n",data);
            }
            else
            {
                printf("Failed to enqueue data into queue.\n");
            }
        }
        else if(strcmp(command, "dequeue") == 0)
        {
            temp = dequeue(&queue);
            if(temp == NULL)
            {
                printf("Failed to dequeue a data from queue.\n");
            }
            else
            {
                printf("Dequeue data %d from queue.\n", *temp);
            }
        }
    }
}