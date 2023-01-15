#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tree
{
public:
 Tree()
 {
  root = 0;
  int j, k;
  for (j = 0; j < 20; j++)
   for (k = 0; k < 4; k++)
    node[j][k] = -1;
 }
 int insert(int n)
 {
  int f = root, index = 0;
  while (node[index][0] != -1)
   index++;
  if (index >= 20)
   return -1;
  if (node[root][0] == -1)
  {
   node[root][0] = 1;
   node[root][1] = n;
   return 1;
  }
  else
  {
   node[index][0] = 1;
   node[index][1] = n;
   while (1)
   {
    if (node[f][1] < n)
    {
     if (node[f][3] == -1)
     {
      node[f][3] = index;
      return 1;
     }
     else
     {
      f = node[f][3];
     }
    }
    else
    {
     if (node[f][2] == -1)
     {
      node[f][2] = index;
      return 1;
     }
     else
     {
      f = node[f][2];
     }
    }
   }
  }
 }
 void inorder(int tmp)
 {
  if (node[tmp][0] != 1)
   return;
  if (node[tmp][2] != -1)
   inorder(node[tmp][2]);
  cout << node[tmp][1] << " ";
  if (node[tmp][3] != -1)
   inorder(node[tmp][3]);
 }
 void preorder(int tmp)
 {
  if (node[tmp][0] != 1)
   return;
  cout << node[tmp][1] << " ";
  if (node[tmp][2] != -1)
   preorder(node[tmp][2]);
  if (node[tmp][3] != -1)
   preorder(node[tmp][3]);
 }
 void postorder(int tmp)
 {
  if (node[tmp][0] != 1)
   return;
  if (node[tmp][2] != -1)
   postorder(node[tmp][2]);
  if (node[tmp][3] != -1)
   postorder(node[tmp][3]);
  cout << node[tmp][1] << " ";
 }
 void levelorder()
 {
  int i = -1;
  while (node[++i][0] != -1)
  {
   cout << node[i][1] << " ";
  }
 }

private:
 int node[20][4];
 int root;
};

int main()
{
 Tree *tree = new Tree();
 int j, node;
 srand(time(NULL));
 for (j = 0; j < 10; j++)
 {
  node = rand() % 10;
  tree->insert(node);
 }
 tree->inorder(0);
 printf("\n");
 tree->preorder(0);
 printf("\n");
 tree->postorder(0);
 printf("\n");
 tree->levelorder();
 printf("\n");
}