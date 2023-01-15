#include<stdio.h>
#include<stdlib.h>
struct TreeNode
{
    int data;
    struct Node *children;
};
struct Node
{
    struct TreeNode *data;
    struct Node *prev,*next;
};
struct TreeNode *insert(struct TreeNode **root,struct TreeNode *node,int data)
{
    struct TreeNode *newNode = malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->children = NULL;
    if(*root == NULL)
    {
        *root = newNode;
        return newNode;
    }
    struct Node *temp = malloc(sizeof(struct Node));
    temp->data = newNode;
    temp->prev = NULL;
    temp->next = NULL;
    if(node->children == NULL)
    {
        node->children = temp;
        return newNode;
    }
    else
    {
        struct Node *cur = node->children;
        while(cur->next != NULL)
            cur = cur->next;
        cur->next = temp;
        temp->prev = cur;
        return newNode;
    }
}
void display(struct TreeNode *r,int d)
{
    int j;
    for(j = 0;j<d;j++)
        printf(" ");
    printf("%d\n",r->data);
    struct Node *cur = r->children;
    while(cur!=NULL)
    {
        display(cur->data,d+1);
        cur = cur->next;
    }
}
int main()
{
    struct TreeNode *root = NULL;
    struct TreeNode *node1 = insert(&root,NULL,1);
    insert(&root,node1,2);
    struct TreeNode *node3 = insert(&root,NULL,3);
    struct TreeNode *node4 = insert(&root,NULL,4);
    insert(&root,node3,5);
    display(root,0);
}