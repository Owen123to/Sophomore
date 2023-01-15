#include<bits/stdc++.h>
using namespace std;
/**
 * A Node class of Doublely Linked List class
 */
template<class T>
class Node {
  public:
  /**
   * Construct a new Node object with no parameter
   */
  Node() : prev(NULL),next(NULL){}
  /**
   * Construct a new Node object with parameter
   * @param data: data to put in
   */
  Node(T data) : prev(NULL),next(NULL),data(data){}
  /**
   * Construct a new Node object with parameters
   * @param data: data to put in
   * @param prev: pointer to the previous node
   * @param next: pointer to the next node
   */
  Node(T data, Node<T> *prev, Node<T> *next) : prev(prev),next(next),data(data){}
  T getData(){return data;}
  void setPrev(Node<T> *temp) {prev = temp;}
  void setNext(Node<T> *temp) {next = temp;}
  Node<T> *getPrev(){return prev;}
  Node<T> *getNext(){return next;}
  private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};

/**
 * A Doublely Linked List class
 */
template<class T>
class LinkedList {
  public:
  /**
   * Construct a new LinkedList object with no parameter
   */
  LinkedList() : head(NULL),tail(NULL){}
  /**
   * Add a node to the tail of the linked list
   * @param data: data to put in
   */
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
  /**
   * Add a node to the head of the linked list
   * @param data: data to put in
   */
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
  /**
   * Delete a node from the linked list with the given data from the head
   * If there are no data to be deleted, then do nothing
   * @param data: data to delete
   */
  void deleteData(T data)
  {
    Node<T> *temp = head;
    while(temp->getData() != data)
    {
        temp = temp->getNext();
        if(temp==tail && temp->getData()!=data)
        return ;
    }
    if(temp == head)
    {
      head->getNext()->setPrev(NULL);
      head = head->getNext();
      return ;
    }
    if(temp == tail)
    {
      tail->getPrev()->setNext(NULL);
      tail = tail->getPrev();
      return ;
    }
    temp->getPrev()->setNext(temp->getNext());
    temp->getNext()->setPrev(temp->getPrev());
    delete temp;
    return ;
  }
  /**
   * Delete valid n nodes from the linked list with the given data from the head
   * If there are no more data to be deleted, then just skip
   * @param data: data to delete
   * @param n: max number of nodes to delete
   */
  void deleteData(T data, int n)
  {
    Node<T> *temp = head;
    for(int i = 0;i!=n;)
    {
        while(temp->getData() != data)
        {
            temp = temp->getNext();
            if(temp==tail && temp->getData()!=data)
            return ;
        }
        if(temp == head)
        {
            head->getNext()->setPrev(NULL);
            head = head->getNext();
            i++;
        }
        if(temp == tail)
        {
            tail->getPrev()->setNext(NULL);
            tail = tail->getPrev();
            i++;
        }
        temp->getPrev()->setNext(temp->getNext());
        temp->getNext()->setPrev(temp->getPrev());
        i++;
        temp = temp->getNext();
    }
    return;
  }
  /**
   * Overload the operator << to print out all the data in the linked list from the head
   * There is a \n in the end of each print
   *
   * Output example:
   * If your linked list data is 5, 4, 3, 2, 1
   * then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
   */
  Node<T> *getHead() {return head;}
  Node<T> *getTail() {return tail;}
  friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
  {
    Node<T> *temp = n->getHead();
    while(temp!=NULL)
    {
      if(temp == n->getHead())
      cout<<"(";
     if(temp==n->getTail())
      cout<<temp->getData();
      if(temp == n->getTail())
      cout<<")";
      if(temp!=n->getTail())
      cout<<temp->getData()<<", ";
      temp = temp->getNext();
    }
    cout<<endl;
    return out;
  }
  private:
    Node<T> *head;
    Node<T> *tail;
};
int main()
{
LinkedList<int> link;
    link.addToTail(1);
    link.addToTail(2);
    link.addToHead(3);
    link.addToTail(4);
    link.addToTail(4);
    link.addToTail(4);
    cout << &link;
    link.deleteData(2);
    cout << &link;
    link.deleteData(4,2);
    cout << &link;
}