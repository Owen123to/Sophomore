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
  private: 
    LinkedList<T> *list;
};
template<class T>
class TreeNode 
{
  public: 
    TreeNode(): left(NULL),right(NULL){}
    TreeNode(T _data,TreeNode<T> *_left,TreeNode<T> *_right):data(_data), left(_left), right(_right){}
    void setData(T _data){data = _data;}
    void setLeft(TreeNode<T> *l){left = l;}
    void setRight(TreeNode<T> *r){right = r;}
    T getData() const {return data;}
    TreeNode<T> *getLeft() const {return left;}
    TreeNode<T> *getRight() const {return right;}
  private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
};
template<class T>
class binarySearchTree 
{
  public:
    virtual void preorder() = 0;
    virtual void inorder() = 0;
    virtual void postorder() = 0;
    virtual void levelorder() = 0;
    virtual bool insert(T data) = 0;
    virtual void setRoot(T data) = 0;
    virtual bool search(T target) = 0;
  protected:
    TreeNode<T> *root = NULL;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> 
{
  public:
  BinarySearchTree() = default;
  BinarySearchTree(TreeNode<T> *temp){this->root = temp;}
  virtual void preorder() override {bool first = true; this->_preorder(first); cout << endl;}
  virtual void inorder() override {bool first = true ; this->_inorder(first); cout << endl;}
  virtual void postorder() override {bool first = true ; this->_postorder(first); cout << endl;}
  virtual void levelorder() override
  {
    if(this->root == NULL) {cout << endl; return;}
    Queue<TreeNode<T> *> tmp;
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
  virtual bool insert(T data) override
  {
    if(this->root == NULL) this->root = new TreeNode<T>(data, NULL, NULL);
    else if(data == this->root->getData()) return false;
    else if(data > this->root->getData())
    {
        if(this->root->getRight() == NULL) this->root->setRight(new TreeNode<T>(data, NULL, NULL));
        else return BinarySearchTree(this->root->getRight()).insert(data);
    }
    else
    {
        if(this->root->getLeft() == NULL) this->root->setLeft(new TreeNode<T>(data, NULL, NULL));
        else return BinarySearchTree(this->root->getLeft()).insert(data);
    }
    return true;
  }
  virtual void setRoot(T data) override
  {
    if(this->root == NULL) this->root = new TreeNode<T>(data, NULL, NULL);
    else this->root->setData(data);
  }
  virtual bool search(T target) override
  {
    if(this->root == NULL) return false;
    else if(target == this->root->getData()) return true;
    else if(target > this->root->getData()) return BinarySearchTree(this->root->getRight()).search(target);
    else return BinarySearchTree(this->root->getLeft()).search(target);
  }
  private:
    void _preorder(bool &first)
    {
        if(this->root == NULL) return;
        if(first) {first = false; cout << this->root->getData();}//v
        else cout << ',' << this->root->getData();
        BinarySearchTree(this->root->getLeft())._preorder(first);//L
        BinarySearchTree(this->root->getRight())._preorder(first);//R
    } 
    void _inorder(bool &first)
    {
        if(this->root == NULL) return;
        BinarySearchTree(this->root->getLeft())._inorder(first);//L
        if(first) {first = false; cout << this->root->getData();}//v
        else cout << ',' << this->root->getData();
        BinarySearchTree(this->root->getRight())._inorder(first);//R
    }
    void _postorder(bool &first)
    {
        if(this->root == NULL) return;
        BinarySearchTree(this->root->getLeft())._postorder(first);//L
        BinarySearchTree(this->root->getRight())._postorder(first);//R
        if(first) {first = false; cout << this->root->getData();}//v
        else cout << ',' << this->root->getData();
    }
};