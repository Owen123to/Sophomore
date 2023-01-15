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
bool decide(char a,char b,char c)
{
    if(b == '+'||b=='*'||b=='/'||b=='^')
    {
        if(a=='-'||a==')'||isdigit(a))
            if(c=='-'||c=='('||isdigit(c))
                return false;
        return true;
    }
    else if(b=='-')
    {
        if(a==' '||c==' '||c=='\0')
            return true;
        return false;
    }
    else if(b=='(')
    {
        if(a==' '||isdigit(a))
            return true;
        if(isdigit(c)||c=='('||c==')'||c=='-')
            return false;
        return true;
    }
    else
    {
        if(isdigit(a)||a=='('||a==')')
            if(c!=' '&&!isdigit(c))
            return false;
        return true;
    }
}
bool err_exp(string aa)
{
    for(int i = 0; i<aa.length(); i++)
    {
        if(aa[i] == '+'||aa[i]=='-'||aa[i]=='*'||aa[i]=='/'||aa[i]=='^'||aa[i]=='('||aa[i]==')')
        {
            if(decide(aa[i-1],aa[i],aa[i+1]))
            {
                cout<<"ERROR"<<endl;
                return true;
            }
        }
    }
    int count1 =0;
    for(int i = 0;i<aa.length();i++)
    {
        if(aa[i] == '(')
        count1++;
        else if(aa[i]==')')
        count1--;
    }
    if(count1!=0)
    {
        cout<<"ERROR"<<endl;
        return true;
    }
        return false;
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
        else if(bb[j]<='0'||bb[j]>='9'||bb[j]!='.')
        {
            first = j-1;
            break;
        }
    }
    return temp2;
}

string change_impression(string cc)
{
    Stack<char> *stack1 = new Stack<char>();
    string temp2 = "";
    string temp3 = "";
    for(int i = 0;cc[i]!='\0';i++)
    {
        if(cc[i] == '-'&&cc[i+1] == '-'&&cc[i+2] == '-')
        {
            temp3= temp3+ '+'+'0';
            i = i+1;
        }
        else if(cc[i]==')'&&cc[i+1] == '-'&&isdigit(cc[i+2])) temp3 = temp3+cc[i]+'+'+'0';
        else temp3+=cc[i];
    }
    int count4 = 0;
    for(first = 0;temp3[first]!='\0';first++)
    {
        if(temp3[first] == '(')
            stack1->push(temp3[first]);
        else if(temp3[first] == ')')
        {
            while(stack1->top()!='(')
                temp2 = temp2 +stack1->pop()+" ";
            stack1->pop();
        }
        else if(temp3[first] == '-'&&isdigit(temp3[first+1])&&!isdigit(temp3[first-1]))
            temp2 += get_digit(cc,first) + " ";
        else if(temp3[first] == '+' || temp3[first] == '-' || temp3[first] == '*' || temp3[first] == '/' || temp3[first] == '^')
        {
            if(stack1->isEmpty()) stack1->push(temp3[first]);
            else
            {
                if(get_operator(stack1->top())>=get_operator(temp3[first]))
                {
                    temp2 = temp2+stack1->pop()+" ";
                    stack1->push(temp3[first]);
                }
                else stack1->push(temp3[first]);
            }
        }
        else
            temp2 += get_digit(temp3,first) + " ";
    }
    if(!stack1->isEmpty())
    {
        while(!stack1->isEmpty())
            temp2 = temp2 + stack1->pop()+ " ";
    }
    delete stack1;
    return temp2;
}
double B_round(double ee)
{
    return (double)(lrint(ee*100)/100.0);
}
double evalue(string dd)
{
    Stack<double> *eve = new Stack<double>();
    for(first= 0;first<dd.length();first++)
    {
        if((dd[first] >='0'&&dd[first]<='9') || (dd[first] == '-'&&isdigit(dd[first+1])&&!isdigit(dd[first-1])))
            eve->push(stof(get_digit(dd,first)));
        else if(dd[first]!=' ')
        {
            double en1 = eve->pop();
            double en2  = eve->pop();
            switch(dd[first])
            {
            case '+' : eve->push(B_round(en2+en1));
            break;
            case '-' : eve->push(B_round(en2-en1));
            break;
            case '*' : eve->push(B_round(en2*en1));
            break;
            case '/' : eve->push(B_round(en2/en1));
            break;
            case '^' : eve->push(B_round(pow(en2,en1)));
            break;
            }
        }
    }
    double temp4 = eve->pop();
    delete eve;
    return temp4;
}

int main()
{
    string input = "";
    while(cin>>input)
    {
        first = 0;
        if(err_exp(input))
            continue;
        cout<<fixed<<setprecision(2)<<evalue(change_impression(input))<<endl;
    }
    return 0;
}
