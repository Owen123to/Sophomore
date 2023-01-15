#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Tree
{
public:
	Tree()
	{
		int j;
		for(j = 0;j < 2000;j ++)
			root[j] = -1;
	}
	int insert(int node)
	{
		int index = 0;
		while(index < 2000 && root[index] != -1)
		{
			if(root[index] < node)
				index = index * 2 + 2;
			else
				index = index * 2 + 1;
		}
		root[index] = node;
	}
	void inorder(int index)
	{
        if(root[index] == -1) return;
        inorder(index * 2 + 1);
		cout<<root[index]<<" ";
		inorder(index * 2 + 2);
	}
	void preorder(int index)
	{
		if(root[index] == -1) return;
		cout<<root[index]<<" ";
        preorder(index * 2 + 1);
		preorder(index * 2 + 2);
	}
	void postorder(int index)
	{
		if(root[index] == -1) return;
        postorder(index * 2 + 1);
		postorder(index * 2 + 2);
		cout<<root[index]<<" ";
	}
	void levelorder()
	{
		for(int i = 0;i<2000;i++)
			if(root[i]!=-1)
			cout<<root[i]<<" ";
	}
private:
	int root[2000];
};

int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand();
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
