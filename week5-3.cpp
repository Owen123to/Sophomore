#include<iostream>
#include<string>
using namespace std;
template<class T>
class Node
{
public:
    Node() : prev(NULL),next(NULL) {}
    Node(T data) : prev(NULL),next(NULL),data(data) {}
    Node(T data, Node<T> *prev, Node<T> *next) : prev(prev),next(next),data(data) {}
    T getData(){return data;}
    void setData(T temp){data = temp;}
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
    void setHead(Node<T> *temp){head = temp;}
    void setTail(Node<T> *temp){tail = temp;}
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
class BigDecimal
{
  public:
  BigDecimal() = default;
  BigDecimal(string data){stoB(data);}
  BigDecimal(BigDecimal *temp)
  {
    symbol = temp->symbol;
    for(Node<string>*curr = temp->integer->getHead();curr!=NULL;curr = curr->getNext()) integer->addToTail(curr->getData());
    for(Node<string>*curr = temp->decimal->getHead();curr!=NULL;curr = curr->getNext()) decimal->addToTail(curr->getData());
  }
  BigDecimal* operator+(BigDecimal *bigDecimal)
  {
    BigDecimal *ans = new BigDecimal();
    string a = this->Btos();
    string b = bigDecimal->Btos();
    if(!symbol&&bigDecimal->symbol) return ans->stoB(ans->rounding((ans->sub(b,a))));//-+
    if(symbol&&!bigDecimal->symbol) return ans->stoB(ans->rounding((ans->sub(a,b))));//+-
    if(!symbol&&!bigDecimal->symbol) ans->symbol = false;
    return ans->stoB(ans->rounding(ans->add(a,b)));
  }
  BigDecimal* operator-(BigDecimal *bigDecimal)
  {
    BigDecimal *ans = new BigDecimal();
    string a = this->Btos();
    string b = bigDecimal->Btos();
    if(!symbol&&bigDecimal->symbol) {ans->symbol = false; return ans->stoB(ans->add(a,b));}//-+
    if(symbol&&!bigDecimal->symbol) return ans->stoB(ans->rounding(ans->add(a,b)));//+-
    if(!symbol&&!bigDecimal->symbol) return ans->stoB(ans->rounding(ans->sub(b,a)));//--
    return ans->stoB(ans->rounding(ans->sub(a,b)));
  }
  BigDecimal* operator*(BigDecimal *bigDecimal)
  {
    BigDecimal *ans = new BigDecimal();
    string a = this->Btos();
    string b = bigDecimal->Btos();
    if(symbol!=bigDecimal->symbol) ans->symbol = false;
    return ans->stoB(ans->rounding(ans->mul(a,b)));
  }
  BigDecimal* operator/(BigDecimal *bigDecimal) 
  {
    BigDecimal *ans = new BigDecimal();
    string a = this->Btos();
    string b = bigDecimal->Btos();
    if(symbol!=bigDecimal->symbol) ans->symbol = false;
    return ans->stoB(ans->rounding(ans->div(a,b)));
  }
  BigDecimal* operator^(BigDecimal *bigDecimal) 
  {
    BigDecimal *ans = new BigDecimal();
    string a = this->Btos();
    string b = bigDecimal->Btos();
    if(!symbol&& stoi(bigDecimal->integer->getTail()->getData()) % 2) ans->symbol = false;
    if(!bigDecimal->symbol) {string one = "1.00"; return ans->stoB(ans->rounding(ans->div(one, ans->power(a, b))));}
    return ans->stoB(ans->rounding(ans->power(a,b)));
  }
  friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal)
  {
    if(bigDecimal->symbol == false) out<<"-";
    out<<bigDecimal->integer<<'.'<<bigDecimal->decimal<<endl;
    return out;
  }
  friend std::istream &operator>>(std::istream &in, BigDecimal *data)
  {
    data->clear_or_delete(1);
    string aa;
    in>>aa;
    data->stoB(aa);
    return in;
  }
  private:
    LinkedList<string> *integer = new LinkedList<string>();
    LinkedList<string> *decimal = new LinkedList<string>();
    bool symbol = true;
    string add(string &a,string &b)
    {
        align(a,b);
        int carry = 0;
        for(int i = a.size()-1,temp = 0;i>=0;--i,carry = temp/10)
        {
            if(a[i] == '.') continue;
            temp = a[i]-'0'+b[i]-'0'+carry;
            a[i] = (char)(temp%10+'0');
        }
        if(carry) a= "1"+a;
        while(a[0] == '0'&&a[1]!='.'&&a.size()>1) a.erase(0,1);
        while(b[0] == '0'&&b[1]!='.'&&b.size()>1) b.erase(0,1);
        return a;
    }
    string sub(string &a,string &b)
    {
        align(a,b);
        if(b>a) {symbol = false;return this->sub(b,a);}
        int borrow = 0;
        for(int i= a.size()-1,temp = 0;i>=0;--i)
        {
            if(a[i] == '.') continue;
            temp = a[i]-b[i]-borrow;
            if(temp<0) {temp+=10;borrow=1;}
            else borrow = 0;
            a[i] = (char)(temp+'0');
        }
        while(a[0] == '0'&&a[1]!='.'&&a.size()>1) a.erase(0,1);
        while(b[0] == '0'&&b[1]!='.'&&b.size()>1) b.erase(0,1);
        return a;
    }
    string mul(string a,string b)
    {
        int a_dot = a.find(".");
        int b_dot = b.find(".");
        int c_dec_size = a.size()-a_dot+b.size()-b_dot-2;
        a.erase(a_dot,1);
        b.erase(b_dot,1);
        string c(a.size()+b.size(),'0');
        for(int i = b.size()-1;i>=0;--i)
        {
            if(b[i] == 0) continue;
            for(int j = a.size()-1,temp = 0,carry = 0;j>=-1;--j,carry = temp/10)
            {
                if(j == -1) {c[i+j+1] = (char)(carry+'0');break;}
                temp = (b[i]-'0')*(a[j]-'0')+(c[i+j+1]-'0')+carry;
                c[i+j+1] = (char)(temp%10+'0');
            }
        }
        c.insert(c.size()-c_dec_size,".");
        while(c[0] == '0'&&c[1]!='.'&&c.size()>1) c.erase(0,1);
        int over_dec = c.size() - c.find(".") -16;
        while(over_dec>0) {c.erase(c.size()-1);--over_dec;}
        return c;
    }
    string div(string a,string b)
    {
        int a_dot = a.find(".");
        int b_dot = b.find(".");
        int dec_gap = a.size()-a_dot-b.size()+b_dot;
        a.erase(a_dot,1);
        b.erase(b_dot,1);
        while(a[0]=='0'&&a.size()) a.erase(0,1);
        while(b[0]=='0'&&b.size()) b.erase(0,1);
        if(!a.size() || !b.size()) return "0.00";
        string ans = "";
        for(int i = 0;i<dec_gap;++i) b+="0";
        for(int i = 0;i>dec_gap;--i) a+="0";
        for(int i = 1;i<=15;++i) a+="0";
        int a_base = a.size();
        int b_base = b.size();
        if(a_base<b_base) return "0.00";
        for(int i = 1;i<=a_base-b_base;++i) b+="0";
        while(b.size()>=b_base)
        {
            int quo = 0;
            while(notSmall(a,b))
            {
                a = sub(a,b);
                quo++;
            }
            ans+=(char)(quo+'0');
            b.erase(b.size()-1);
        }
        while(ans.size()<16) ans.insert(0,"0");
        ans.insert(ans.size()-15,".");
        while(ans[0] == '0'&&ans[1]!='.') ans.erase(0,1);
        int over_dec = ans.size() - ans.find(".") -16;
        while(over_dec>0) {ans.erase(ans.size()-1);--over_dec;}
        return ans;
    }
    string power(string &a,string &b)
    {
        if(a == "1.00")
        return "1.00";
        string ans_int = "1.00";
        string ans_dec = "1.00";
        string one = "1.00";
        string b_int = b.substr(0,b.find(".")) + ".00";
        string b_dec = "0"+b.substr(b.find("."));
        if(b_dec!="0.00") ans_dec = Taylor(a,b_dec);
        while(b_int[0]!='0')
        {
            ans_int = mul(ans_int,a);
            b_int = sub(b_int,one);
        }
        return mul(ans_int,ans_dec);
    }
    string Taylor(string a,string b)
    {
        string temp = "";
        temp = ln(a);
        string x = mul(b,temp);
        string x_base = x;
        string one = "1.00";
        string ans = add(one,x);
        for(int i =2;i<=50;++i)
        {
            x = mul(x,x_base);
            temp = factorial(i);
            temp = div(x,temp);
            ans = add(ans,temp);
        }
        return ans;
    }
    string ln(string &a)
    {
        string ln_simple[17];//++
        ln_simple[0] = "6.907755278982136"; //ln1000
        ln_simple[1] = "4.605170185988091"; //ln100
        ln_simple[2] = "0.693147180559945"; //ln2
        ln_simple[3] = "0.048790164169432"; //ln1.05
        ln_simple[4] = "0.009950330853168"; //ln1.01
        ln_simple[5] = "0.001998002662673"; //ln1.002
        ln_simple[6] = "0.000199980002666"; //ln1.0002
        ln_simple[7] = "0.000019999800002"; //ln1.00002
        ln_simple[8] = "0.000001999998000"; //ln1.0000002
        ln_simple[9] = "0.000000199999979"; //ln1.000000002
        ln_simple[10] = "0.00000001999999"; //ln1.0000000002
        ln_simple[11] = "0.00000000199999"; //ln1.00000000002
        ln_simple[12] = "0.00000000020000"; //ln1.000000000002
        ln_simple[13] = "0.00000000002000"; //ln1.0000000000002
        ln_simple[14] = "0.00000000000199"; //ln1.00000000000002
        ln_simple[15] = "0.00000000000020"; //ln1.000000000000002
        ln_simple[16] = "0.00000000000001"; //ln1.0000000000000002
        string simple[17];// //
        simple[0] = "1000.00"; //ln1000
        simple[1] = "100.00"; //ln100
        simple[2] = "2.00"; //ln2
        simple[3] = "1.05"; //ln1.05
        simple[4] = "1.01"; //ln1.01
        simple[5] = "1.002"; //ln1.002
        simple[6] = "1.0002"; //ln1.0002
        simple[7] = "1.00002"; //ln1.00002
        simple[8] = "1.000002"; //ln1.000002
        simple[9] = "1.0000002"; //ln1.0000002
        simple[10] = "1.00000002"; //ln1.00000002
        simple[11] = "1.000000002"; //ln1.000000002
        simple[12] = "1.0000000002"; //ln1.0000000002
        simple[13] = "1.00000000002"; //ln1.00000000002
        simple[14] = "1.000000000002"; //ln1.000000000002
        simple[15] = "1.0000000000002"; //ln1.0000000000002
        simple[16] = "1.00000000000002"; //ln1.00000000000002
        string result = "0.00";
        string tmp = "";
        for(int i = 0 ; i < 17 ; ++i)
        {
            while(notSmall(a,simple[i]))
            {
                tmp = simple[i];
                a = div(a,tmp);
                tmp = ln_simple[i];
                result = add(result,tmp);
            }
        }
        return result;
    }
    string factorial(int i)
    {
        string ans = to_string(i)+".00";
        string temp = "";
        while(--i)
        {
            temp = to_string(i)+".00";
            ans = mul(ans,temp);
        }
        return ans;
    }
    void align(string &a,string &b)
    {
        int a_dot = a.find(".");
        int b_dot = b.find(".");
        if(a_dot == -1||b_dot == -1)
        {
            int in_gap = a.size() - b.size();
            for(int i = in_gap;i>0;--i) b.insert(0,"0");
            for(int i = in_gap;i<0;++i) a.insert(0,"0");
            return ;
        }
        int i_gap = a_dot-b_dot;
        int d_gap = a.size()-a_dot-b.size()+b_dot;
        for(int i = 0;i<i_gap;++i) b="0"+b;
        for(int i = 0;i>i_gap;--i) a="0"+a;
        for(int i = 0;i<d_gap;++i) b+="0";
        for(int i = 0;i>d_gap;--i) a+="0";
        return;
    }
    bool notSmall(string &a,string &b)
    {
        int a_dot = a.find(".");
        if(a_dot == -1) a_dot = a.size();
        int b_dot = b.find(".");
        if(b_dot == -1) b_dot = b.size();
        if(a_dot>b_dot) return true;
        if(a_dot<b_dot) return false;
        return a>=b;
    }
    string rounding(string x)
    {
        int last_idx = x.size() - 1;
        while(x[last_idx] == '0' && x[last_idx-2] != '.') {x.erase(last_idx); --last_idx;}
        bool carryout = false;
        int dot_idx = x.find(".");
        if(dot_idx+2 == last_idx) return x;
        else if(x[dot_idx+3] < '5') carryout = false;
        else if(x[dot_idx+3] > '5') carryout = true;
        else if(x[dot_idx+3] == '5' && dot_idx+3 != last_idx) carryout = true;
        else if(x[dot_idx+2] % 2) carryout = true;
        else carryout = false;
        if(carryout)
        {
            int carry = 1;
            for(int i=dot_idx+2,tmp = 0;i>=0&&carry;--i,carry=tmp/10)
            {
                if(x[i] == '.') continue;
                tmp = x[i] - '0' + carry;
                x[i] = (char)(tmp % 10 + '0');
            }
            if(carry) x.insert(0,"1");
        }
        while(last_idx != dot_idx+2) {x.erase(last_idx); --last_idx;}
        return x;
    }
    void clear_or_delete(int n)
    {
        symbol = true;
        for(;integer->getHead()!=integer->getTail();integer->setHead(integer->getHead()->getNext())){delete integer->getHead()->getPrev();}
        delete integer->getHead();
        integer->setHead(NULL);
        integer->setTail(NULL);
        for(;decimal->getHead()!=decimal->getTail();decimal->setHead(decimal->getHead()->getNext())){delete decimal->getHead()->getPrev();}
        delete decimal->getHead();
        decimal->setHead(NULL);
        decimal->setTail(NULL);
        if(n==2)
        {
            delete integer;
            delete decimal;
            delete this;
        }
    }
    BigDecimal *stoB(string data)
    {
        bool isdecimal = false;
        int size = data.size();
        for(int i = 0 ; i < size ; ++i)
        {
            string tmp;
            if(data[i] == '-') symbol = false;
            else if(data[i] == '.') isdecimal = true;
            else if(isdecimal) {tmp += data[i]; decimal->addToTail(tmp);}
            else {tmp += data[i]; integer->addToTail(tmp);}
        }
        while(decimal->getSize() < 2) decimal->addToTail("0");
        return this;
    }
    string Btos()
    {
        string tmp;
        for(Node<string> *curr = integer->getHead() ; curr != nullptr ; curr = curr->getNext()) tmp += curr->getData();
        tmp += ".";
        for(Node<string> *curr = decimal->getHead() ; curr != nullptr ; curr = curr->getNext()) tmp += curr->getData();
        return tmp;
    }
};
int main() {
  BigDecimal *bigDecimal1 = new BigDecimal();
  BigDecimal *bigDecimal2 = new BigDecimal();
  char operation;
  while(cin >> bigDecimal1 >> operation >> bigDecimal2)
  {
    switch (operation)
    {
    case '+':
      cout << (*bigDecimal1 + bigDecimal2);
      break;
    case '-':
      cout << (*bigDecimal1 - bigDecimal2);
      break;
    case '*':
      cout << (*bigDecimal1 * bigDecimal2);
      break;
    case '/':
      cout << (*bigDecimal1 / bigDecimal2);
      break;
    case '^':
      cout << (*bigDecimal1 ^ bigDecimal2);
      break;
    default:
      break;
    }
  }
  return 0;
}
