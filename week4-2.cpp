#include<bits/stdc++.h>
using namespace std;
template<class T>
class Node
{
public:
    Node() : prev(NULL),next(NULL) {}
    Node(T data) : prev(NULL),next(NULL),data(data) {}
    Node(T data, Node<T> *prev, Node<T> *next) : prev(prev),next(next),data(data) {}
    T getData()
    {
        return data;
    }
    void setPrev(Node<T> *temp)
    {
        prev = temp;
    }
    void setNext(Node<T> *temp)
    {
        next = temp;
    }
    Node<T> *getPrev()
    {
        return prev;
    }
    Node<T> *getNext()
    {
        return next;
    }
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
    Node<T> *getHead()
    {
        return head;
    }
    Node<T> *getTail()
    {
        return tail;
    }
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
class Stack
{
public:
    Stack()
    {
        list = new LinkedList<T>;
    }
    void push(T data)
    {
        list->addToTail(data);
    }
    T pop()
    {
        return list->removeFormTail()->getData();
    }
    T top()
    {
        return list->getTail()->getData();
    }
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
void compare (Stack<int> *i,Stack<int> *j)
{
    if(i->isEmpty()&&j->isEmpty())
        return;
    else if(j->isEmpty() || (!i->isEmpty()&&(i->top()<j->top())))
    {
        j->push(i->pop());
        return ;
    }
    else if(i->isEmpty() || (!j->isEmpty()&&(i->top()>j->top())))
    {
        i->push(j->pop());
        return ;
    }
}
int main()
{
    int disks = 0;
    while(scanf("%d",&disks)!=EOF)
    {
        Stack<int> *A = new Stack<int>();
        Stack<int> *B = new Stack<int>();
        Stack<int> *C = new Stack<int>();
        for(int i = disks; i>0; i--)
                A->push(i);
        int count = 0;
        if(disks%2 != 0)
        {
            while(1)
            {
                compare(A,C);
                count++;
                if(C->size() == disks)
                    break;
                compare(A,B);
                count++;
                if(C->size() == disks)
                    break;
                compare(B,C);
                count++;
                if(C->size() == disks)
                    break;
            }
        }
        else
        {
            while(1)
            {
                compare(A,B);
                count++;
                if(C->size() == disks)
                    break;
                compare(A,C);
                count++;
                if(C->size() == disks)
                    break;
                compare(B,C);
                count++;
                if(C->size() == disks)
                    break;
            }
        }
        delete A,B,C;
        cout<<count<<endl;
    }
    return 0;
}
