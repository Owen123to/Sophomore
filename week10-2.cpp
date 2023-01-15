#include<bits/stdc++.h>
using namespace std;
template<class T>
class Node
{
public:
    Node() : prev(NULL),next(NULL) {}
    Node(T data) : prev(NULL),next(NULL),data(data) {}
    Node(T data, Node<T> *prev, Node<T> *next) : prev(prev),next(next),data(data) {}
    T getData(){return data;}
    void setPrev(Node<T> *temp){prev = temp;}
    void setNext(Node<T> *temp){next = temp;}
    Node<T> *getPrev(){return prev;}
    Node<T> *getNext(){return next;}
private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};
template<class T>
class LinkedList
{
public:
    LinkedList() : head(NULL),tail(NULL) {}
    void addToTail(T data)
    {
        Node<T> *newNode = new Node<T> (data);
        if(this->head == NULL)
        {
            head = newNode;
            tail = newNode;
            return ;
        }
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
        return;
    }
    void addToHead(T data)
    {
        Node<T> *newNode = new Node<T> (data);
        if(this->head == NULL)
        {
            head = newNode;
            tail = newNode;
            return ;
        }
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
        return ;
    }
    Node<T> *removeFormHead()
    {
        if(head == NULL)
            return NULL;
        Node<T> *temp = head;
        head = head->getNext();
        if(head == NULL)
            tail = NULL;
        if(head!= NULL)
            head->setPrev(NULL);
        temp->setNext(NULL);
        return temp;
    }
    Node<T> *removeFormTail()
    {
        if(head == NULL)
            return NULL;
        Node<T> *temp = tail;
        tail = tail->getPrev();
        if(tail == NULL)
            head = NULL;
        if(tail!= NULL)
            tail->setNext(NULL);
        temp->setPrev(NULL);
        return temp;
    }
    void deleteData(T data)
    {
        Node<T> *temp = head;
        while(temp->getData() != data)
        {
            temp = temp->getNext();
            if(temp==tail && temp->getData()!=data)
            {
                delete temp;
                return ;
            }
        }
        if(temp == head && temp == tail)
        {
            head = tail = NULL;
            delete temp;
            return ;
        }
        if(temp == head)
        {
            head->getNext()->setPrev(NULL);
            head = head->getNext();
            delete temp;
            return ;
        }
        if(temp == tail)
        {
            tail->getPrev()->setNext(NULL);
            tail = tail->getPrev();
            delete temp;
            return ;
        }
        temp->getPrev()->setNext(temp->getNext());
        temp->getNext()->setPrev(temp->getPrev());
        delete temp;
        return ;
    }
    void deleteDatas(T data, int n)
    {
        while(n--)
            deleteData(data);
    }
    Node<T> *getHead(){return head;}
    Node<T> *getTail(){return tail;}
    friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
    {
        Node<T> *temp = n->getHead();
        while(temp!=NULL)
        {
            if(temp == n->getHead())
                out<<"(";
            if(temp==n->getTail())
               out<<temp->getData()<<")";
            if(temp!=n->getTail())
                out<<temp->getData()<<", ";
            temp = temp->getNext();
        }
        out<<endl;
        return out;
    }
private:
    Node<T> *head;
    Node<T> *tail;
};
template<class T>
class Queue
{
  public:
  Queue() {list = new LinkedList<T>;}
  void enqueue(T data) {list->addToTail(data);}
  T dequeue() {return list->removeFormHead()->getData();}
  T front() {return list->getHead()->getData();}
  LinkedList<T> *getlist(){return list;}
  bool isEmpty()
  {
    if(list->getHead() == NULL && list->getTail() == NULL)
    return true;
    return false;
  }
  int size()
  {
    int total = 0;
    Node<T> *temp = list->getHead();
    while(temp!=NULL)
    {
        total++;
        temp = temp->getNext();
    }
    return total;
  }
  bool only_null()
  {
    if(isEmpty()) return false;
    Node<T> *temp = list->getHead();
    while(temp!=list->getTail())
    {
        if(temp->getData() != nullptr) return false;
        temp = temp->getNext();
    }
    if(temp->getData()!= nullptr) return false;
    return true;
  }
  private:
    LinkedList<T> *list;
};
template<class T>
class TreeNode
{
  public:
    TreeNode(): height(0),left(NULL),right(NULL){}
    TreeNode(T _data,int h,TreeNode<T> *_left,TreeNode<T> *_right):data(_data),height(h),left(_left),right(_right){}
	void setHeight(int h){height = h;}
    void setData(T _data){data = _data;}
    void setLeft(TreeNode<T> *l){left = l;}
    void setRight(TreeNode<T> *r){right = r;}
    T getData() const {return data;}
	int getHeight() const {if(this == nullptr) return -1;else return height;}
    TreeNode<T> *getLeft() const {return left;}
    TreeNode<T> *getRight() const {return right;}
    int setheight(TreeNode<T>*tmp)
    {
        if(tmp == nullptr) return 0;
        int h = 0;
        (tmp->getLeft()->getHeight()>tmp->getRight()->getHeight())? h = tmp->getLeft()->getHeight()+1:h=tmp->getRight()->getHeight()+1;
        return h;
    }
  private:
    T data;
	int height;
    TreeNode<T> *left;
    TreeNode<T> *right;
};
int  all_compare(string temp,string tmp)
{
    if(temp[0] >='0'&&temp[0]<='9')
    {
        if(temp.size()>tmp.size()) return 1;
        else if(temp.size()<tmp.size()) return 0;
        else
        {
            for(int i = 0;i<temp.size();i++)
            {
                if(temp[i]<tmp[i]) return 0;
                else if(temp[i]>tmp[i]) return 1;
            }
            return 2;
        }
    }
    else if(temp == tmp) return 2;
    else if(temp>tmp) return 1;
    else return 0;
}
int max(int a,int b){return (a>b)?a:b;}
template<class T>
class AVL
{
	public:
	AVL() = default;
	AVL(TreeNode<T> *temp){this->root = temp;}
	void preorder()  {bool first = true; this->_preorder(first); cout << endl;}
    void inorder() {bool first = true ; this->_inorder(first); cout << endl;}
    void postorder()  {bool first = true ; this->_postorder(first); cout << endl;}
	void levelorder()
  	{
    	if(this->root == NULL) {cout << endl; return;}
    	Queue<TreeNode<T>*> tmp;
    	tmp.enqueue(this->root);
    	while(!tmp.isEmpty())
    	{
        	TreeNode<T> *curr = tmp.front();
        	tmp.dequeue();
        	if(curr != this->root) cout << ',';
        	cout << curr->getData();
        	if(curr->getLeft() != NULL) tmp.enqueue(curr->getLeft());
        	if(curr->getRight() != NULL) tmp.enqueue(curr->getRight());
    	}
    	cout << endl;
  	}
  	TreeNode<T> * getroot(){return this->root;}
	void setRoot(T data,int h)
  	{
    	if(this->root == NULL) this->root = new TreeNode<T>(data,h,NULL,NULL);
    	else
		{
			this->root->setData(data);
			this->root->setHeight(h);
		}
  	}
	TreeNode<T>* search(T target)
  	{
    	if(this->root == nullptr) return nullptr;
    	else if(target == this->root->getData()) return this->root;
    	else if(all_compare(target,this->root->getData()) == 1) return AVL(this->root->getRight()).search(target);
    	else return AVL(this->root->getLeft()).search(target);
  	}
    TreeNode<T>* treenode_balance(TreeNode<T>* tmp)
    {
        int temp = this->get_balance(tmp);
        if(temp>1)
        {
            if(this->get_balance(tmp->getLeft()) >= 0)
                return this->r_rotate(tmp);
            else
            {
                tmp->setLeft(this->l_rotate(tmp->getLeft()));
                return this->r_rotate(tmp);
            }
        }
        else if(temp < -1)
        {
            if(this->get_balance(tmp->getRight()) <= 0)
            return this->l_rotate(tmp);
            else
            {
                tmp->setRight(this->r_rotate(tmp->getRight()));
                return this->l_rotate(tmp);
            }
        }
        return tmp;
    }
	TreeNode<T>* insert(T data)
	{
        if(this->root == nullptr)
        {
            this->root = new  TreeNode<T>(data,0,nullptr,nullptr);
            return this->root;
        }
        if(all_compare(data,this->root->getData()) == 1)
            this->root->setRight(AVL(this->root->getRight()).insert(data));
        else if(all_compare(data,this->root->getData()) == 0)
            this->root->setLeft(AVL(this->root->getLeft()).insert(data));
        this->root->setHeight(this->root->setheight(this->root));
        this->root = this->treenode_balance(this->root);
        return this->root;
	}
    TreeNode<T>* delete_node(T data)
	{
        if(this->root == nullptr) return nullptr;
        if(all_compare(data,this->root->getData()) == 1)
            this->root->setRight(AVL(this->root->getRight()).delete_node(data));
        else if(all_compare(data,this->root->getData()) == 0)
            this->root->setLeft(AVL(this->root->getLeft()).delete_node(data));
        else
        {
            if(this->root->getLeft() == nullptr && this->root->getRight() == nullptr) return nullptr;
            else if(this->root->getLeft() == nullptr) return this->root->getRight();
            else if(this->root->getRight() == nullptr) return this->root->getLeft();
            else
            {
                TreeNode<T>* temp = this->findMaxValue(this->root->getLeft());
                T ttmp = this->root->getData();
                this->root->setData(temp->getData());
                temp->setData(ttmp);
                this->root->setLeft(AVL(this->root->getLeft()).delete_node(data));
            }
        }
        this->root->setHeight(this->root->setheight(this->root));
        return this->treenode_balance(this->root);
	}
    TreeNode<T>* findMaxValue(TreeNode<T>*tmp)
    {
        if(tmp->getRight() != nullptr)
            return this->findMaxValue(tmp->getRight());
        return tmp;
    }
    TreeNode<T>* r_rotate(TreeNode<T>* n)
    {
        TreeNode<T> *temp = n->getLeft();
        TreeNode<T> *tmp = temp->getRight();
        n->setLeft(tmp);
        temp->setRight(n);
        n->setHeight(n->setheight(n));
        temp->setHeight(temp->setheight(temp));
        return temp;
    }
    TreeNode<T>* l_rotate(TreeNode<T>* n)
    {
        TreeNode<T> *temp = n->getRight();
        TreeNode<T> *tmp = temp->getLeft();
        n->setRight(tmp);
        temp->setLeft(n);
        n->setHeight(n->setheight(n));
        temp->setHeight(temp->setheight(temp));
        return temp;
    }
    int get_balance(TreeNode<T>* temp)
    {
        if(temp == nullptr) return 0;
        return temp->getLeft()->getHeight() - temp->getRight()->getHeight();
    }
    string serialize()
    {
        string s = "";
        if(this->root == NULL) return s;
        Queue<TreeNode<T>*> tmp;
        tmp.enqueue(this->root);
        while(!tmp.isEmpty())
        {
            TreeNode<T> *curr = tmp.front();
            tmp.dequeue();
            TreeNode<T> *temp = nullptr;
            if(curr != this->root) s+=',';
            if(curr == nullptr)
                s += "NULL";
            if(curr!=nullptr)
            {
                s += (curr->getData());
                if(curr->getLeft()!=nullptr) tmp.enqueue(curr->getLeft());
                else  tmp.enqueue(temp);
                if(curr->getRight()!=nullptr) tmp.enqueue(curr->getRight());
                else  tmp.enqueue(temp);
            }
            if(tmp.only_null()) break;
        }
        return s;
    }

