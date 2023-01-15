#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
avl_node_t *insert(avl_node_t *root, void *element, int (*compare)(void *elementA, void *elementB))
{
    if (root == NULL)
        root = element;
    else if (compare(element, root) == 0)
        return NULL;
    else if (compare(element, root) == 1)
    {
        root->right = insert(root->right, element, compare);
        if (balanceFactor(root) == -2)
        {
            if (compare(element, root->right) == 1)
                root = LL(root);
            else
                root = RL(root);
        }
    }
    else if (compare(element, root) == -1)
    {
        root->left = insert(root->left, element, compare);
        if (balanceFactor(root) == 2)
        {
            if (compare(element, root->left) == -1)
                root = RR(root);
            else
                root = LR(root);
        }
    }
    root->height = height(root);
    return root;
}
avl_node_t *Delete(avl_node_t *root, void *element, int (*compare)(void *elementA, void *elementB),void (*copy)(void *a, void *b))
{
    avl_node_t *temp = NULL;
    if (root == NULL)
        return NULL;
    if (compare(element, root) == 1)
    {
        root->right = Delete(root->right, element, compare, copy);
        if (balanceFactor(root) == 2)
        {
            if (balanceFactor(root->left) >= 0)
                root = RR(root);
            else
                root = LR(root);
        }
    }
    else if (compare(element, root) == -1)
    {
        root->left = Delete(root->left, element, compare, copy);
        if (balanceFactor(root) == -2)
        {
            if (balanceFactor(root->right) <= 0)
                root = LL(root);
            else
                root = RL(root);
        }
    }
    else
    {
        if (root->right != NULL)
        {
            temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            copy(root, temp);
            root->right = Delete(root->right, temp, compare, copy);
            if (balanceFactor(root) == 2)
            {
                if (balanceFactor(root->left) >= 0)
                    root = RR(root);
                else
                    root = LR(root);
            }
        }
        else return root->left;
    }
    root->height = height(root);
    return root;
}
avl_node_t *find(avl_node_t *root, void *element, int (*compare)(void *elementA, void *elementB))
{
    if (root == NULL)
        return NULL;
    if (compare(element,root) == 0)
        return root;
    else if (compare(element, root) == 1)
        return find(root->right, element, compare);
    else if(compare(element, root) == -1)
        return find(root->left, element, compare);
    else
    return NULL;
}
static avl_node_t *rotateright(avl_node_t *root)
{
    avl_node_t *leftchild = root->left;
    root->left = leftchild->right;
    leftchild->right = root;
    root->height = height(root);
    leftchild->height = height(leftchild);
    return leftchild;
}
static avl_node_t *rotateleft(avl_node_t *root)
{
    avl_node_t *rightchild = root->right;
    root->right = rightchild->left;
    rightchild->left = root;
    root->height = height(root);
    rightchild->height = height(rightchild);
    return rightchild;
}
static avl_node_t *RR(avl_node_t *node){return rotateright(node);}
static avl_node_t *LL(avl_node_t *node){return rotateleft(node);}
static avl_node_t *LR(avl_node_t *node)
{
    node->left = rotateleft(node->left);
    node = rotateright(node);
    return node;
}
static avl_node_t *RL(avl_node_t *node)
{
    node->right = rotateright(node->right);
    node = rotateleft(node);
    return node;
}
static int height(avl_node_t *node)
{
    int rh, lh;
    if (node == NULL)
        return 0;
    if (node->left == NULL)
        lh = 0;
    else
        lh = 1 + node->left->height;
    if (node->right == NULL)
        rh = 0;
    else
        rh = 1 + node->right->height;
    return (rh>lh)?rh:lh;
}
static int balanceFactor(avl_node_t *node)
{
    int rh, lh;
    if (node == NULL)
        return 0;
    if (node->left == NULL)
        lh = 0;
    else
        lh = 1 + node->left->height;
    if (node->right == NULL)
        rh = 0;
    else
        rh = 1 + node->right->height;
    return lh - rh;
}
void inorder(avl_node_t *root, void (*print)(void *))
{
    if (root == NULL) return;
    inorder(root->left, print);
    print(root);
    inorder(root->right, print);
}
void preorder(avl_node_t *root, void (*print)(void *))
{
    if (root == NULL)
        return;
    print(root);
    preorder(root->left, print);
    preorder(root->right, print);
}

