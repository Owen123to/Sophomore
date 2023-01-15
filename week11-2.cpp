#include<iostream>
using namespace std;
typedef enum {red = 0,black} Color;
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
template<class T>
class tree_Node
{
    public:
    tree_Node():color(red),left(nullptr),right(nullptr),parent(nullptr){}
    tree_Node(T data):key(data),color(red),left(nullptr),right(nullptr),parent(nullptr){}
    void setparent(tree_Node<T> *temp){parent = temp;}
    void setright(tree_Node<T> *temp){right = temp;}
    void setleft(tree_Node<T> *temp){left = temp;}
    void setkey(T temp){key = temp;}
    void setcolor(Color temp){color = temp;}
    tree_Node<T> *getparent(){return parent;}
    tree_Node<T> *getright(){return right;}
    tree_Node<T> *getleft(){return left;}
    T getkey(){return key;}
    Color getcolor(){return color;}
    private:
    Color color;
    T key;
    tree_Node<T> *left;
    tree_Node<T> *right;
    tree_Node<T> *parent;
};
template<class T>
class RBT
{
    public:
    RBT() = default;
    void LR(tree_Node<T> *x)
    {
        tree_Node<T> *x_r = x->getright();
        tree_Node<T> *x_l = x->getright()->getleft();
        x->setright(x_l);
        if(x->getparent() == nullptr) this->root = x_r;
        else if(x->getparent()->getleft() == x) x->getparent()->setleft(x_r);
        else x->getparent()->setright(x_r);
        if(x->getleft()!=nullptr) x_l->setparent(x);
        x_r->setparent(x->getparent());
        x_r->setleft(x);
        x->setparent(x_r);
    }
    void RR(tree_Node<T> *y)
    {
        tree_Node<T> *y_r = y->getleft()->getright();
        tree_Node<T> *y_l = y->getleft();
        y->setleft(y_r);
        if(y_r!=nullptr) y_r->setparent(y);
        if(y->getparent()==nullptr) root = y_l;
        else if(y->getparent()->getleft() == y)
            y->getparent()->setleft(y_l);
        else y->getparent()->setright(y_l);
        if(y->getleft()!=nullptr) y_r->setparent(y);
        y_l->setparent(y->getparent());
        y_l->setright(y);
        y->setparent(y_l);
    }
    tree_Node<T> *rMost(tree_Node<T> *cur)
    {
        while(cur->getright()!=nullptr)
            cur = cur->getright();
        return cur;
    }
    tree_Node<T> *search(T data)
    {
        tree_Node<T> *cur = root;
        while(cur!=nullptr && all_compare(data,cur->getkey())!=2)
             (all_compare(data,cur->getkey()) == 1)? cur = cur->getright():cur = cur->getleft();
        return cur;
    }
    tree_Node<T> *insert_Element(T data)
    {
        tree_Node<T> *insert_node = new tree_Node<T>(data);
        this->root = insert(root,insert_node);
        insert_fix(insert_node);
        return root;
    }
    tree_Node<T> *insert(tree_Node<T>*root,tree_Node<T> *node)
    {
        if(root == nullptr) return node;
        if(all_compare(root->getkey(),node->getkey()) == 1)
        {
            root->setleft(insert(root->getleft(),node));
            root->getleft()->setparent(root);
        }
        else if(all_compare(root->getkey(),node->getkey()) == 0)
        {
            root->setright(insert(root->getright(),node));
            root->getright()->setparent(root);
        }
        return root;
    }
    void insert_fix(tree_Node<T> *cur)
    {
        while(cur!=root&&cur->getparent()->getcolor() == red)
        {
            tree_Node<T> *pa = cur->getparent();
            tree_Node<T> *gp = pa->getparent();
            tree_Node<T> *uncle = nullptr;
            if(pa == gp->getleft())
            {
                uncle = gp->getright();
                if(uncle!=nullptr&&uncle->getcolor() == red)
                {
                    uncle->setcolor(black);
                    pa->setcolor(black);
                    gp->setcolor(red);
                    cur = gp;
                }
                else
                {
                    if(cur == pa->getright())
                    {
                        LR(pa);
                        pa = cur;
                        cur = pa->getleft();
                    }
                    gp->setcolor(red);
                    pa->setcolor(black);
                    RR(gp);
                }
            }
            else
            {
                uncle = gp->getleft();
                if(uncle!=nullptr&&uncle->getcolor() == red)
                {
                    pa->setcolor(black);
                    uncle->setcolor(black);
                    gp->setcolor(red);
                    cur = gp;
                }
                else
                {
                    if(cur == pa->getleft())
                    {
                        RR(pa);
                        pa = cur;
                        cur = pa->getright();
                    }
                    pa->setcolor(black);
                    gp->setcolor(red);
                    LR(gp);
                }
            }
        }
        root->setcolor(black);
    }
    tree_Node<T> *remove(T data)
    {
        tree_Node<T> *d = search(data);
        if(d == nullptr) return this->root;
        tree_Node<T> *x;
        tree_Node<T> *pa = nullptr;
        Color temp;
        if(d->getleft()!=nullptr&&d->getright()!=nullptr)
        {
            x = rMost(d->getleft());
            d->setkey(x->getkey());
            d = x;
        }
        if(d->getright() != nullptr)
        {
            x = d;
            d = d->getright();
            d->setparent(x->getparent());
            pa = x->getparent();
        }
        else if(d->getleft()!=nullptr)
        {
            x = d;
            d = d->getleft();
            d->setparent(x->getparent());
            pa = x->getparent();
        }
        else
        {
            x = d;
            d = nullptr;
            pa = x->getparent();
        }
        if(pa!=nullptr)
        {
            if(pa->getleft() == x)
            pa->setleft(d);
            else pa->setright(d);
        }
        else this->root = d;
        temp = x->getcolor();
        delete x;
        if(this->root == nullptr) return nullptr;
        if(temp == black)
            remove_fix(d,pa);
        return this->root;
    }
    void remove_fix(tree_Node<T> *cur,tree_Node<T> *pa)
    {
        while(cur!=this->root && (cur==nullptr||cur->getcolor() == black))
        {
            if(cur == pa->getleft())
            {
                tree_Node<T> *sib = pa->getright();
                if(sib!=nullptr&&sib->getcolor() == red)
                {
                    sib->setcolor(black);
                    pa->setcolor(red);
                    LR(pa);
                    sib = pa->getright();
                }
                if((sib->getleft() == nullptr||sib->getleft()->getcolor() == black)&&(sib->getright() == nullptr||sib->getright()->getcolor()==black))
                {
                    sib->setcolor(red);
                    cur = pa;
                    pa = cur->getparent();
                }
                else
                {
                    if((sib->getright() == nullptr||sib->getright()->getcolor() == black))
                    {
                        sib->getleft()->setcolor(black);
                        sib->setcolor(red);
                        RR(sib);
                        sib = pa->getright();
                    }
                    sib->setcolor(pa->getcolor());
                    pa->setcolor(black);
                    sib->getright()->setcolor(black);
                    LR(pa);
                    cur = this->root;
                }
            }
            else
            {
                tree_Node<T> *sib = pa->getleft();
                if(sib!=nullptr&&sib->getcolor()==red)
                {
                    sib->setcolor(black);
                    pa->setcolor(red);
                    RR(pa);
                    sib = pa->getleft();
                }
                if((sib->getleft() == nullptr||sib->getleft()->getcolor() == black)&&(sib->getright() == nullptr||sib->getright()->getcolor()==black))
                {
                    sib->setcolor(red);
                    cur = pa;
                    pa = cur->getparent();
                }
                else
                {
                    if(sib->getleft() == nullptr||sib->getleft()->getcolor()==black)
                    {
                        sib->getright()->setcolor(black);
                        sib->setcolor(red);
                        LR(sib);
                        sib = pa->getleft();
                    }
                    sib->setcolor(pa->getcolor());
                    pa->setcolor(black);
                    sib->getleft()->setcolor(black);
                    RR(pa);
                    cur = this->root;
                }
            }
        }
        cur->setcolor(black);
    }
    string serialize()
    {
        string s = "";
        if(this->root == NULL) return s;
        Queue<tree_Node<T>*> tmp;
        tmp.enqueue(this->root);
        while(!tmp.isEmpty())
        {
            tree_Node<T> *curr = tmp.front();
            tmp.dequeue();
            tree_Node<T> *temp = nullptr;
            if(curr != this->root) s+=',';
            if(curr == nullptr)
                s += "NULL";
            if(curr!=nullptr)
            {
                s += (curr->getkey());
                if(curr->getleft()!=nullptr) tmp.enqueue(curr->getleft());
                else  tmp.enqueue(temp);
                if(curr->getright()!=nullptr) tmp.enqueue(curr->getright());
                else  tmp.enqueue(temp);
            }
            if(tmp.only_null()) break;
        }
        return s;
    }
    //private:
    tree_Node<T> *root = nullptr;
};
int main()
{
    RBT<string> *tree = new RBT<string>();
    string aa,bb;
    while(cin>>aa>>bb)
    {
        if(aa == "insert") tree->root = tree->insert_Element(bb);
        if(aa == "delete") tree->root = tree->remove(bb);
    }
    cout<<tree->serialize()<<endl;
	return 0;
}