	TreeNode<T> *root = nullptr;
    void _preorder(bool &first)
    {
        if(this->root == NULL) return;
        if(first) {first = false; cout << this->root->getData();}//v
        else cout << ',' << this->root->getData();
        AVL(this->root->getLeft())._preorder(first);//L
        AVL(this->root->getRight())._preorder(first);//R
    }
    void _inorder(bool &first)
    {
        if(this->root == NULL) return;
        AVL(this->root->getLeft())._inorder(first);//L
        if(first) {first = false; cout << this->root->getData();}//v
        else cout << ',' << this->root->getData();
        AVL(this->root->getRight())._inorder(first);//R
    }
    void _postorder(bool &first)
    {
        if(this->root == NULL) return;
        AVL(this->root->getLeft())._postorder(first);//L
        AVL(this->root->getRight())._postorder(first);//R
        if(first) {first = false; cout << this->root->getData();}//v
        else cout << ',' << this->root->getData();
    }
};
int main()
{
    AVL<string> *tree = new AVL<string>();
    string aa,bb;
    while(cin>>aa>>bb)
    {
        if(aa == "insert") tree->root = tree->insert(bb);
        if(aa == "delete") tree->root = tree->delete_node(bb);
    }
    cout<<tree->serialize()<<endl;
	return 0;
}
