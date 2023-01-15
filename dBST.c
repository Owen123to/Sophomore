#include"dllBST.h"
#include<stdio.h>
#include<stdlib.h>

btreeNode_t *insertNode(btreeNode_t *elementB, btreeNode_t *root, int(*compare)(void *elementA, void *element))
{
    if(root == NULL)
    {
        root = elementB;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if(compare(elementB,root)==1)//element>root
            root->right = (struct node*)insertNode(elementB,(btreeNode_t *)root->right,compare);
        else if(compare(elementB,root) == -1)
            root->left = (struct node*)insertNode(elementB,(btreeNode_t *)root->left,compare);
    }
    return root;
}
btreeNode_t* deleteNode(btreeNode_t* elementD,btreeNode_t* root,int(*compare)(void* elementA,void* element),void(*copy)(void* elementB,void* elementC))
{
    btreeNode_t* temp;
    if(root == NULL)
        printf("NO element\n");
    else
    {
        if(compare(elementD,root) == 1)//element>root
            root->right = deleteNode(elementD,root->right,compare,copy);
        else if(compare(elementD,root) == -1)
            root->left = deleteNode(elementD,root->left,compare,copy);
        else
        {
            if(root->left&&root->right)
            {
                temp = findMinNode(root->right);
                copy(root,temp);
                root->right = deleteNode(elementD,root->right,compare,copy);
            }
            else if(root->left == NULL)
            {
                temp = root;
                root = root->right;
                free(temp);
            }
            else
            {
                temp = root;
                root = root->left;
                free(temp);
            }
        }
    }
    return root;
}
btreeNode_t* findMinNode(btreeNode_t* root)
{
    if(root == NULL||root->left == NULL)
        return root;
    else
        return findMinNode((btreeNode_t*)(root->left));
}
btreeNode_t* findMaxNode(btreeNode_t* root)
{
    if(root == NULL || root->right == NULL)
        return root;
    else
        return findMaxNode((btreeNode_t*)(root->right));
}
btreeNode_t* findNode(btreeNode_t*element,btreeNode_t* root,int(*compare)(void* elementA,void* element))
{
    if(root == NULL) return NULL;
    if(compare(element,root) == 1) return findNode(element,root->right,compare);
    if(compare(element,root) == -1) return findNode(element,root->left,compare);
    return root;
}
void inOrder(btreeNode_t* root,void(*print)(void* element))
{
    if(root == NULL) return;
    inOrder(root->left,print);
    print(root);
    inOrder(root->right,print);
}
btreeNode_t* treeCopy(btreeNode_t* root,btreeNode_t* creat(),void(*copy)(void* elementB,void* elementC))
{
    if(root == NULL) return NULL;
    btreeNode_t* root_copy = creat();
    copy(root_copy,(void *)root);
    ((btreeNode_t*)root_copy)->left = treeCopy(root->left,creat,copy);
    ((btreeNode_t*)root_copy)->right = treeCopy(root->right,creat,copy);
    return (btreeNode_t*)root_copy;
}
int treeEuqal(btreeNode_t* root1,btreeNode_t* root2,int compare(void *temp1,void *temp2))
{
    if(root1 == NULL&&root2 == NULL)
    return 1;
    else if(root1 == NULL || root2 == NULL)
    return 0;
    else
    {
        if(compare(root1,root2)==0&&treeEuqal(root1->left,root2->left,compare)&&treeEuqal(root1->right,root2->right,compare))
        return 1;
        return 0;
    }
}
