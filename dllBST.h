#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

typedef struct node {
    struct node * left;
    struct node * right;
} btreeNode_t;

btreeNode_t* insertNode(btreeNode_t *elementB, btreeNode_t *root, int(*compare)(void *elementA, void *element));
btreeNode_t* deleteNode(btreeNode_t *elementD,btreeNode_t *root,int(*compare)(void* elementA,void* element),void(*copy)(void* elementB,void* elementC));
btreeNode_t* findMinNode(btreeNode_t* root);
btreeNode_t* findMaxNode(btreeNode_t* root);
btreeNode_t* findNode(btreeNode_t* element,btreeNode_t* root,int(*compare)(void* elementA,void* element));
void inOrder(btreeNode_t* root,void(*print)(void* element));
btreeNode_t* treeCopy(btreeNode_t* root,btreeNode_t* creat(),void(*copy)(void* elementB,void* elementC));
int treeEuqal(btreeNode_t* root1,btreeNode_t* root2,int compare(void *temp1,void *temp2));
#endif