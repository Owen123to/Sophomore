#include<iostream>
#include<cstdlib>
#include<stack>
#include<queue>
using namespace std;
template<class T>
class Node
{
public:
    Node() : prev(NULL),next(NULL) {}
    Node(T data) : prev(NULL),next(NULL),data(data) {}
    Node(T data, Node<T> *prev, Node<T> *next) : prev(prev),next(next),data(data) {}
    T getData(){return data;}
    Node<T> &setData(T temp){data = temp;return data;}
    Node<T> *setPrev(Node<T> *temp){prev = temp;return prev;}
    Node<T> *setNext(Node<T> *temp){next = temp;return next;}
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
    void addFront(Node<T> *at,T d)
    {
        Node<T> *temp = new Node<T>(d,at->getPrev(),at);
        if(at->getPrev()!=nullptr) at->getPrev()->setNext(temp);
        at->setPrev(temp);
        if(head == at) head = temp;
    }
    void addAfter(Node<T> *at,T d)
    {
        Node<T> *temp = new Node<T>(d,at,at->getNext());
        if(at->getNext()!=nullptr) at->getNext()->setPrev(temp);
        at->setNext(temp);
        if(tail == at) tail = temp;
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
    unsigned int getSize()
    {
        if(head == NULL)
            return 0;
        unsigned int count = 1;
        Node<T> *temp = head;
        while(temp->getNext()!=NULL)
        {
            temp = temp->getNext();
            count++;
        }
        return count;
    }
    void reverse()
    {
        Node<T> *current = head;
        Node<T> *prev_t = NULL,*next_t = NULL;
        tail = head;
        while(current != NULL)
        {
            next_t = current->getNext();
            current->setNext(prev_t);
            current->setPrev(next_t);
            prev_t = current;
            current = next_t;
        }
        head = prev_t;
    }
    bool exist(T d)
    {
        Node<T> *temp = head;
        while(temp != NULL)
        {
            if(temp->getData()==d)
            return true;
            temp = temp->getNext();
        }
        return false;
    }
    T getdata(unsigned int k)
    {
        Node<T> *temp = head;
        while(k--)
            temp = temp->getNext();
        return temp->getData();
    }
    void setdata(unsigned int g,T ttmp)
    {
        Node<T> *temp = head;
        while(g--)
            temp = temp->getNext();
        temp->setData(ttmp);
    }
    Node<T> &operator[](int i)
    {
        Node<T> *temp = head;
        for(int k = 0;k<i&&temp !=NULL;k++)
            temp = temp->getNext();
        if(temp == NULL)
            throw invalid_argument("No index in LK.\n");
        return *temp;
    }
    Node<T> *setHead(Node<T> *temp){head = temp;return head;}
    Node<T> *setTail(Node<T> *temp){tail = temp;return tail;}
    Node<T> *getHead(){return head;}
    Node<T> *getTail(){return tail;}
    friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
    {
        Node<T> *temp = n->getHead();
        while(temp!=NULL)
        {
            out<<temp->getData();
            temp = temp->getNext();
        }
        return out;
    }
private:
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
class TreeNode
{
  public:
    virtual LinkedList<TreeNode<T>*> *getChildren() = 0;
    virtual LinkedList<TreeNode<T>*> *setChildren(LinkedList<TreeNode<T>*>*) = 0;
    virtual T getData() = 0;
    virtual T &setData(T) = 0;
  protected:
    T data;
    LinkedList<TreeNode<T>*>* children;
};
template<class T, class D>
class Tree
{
  public:
    virtual void insert(D data) = 0;
    virtual bool search(D data) = 0;
    virtual TreeNode<T> *getroot() = 0;
    virtual void print(TreeNode<T> *) = 0;
  protected:
    TreeNode<T>* root;
};

template<class T>
class GeneralTreeNode : public TreeNode<T>
{
    public:
    GeneralTreeNode() {this->children = new LinkedList<TreeNode<T>*>();end = false;}
    GeneralTreeNode(T d) {this->data = d;this->children = new LinkedList<TreeNode<T>*>();end = false;}
    virtual LinkedList<TreeNode<T>*>* getChildren() override {return this->children;}
    virtual LinkedList<TreeNode<T>*>* setChildren(LinkedList<TreeNode<T>*>* temp) override {this->children = temp;return this->children;}
    bool getend(){return end;}
    bool &setend(bool temp){end = temp;return end;}
    virtual T getData() override {return this->data;}
    virtual T &setData(T temp) override {this->data = temp;return this->data;}
    private:
    bool end;
};

template<class T, class D>
class GeneralTree : public Tree<T, D>
{
  public:
    GeneralTree(){this -> root = new GeneralTreeNode<T>();}
    TreeNode<T> *getroot(){return this->root;}
    virtual void insert(D data) override
    {
        LinkedList<TreeNode<T> *>*temp_child = this->getroot()->getChildren();
        Node<TreeNode<T>*> *temp_node = temp_child->getHead();
        for(int i = 0;i<data.size();i++)
        {
            if(temp_node == nullptr) {temp_child->addToHead(new GeneralTreeNode<T>(data[i]));temp_node = temp_child->getHead();}
            else
            {
                while(temp_node->getNext()!=nullptr&&temp_node->getNext()->getData()->getData()<=data[i]) temp_node = temp_node->getNext();
                if(temp_node->getData()->getData()<data[i]) {temp_child->addAfter(temp_node,new GeneralTreeNode<T>(data[i]));temp_node = temp_node->getNext();}
                else if(temp_node->getData()->getData()>data[i]) {temp_child->addFront(temp_node,new GeneralTreeNode<T>(data[i]));temp_node = temp_node->getPrev();}
            }
            if(i == data.size()-1) {((GeneralTreeNode<T>*)(temp_node->getData()))->setend(true);return ;}
            temp_child = temp_node->getData()->getChildren();
            temp_node = temp_child->getHead();
        }
    }
    virtual bool search(D data) override
    {
        LinkedList<TreeNode<T> *>*temp_child = this->getroot()->getChildren();
        Node<TreeNode<T>*> *temp_node = temp_child->getHead();
        for(int i = 0;i<data.size();i++)
        {
            if(temp_node == nullptr) return false;
            while(temp_node->getNext()!=nullptr&&temp_node->getNext()->getData()->getData()<=data[i]) temp_node = temp_node->getNext();
            if(temp_node->getData()->getData()!=data[i]) return false;
            if(i == data.size()-1) {return ((GeneralTreeNode<T>*)(temp_node->getData()))->getend();}
            temp_child = temp_node->getData()->getChildren();
            temp_node = temp_child->getHead();
        }
        return false;
    }
    virtual void print(TreeNode<T> *node) override
    {
        if(node == this->getroot()) cout<<"{\"root\":";
        cout<<"{\"children\":[";
        for(Node<TreeNode<T>*>*temp = node->getChildren()->getHead();temp!=nullptr;temp = temp->getNext())
        {
            print(temp->getData());
            if(temp->getNext()!=nullptr) cout<<",";
        }
        cout<<"],\"data\":";
        if(node == this->getroot()) cout<<"\"\"";
        else cout<<"\""<<node->getData()<<"\"";
        if(((GeneralTreeNode<T>*)node)->getend()) cout<<",\"end\":\"true\"";
        cout<<"}";
        if(node == this->getroot()) cout<<"}";
    }
};


int main()
{
    GeneralTree<char,string> *D_tree = new GeneralTree<char,string>();
    int n = 0,m = 0;
    string tmp;
    cin>>n>>m;
    while(n--)
    {
        cin>>tmp;
        D_tree->insert(tmp);
    }
    while(m--)
    {
        cin>>tmp;
        cout<<D_tree->search(tmp)<<endl;
    }
    D_tree->print(D_tree->getroot());
    cout<<endl;
    return 0;
}
