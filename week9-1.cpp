#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>
#include <stack>
using namespace std;
template<class T>
class Node
{
public:
	Node(){data = new T;}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d){*data = d;}
	T &getData() const{return *data;}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const{return next;}
	ListNode *getPrev() const{return prev;}
	void setNext(ListNode *n){next = n;}
	void setPrev(ListNode *p){prev = p;}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}
	ListNode<T> *gethead(){return head;}
	ListNode<T> *gettail(){return tail;}
protected:
	ListNode<T> *head, *tail;
};
template<class T>
class TreeNode : public Node<T>
{
public:
	TreeNode() : Node<T>(){size = 0;child = new LinkList<TreeNode<T> *>();}
	TreeNode(T d) : Node<T>(d){size = 0;child = new LinkList<TreeNode<T> *>();}
	void addChild(TreeNode *n){++size;child->addFromTail(*n);}
	void addChild(T d)
	{
		++size;
		TreeNode<T> *temp = new TreeNode<T>(d);
		child->addFromTail(temp);
	}
	TreeNode<T> *operator[](int n)
	{
		return (*child)[n].getData();
	}
	int getsize(){return size;}
	LinkList<T> *getchild(){return child;}
private:
	int size;
	LinkList<TreeNode<T> *> *child;
};
template<class T>
class Tree
{
public:
	Tree(){root = nullptr;}
	TreeNode<T> *operator[](int n)
	{
		if(root == nullptr) return nullptr;
		queue<TreeNode<T>*> store;
		TreeNode<T> *temp;
		store.push(root);
		while(!store.empty())
		{
			temp = store.front();
			store.pop();
			if(n == 0)
			return temp;
			n--;
			for(int i = 0;i<temp->getsize();i++)
			store.push((*temp)[i]);
		}
		return nullptr;
	}
	int count()
	{
		if(root == nullptr) return 0;
		queue<TreeNode<T>*> store;
		int sum = 0;
		TreeNode<T> *temp;
		store.push(root);
		while(!store.empty())
		{
			temp = store.front();
			store.pop();
			++sum;
			for(int i = 0;i<temp->getsize();i++)
			store.push((*temp)[i]);
		}
		return sum;
	}
	void levelOrder()
	{
		if(root == nullptr) return;
		queue<TreeNode<T>*> store;
		TreeNode<T> *temp;
		store.push(root);
		while(!store.empty())
		{
			temp = store.front();
			store.pop();
			cout<<temp->getData()<<" ";
			for(int i = 0;i<temp->getsize();i++)
			store.push((*temp)[i]);
		}
		cout<<endl;
	}
	void preorder()
	{
		stack<TreeNode<T>*> store;
		TreeNode<T> *temp;
		store.push(root);
		while(!store.empty())
		{
			temp = store.top();
			store.pop();
			cout<<temp->getData()<<"";
			for(int i = temp->getsize();i>0;--i)
				store.push((*temp)[i-1]);
		}
		cout<<endl;
	}
	void postorder()
	{
		stack<TreeNode<T>*> store1;
		stack<TreeNode<T>*> store2;
		TreeNode<T> *temp;
		store1.push(root);
		while(!store1.empty())
		{
			temp = store1.top();
			store1.pop();
			store2.push(temp);
			for(int i = 0;i<temp->getsize();++i)
			store1.push((*temp)[i]);
		}
		while(!store2.empty())
		{
			cout<<store2.top()->getData()<<" ";
			store2.pop();
		}
		cout<<endl;
	}
	void setRoot(T d){root = new TreeNode<T>(d);}
	TreeNode<T> *getroot(){return root;}
private:
	TreeNode<T> *root;
};

int main()
{
	Tree<int> *tree = new Tree<int>();
	srand(0);
	int j, k;
	for(j = 0;j < 20;j ++)
	{
		if(tree->count() == 0)
			tree->setRoot(rand() % 100);
		else
		{
			k = rand() % tree->count();
			(*tree)[k]->addChild(rand() % 100);
		}
	}
	tree->levelOrder();
	tree->preorder();
	tree->postorder();
}
