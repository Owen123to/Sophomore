#ifndef __AVLTREE_H__
#define __AVLTREE_H__
typedef struct avl_node
{
	struct avl_node *left;
    struct avl_node *right;
	int height;
} avl_node_t;
 
avl_node_t *insert(avl_node_t *root, void *element, int (*compare)(void *elementA, void *elementB));
avl_node_t *Delete(avl_node_t *root, void *element, int (*compare)(void *elementA, void *elementB), void (*copy)(void *a, void *b));
avl_node_t *find(avl_node_t *root, void *element, int (*compare)(void *elementA, void *elementB));
static avl_node_t *rotateright(avl_node_t *);
static avl_node_t *rotateleft(avl_node_t *);
static avl_node_t *RR(avl_node_t *);
static avl_node_t *LL(avl_node_t *);
static avl_node_t *LR(avl_node_t *);
static avl_node_t *RL(avl_node_t *);
void inorder(avl_node_t *root, void (*print)(void *));
static int height(avl_node_t *node);
static int balanceFactor(avl_node_t *node);

#endif