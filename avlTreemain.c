#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
typedef struct treeNode
{
    avl_node_t root;
    int data;
}treeNode;
void initial(treeNode* temp,int nu)
{
    temp->data = nu;
    temp->root.left = NULL;
    temp->root.right = NULL;
    temp->root.height = 0;
}
int compare(void *temp1,void *temp2)
{
    if(((treeNode *)temp1)->data == ((treeNode *)temp2)->data) return 0;
    else if(((treeNode *)temp1)->data > ((treeNode *)temp2)->data)
        return 1;
    return -1;
}
void copy(void *temp1,void *temp2){((treeNode *)temp1)->data = ((treeNode *)temp2)->data;}
void print(void *temp){printf("%d ",((treeNode*)temp)->data);}
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
    printf("First we creat six treeNode and set aa which digit is 20 be the tree's root\n");
    treeNode *aa = (treeNode*)malloc(sizeof(treeNode));
    treeNode *bb = (treeNode*)malloc(sizeof(treeNode));
    treeNode *cc = (treeNode*)malloc(sizeof(treeNode));
    treeNode *dd = (treeNode*)malloc(sizeof(treeNode));
    treeNode *ee = (treeNode*)malloc(sizeof(treeNode));
    treeNode *ff = (treeNode*)malloc(sizeof(treeNode));
    treeNode *gg = (treeNode*)malloc(sizeof(treeNode));
    treeNode *hh = (treeNode*)malloc(sizeof(treeNode));
    treeNode *ii = (treeNode*)malloc(sizeof(treeNode));
    initial(aa,20);
    initial(bb,10);
    initial(cc,15);
    initial(dd,30);
    initial(ee,25);
    initial(ff,1);
    initial(gg,5);
    initial(hh,50);
    initial(ii,22);
    printf("Then we insert bb which digit is 10,cc which digit is 15,dd which digit is 30,ee which digit is 25,ff which digit is 1,gg which digit is 5,hh which is 50,ii which is 22 into the tree's root\n");
    //各自插入到樹中
    //插入完應為           15
    //               5         25
    //             1   10  20     30
    //                       22     50
    //電腦inorder映出應為1 5 10 15 20 22 25 30 50
    aa = (treeNode *)insert((avl_node_t *)aa,(avl_node_t *)bb,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)cc,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)dd,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)ee,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)ff,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)gg,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)hh,compare);
    aa = (treeNode *)insert((avl_node_t*)aa,(avl_node_t*)ii,compare);
    printf("Then we check the tree's order whether is right or not\n");
    printf("So we use inorder to check,and the inorder'order should be 1 5 10 15 20 22 25 30 50\n");
    inorder((avl_node_t *)aa,print);
    printf("\n");
    printf("Then we try to delete gg which is 5\n");
    printf("So we use inorder to check,and the inorder'order should be 1 10 15 20 22 25 30 50\n");
    aa = (treeNode *)Delete((avl_node_t*)aa,(avl_node_t*)gg,compare,copy);
    inorder((avl_node_t *)aa,print);
    printf("\n");
    printf("Then we try to delete ff which is 1\n");
    printf("So we use inorder to check,and the inorder'order should be 10 15 20 22 25 30 50\n");
    aa = (treeNode *)Delete((avl_node_t*)aa,(avl_node_t*)ff,compare,copy);
    inorder((avl_node_t *)aa,print);
    printf("\n");
    printf("Then we to find ii which is 22\n");
    print(find((avl_node_t*)aa,(avl_node_t*)ii,compare));
}

