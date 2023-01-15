#include"dllBST.h"
#include<stdio.h>
#include<stdlib.h>
typedef struct tree_Node
{
    btreeNode_t root;
    int data;
}treeNode;
btreeNode_t* creat()
{
    treeNode* element = (treeNode*)malloc(sizeof(treeNode));
    element->root.left = NULL;
    element->root.right = NULL; 
    return (btreeNode_t*)element;
}
void initial(treeNode* temp,int nu)
{
    temp->data = nu;
    temp->root.left = NULL;
    temp->root.right = NULL;
    return;
}
int compare(void *temp1,void *temp2)
{
    if(((treeNode *)temp1)->data == ((treeNode *)temp2)->data) return 0;
    else if(((treeNode *)temp1)->data > ((treeNode *)temp2)->data)
        return 1;
    return -1;
}
void copy(void *temp1,void *temp2){((treeNode *)temp1)->data = ((treeNode *)temp2)->data;}
void print(void *temp){printf("%d\n",((treeNode*)temp)->data);}
void delete_tree(treeNode* temp)
{
    if(temp == NULL) return;
    delete_tree(((treeNode*)(temp->root.left)));
    delete_tree(((treeNode*)(temp->root.right)));
    free(&(temp->data));
    free(temp);
}
int main()
{
    //先創6個點,以aa為樹根
    printf("First we creat six treeNode and set aa which digit is six be the tree's root\n");
    treeNode *aa = (treeNode*)malloc(sizeof(treeNode));
    treeNode *bb = (treeNode*)malloc(sizeof(treeNode));
    treeNode *cc = (treeNode*)malloc(sizeof(treeNode));
    treeNode *dd = (treeNode*)malloc(sizeof(treeNode));
    treeNode *ee = (treeNode*)malloc(sizeof(treeNode));
    treeNode *ff = (treeNode*)malloc(sizeof(treeNode));
    initial(aa,6);
    initial(bb,10);
    initial(cc,3);
    initial(dd,4);
    initial(ee,2);
    initial(ff,8);
    printf("Then we insert bb which digit is ten,cc which digit is three,dd which digit is four,ee which digit is two,ff which digit is eight into the tree's root\n");
    //各自插入到樹中
    //插入完應為         6
    //               3     10
    //             2   4  8
    //電腦inorder映出應為2 3 4 6 8 10
    insertNode((btreeNode_t *)bb,(btreeNode_t *)aa,compare);
    insertNode((btreeNode_t*)cc,(btreeNode_t*)aa,compare);
    insertNode((btreeNode_t*)dd,(btreeNode_t*)aa,compare);
    insertNode((btreeNode_t*)ee,(btreeNode_t*)aa,compare);
    insertNode((btreeNode_t*)ff,(btreeNode_t*)aa,compare);
    printf("After we insert these treeNodes,then we try to find the max treeNode\n");
    printf("And the max treeNode should be 10\n");
    print(findMaxNode((btreeNode_t*)aa));
    printf("\n");
    printf("After we find max treeNode,then we try to find the min treeNode\n");
    printf("And the min treeNode should be 2\n");
    print(findMinNode((btreeNode_t*)aa));
    printf("\n");
    printf("Then we check the tree's order whether is right or not\n");
    printf("So we use inorder to check,and the inorder'order should be 2 3 4 6 8 10\n");
    inOrder((btreeNode_t *)aa,print);
    printf("\n");
    printf("After check the order,we try to find the bb which number is ten in the tree\n");
    printf("And print the bb\n");
    print(findNode((btreeNode_t*)bb,(btreeNode_t *)aa,compare));
    printf("After find bb in the tree,we copy the tree\n");
    treeNode* copynode = (treeNode*)treeCopy((btreeNode_t*)aa,creat,copy);
    inOrder((btreeNode_t*)copynode,print);
    printf("\n");
    printf("After copy the tree, we compare whether the tree is same or not\n");
    printf("%s\n",treeEuqal((btreeNode_t*)copynode,(btreeNode_t*)aa,compare) == 1?"Same":"Not Same");
    printf("Then we delete bb which number is ten in aa,to compare the two tree is same or not\n");
    deleteNode((btreeNode_t *)bb,(btreeNode_t *)aa,compare,copy);
    printf("%s\n",treeEuqal((btreeNode_t*)copynode,(btreeNode_t*)aa,compare) == 1?"Same":"Not Same");
    printf("After we compare the two trees,we delete cc which number is three and delete aa which number is six\n");
    printf("Then we print inorder and the order should be 2 4 8\n");
    deleteNode((btreeNode_t *)cc,(btreeNode_t *)aa,compare,copy);
    deleteNode((btreeNode_t *)aa,(btreeNode_t *)aa,compare,copy);
    inOrder((btreeNode_t *)aa,print);
    printf("\n");
    delete_tree(aa);
    delete_tree(copynode);
}