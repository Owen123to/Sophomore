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
    //private:
    LinkedList<T> *list;
};
int first = 0;
bool err_exp(string aa)
{
    for(int i = 0; i<aa.length(); i++)
    {
        if((aa[i] == '+'&&aa[i+1] == '+') ||(aa[i] == '*'&&aa[i+1] == '*') ||(aa[i] == '/'&&aa[i+1] == '/') ||(aa[i] == '^'&&aa[i+1] == '^'))
        {
            cout<<"ERROR"<<endl;
            return 1;
        }
        else if((aa[i] == '+'&&(!isdigit(aa[i-1])||!isdigit(aa[i+1])))||(aa[i] == '-'&&aa[i+1] == '\0')||(aa[i] == '*'&&(!isdigit(aa[i-1])||!isdigit(aa[i+1])))||(aa[i] == '/'&&(!isdigit(aa[i-1])||!isdigit(aa[i+1])))||(aa[i] == '^'&&(!isdigit(aa[i-1])||!isdigit(aa[i+1]))))
        {
            cout<<"ERROR"<<endl;
            return 1;
        }
        else if(aa[i] == '(')
        {
            int count1 = 1;
            for(int j = i+1; j<aa.length(); j++)
            {
                if(aa[j] == '(')
                    count1++;
                else if(aa[j] == ')')
                    count1--;
            }
            if(count1!=0)
            {
                cout<<"ERROR"<<endl;
                return 1;
            }
        }
    }
}
int get_operator(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;
    if(ch == '*' || ch == '/')
        return 2;
    if(ch == '^')
        return 3;
    else return 0;
}
string  get_digit(string bb,int index)
{
    string temp2 = "";
    temp2+=bb[index];
    for(int j = index+1; j<bb.length(); j++)
    {
        if(bb[j]>='0'&&bb[j]<='9' || bb[j]=='.')
        {
            temp2+=bb[j];
            if(j == bb.length()-1)
                first = j;
        }
        else if(bb[j]<='0'||bb[j]>='9'|bb[j]!='.')
        {
            first = j;
            break;
        }
    }
    return temp2;
}
string change_impression(string cc)
{
    Stack<char> stack1;
    string temp2 = "";
    for(first = 0;cc[first]!='\0';first++)
    {
        if(cc[first] == '(')
            stack1.push(cc[first]);
        else if(cc[first] == ')')
        {
            while(stack1.top()!='(')
                temp2 = temp2 +stack1.pop()+" ";
            stack1.pop();
        }
        else if(cc[first] == '-'&&isdigit(cc[first+1])&&!isdigit(cc[first-1]))
            temp2 += get_digit(cc,first) + " ";
        else if(cc[first] == '+'||cc[first] == '-' ||cc[first] == '*' || cc[first] == '/' || cc[first] == '^')
        {
            if(stack1.isEmpty())
                stack1.push(cc[first]);
            else
            {
                if(get_operator(stack1.top())>=get_operator(cc[first]))
                {
                    temp2 = temp2+stack1.pop()+" ";
                    stack1.push(cc[first]);
                }
                else
                    stack1.push(cc[first]);
            }
        }
        else
            temp2 += get_digit(cc,first) + " ";
    }
    if(!stack1.isEmpty())
        while(!stack1.isEmpty())
            temp2 = temp2 + stack1.pop()+ " ";
    return temp2;
}

int main()
{
    string aa;
    cin>>aa;
    std::cout << change_impression(aa);
}

