#include <iostream>
#include <string>
using namespace std;

template<class T>
class Node
{
public:
    Node(): prev(nullptr), next(nullptr) {}
    Node(T d): data(d), prev(nullptr), next(nullptr) {}
    Node(T d, Node<T> *p, Node<T> *n): data(d), prev(p), next(n) {}
    T getData() const {return data;}
    Node<T> *getPrev() const {return prev;}
    Node<T> *getNext() const {return next;}
    T &setData(T d) {data = d; return data;}
    Node<T> *setPrev(Node<T> *p) {prev = p; return prev;}
    Node<T> *setNext(Node<T> *n) {next = n; return next;}
private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template<class T>
class LinkedList
{
public:
    LinkedList(): head(nullptr), tail(nullptr) {}
    Node<T> *getHead() {return head;}
    Node<T> *getTail() {return tail;}
    Node<T> *setHead(Node<T> *h) {head = h; return head;}
    Node<T> *setTail(Node<T> *t) {tail = t; return tail;}
    void addToTail(T data)
    {
        if(head == nullptr) head = tail = new Node<T>(data);
        else tail = tail->setNext(new Node<T>(data, tail, nullptr));
    }
    void addToHead(T data)
    {
        if(head == nullptr) head = tail = new Node<T>(data);
        else head = head->setPrev(new Node<T>(data, nullptr, head));
    }
    void addFront(Node<T> *at, T d)
    {
        Node<T> *tmp = new Node<T>(d, at->getPrev(), at);
        if(at->getPrev() != nullptr) at->getPrev()->setNext(tmp);
        at->setPrev(tmp);
        if(head == at) head = tmp;
    }
    void addAfter(Node<T> *at, T d)
    {
        Node<T> *tmp = new Node<T>(d, at, at->getNext());
        if(at->getNext() != nullptr) at->getNext()->setPrev(tmp);
        at->setNext(tmp);
        if(tail == at) tail = tmp;
    }
    void deleteNode(Node<T> *tmp)
    {
       (tmp == head) ? (head = tmp->getNext()) : (tmp->getPrev()->setNext(tmp->getNext()));
       (tmp == tail) ? (tail = tmp->getPrev()) : (tmp->getNext()->setPrev(tmp->getPrev()));
       delete tmp;
    }
    void deleteData(T data)
    {
        for(Node<T> *curr = head ; curr != nullptr ; curr = curr->getNext())
            if(data == curr->getData()) {deleteNode(curr); break;}
    }
    void deleteData(T data, int n)
    {
        for(Node<T> *curr = head, *tmp ; curr != nullptr && n > 0 ; curr = tmp->getNext())//*tmp
        {
            tmp = curr;
            if(data == curr->getData()) deleteNode(curr);
        }
    }
    friend ostream &operator<<(ostream &out, LinkedList<T> * n)
    {
        out << '(';
        for(Node<T> *tmp = n->head ; tmp != n->tail ; tmp = tmp->getNext()) out << tmp->getData()->getData() << ", ";
        out << n->tail->getData()->getData() << ')' << endl;
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
    virtual T getData() const = 0;
    virtual LinkedList<TreeNode<T> *> *getChild() const = 0;
    virtual T &setData(T) = 0;
    virtual LinkedList<TreeNode<T> *> *setChild(LinkedList<TreeNode<T> *> *) = 0;
protected:
    T data;
    LinkedList<TreeNode<T> *> *child;
};

template<class T, class D>
class Tree
{
public:
    virtual TreeNode<T> *insert(D data, D path, D type) = 0;
    virtual TreeNode<T> *search(D data) = 0;
    virtual TreeNode<T> *getRoot() = 0;
    virtual void setRoot(TreeNode<T> *t) = 0;
    virtual void print(TreeNode<T> *) = 0;
protected:
    TreeNode<T> *root;
};

template<class T>
class GeneralTreeNode : public TreeNode<T>
{
public:
    GeneralTreeNode() {this->data = path = type = ""; this->child = new LinkedList<TreeNode<T> *>();}
    GeneralTreeNode(T p, T t) {this->data = ""; path = p; type = t; this->child = new LinkedList<TreeNode<T> *>();}//can use GeneralTreeNode()?
    GeneralTreeNode(T d, T p, T t) {this->data = d; path = p; type = t; this->child = new LinkedList<TreeNode<T> *>();}
    GeneralTreeNode(GeneralTreeNode<T> *g) {this->data = g->getData(); path = g->getPath(); type = g->getType(); this->child = new LinkedList<TreeNode<T> *>();}
    T getPath() const {return path;}
    T getType() const {return type;}
    T getData() const {return this->data;}
    LinkedList<TreeNode<T> *> *getChild() const {return this->child;}
    T &setPath(T p) {path = p; return path;}
    T &setType(T t) {type = t; return type;}
    T &setData(T d) {this->data = d; return this->data;}
    LinkedList<TreeNode<T> *> *setChild(LinkedList<TreeNode<T> *> *c) {this->child = c; return this->child;}
private:
    T path;
    T type;
};

template<class T, class D>
class GeneralTree : public Tree<T, D>
{
public:
    GeneralTree() {this->root = nullptr;}
    TreeNode<T> *getRoot() {return this->root;}
    void setRoot(TreeNode<T> *t) {this->root = t;}
    TreeNode<T> *deserialized(TreeNode<T> *t, string &s, int &idx)
    {
        string tmp;
        int staff = 3;
        idx -= 3;
        while(idx >= 0)
        {
            if(s[idx] == ',') return t;
            if(s[idx] == '\"' || s[idx] == '}')
            {
                if(s[idx] == '\"')
                {
                    idx -= 9;
                    if(idx < 0) break;
                    if(staff == 3) {((GeneralTreeNode<T> *)t)->setType(tmp); tmp = "";}
                    else if(staff == 2) {((GeneralTreeNode<T> *)t)->setPath(tmp); tmp = "";}
                    else if(staff == 1)
                    {
                        ((GeneralTreeNode<T> *)t)->setData(tmp);
                        tmp = "";
                        if(s[idx] == ',') return t;
                    }
                    --staff;
                }
                if(s[idx] == ']' || s[idx] == '}')
                {
                    if(s[idx] == '}') {++idx; t->getChild()->addToHead(deserialized(new GeneralTreeNode<T>(), s, idx));}
                    else if(s[idx-1] != '[') t->getChild()->addToHead(deserialized(new GeneralTreeNode<T>(), s, idx));
                    else --idx;
                    if(s[idx] != ',') idx -= 12;
                }
            }
            else tmp = s[idx] + tmp;
            if(s[idx] == '[')
            {
                return t;
            }
            --idx;
        }
        return t;
    }
    void run(D gcc)
    {
        string tmp1, tmp2;
        if(gcc == "mkdir")
        {
            cin >> tmp1;
            mkdir(tmp1);
        }
        else if(gcc == "touch")
        {
            cin >> tmp1;
            cin.ignore();
            getline(cin, tmp2);
            touch(tmp1, tmp2);
        }
        else if(gcc == "rm")
        {
            cin >> tmp1;
            rm(tmp1);
        }
        else if(gcc == "cp")
        {
            cin >> tmp1;
            cin >> tmp2;
            cp(tmp1, tmp2);
        }
        else if(gcc == "mv")
        {
            cin >> tmp1;
            cin >> tmp2;
            mv(tmp1, tmp2);
        }
    }
    void mkdir(D destination) {insert(destination, "", "dir");}
    void touch(D destination, D data) {insert(destination, data, "file");}
    void rm(D destination)
    {
        TreeNode<T> *tmp = remove(destination);
        if(tmp != nullptr) delete tmp;
    }
    void cp(D source, D destination)
    {
        TreeNode<T> *tmp = search(source);
        TreeNode<T> *tmp2 = search(destination);
        if(tmp != nullptr && tmp2 != nullptr) replace(treeCopy(tmp), tmp2);
    }
    void mv(D source, D destination)
    {
        TreeNode<T> *tmp = remove(source);
        TreeNode<T> *tmp2 = insert(destination, "", "dir");
        if(tmp != nullptr && tmp2 != nullptr) replace(tmp, tmp2);
    }
    void replace(TreeNode<T> *sour, TreeNode<T> *dest)
    {
        Node<TreeNode<T> *> *cur_node = dest->getChild()->getHead();
        if(cur_node == nullptr) {dest->getChild()->addToTail(sour); return;}
        while(cur_node->getNext() != nullptr && ((GeneralTreeNode<T> *)(cur_node->getNext()->getData()))->getPath() <= ((GeneralTreeNode<T> *)sour)->getPath())
            cur_node = cur_node->getNext();
        if(((GeneralTreeNode<T> *)(cur_node->getData()))->getPath() < ((GeneralTreeNode<T> *)sour)->getPath()) dest->getChild()->addAfter(cur_node, sour);
        else if(((GeneralTreeNode<T> *)(cur_node->getData()))->getPath() > ((GeneralTreeNode<T> *)sour)->getPath()) dest->getChild()->addFront(cur_node, sour);
        else
        {
            Node<TreeNode<T> *> *tmp = cur_node;
            cur_node->setData(sour);
            delete tmp;
        }
    }
    TreeNode<T> *insert(D path, D data, D type)
    {
        LinkedList<TreeNode<T> *> *cur_child = this->root->getChild();
        Node<TreeNode<T> *> *cur_node = cur_child->getHead();
        int size = path.size();
        string tmp = "";
        for(int i = 1 ; i <= size ; ++i)
        {
            if(i == size || path[i] == '/')
            {
                if(cur_node == nullptr) {cur_child->addToHead(new GeneralTreeNode<T>(tmp, "dir")); cur_node = cur_child->getHead();}
                else
                {
                    while(cur_node->getNext() != nullptr && ((GeneralTreeNode<T> *)(cur_node->getNext()->getData()))->getPath() <= tmp) cur_node = cur_node->getNext();
                    if(((GeneralTreeNode<T> *)(cur_node->getData()))->getPath() < tmp) {cur_child->addAfter(cur_node, new GeneralTreeNode<T>(tmp, "dir")); cur_node = cur_node->getNext();}
                    else if(((GeneralTreeNode<T> *)(cur_node->getData()))->getPath() > tmp) {cur_child->addFront(cur_node, new GeneralTreeNode<T>(tmp, "dir")); cur_node = cur_node->getPrev();}
                }
                if(i == size)
                {
                    ((GeneralTreeNode<T> *)(cur_node->getData()))->setData(data);
                    ((GeneralTreeNode<T> *)(cur_node->getData()))->setType(type);
                    return cur_node->getData();
                }
                cur_child = cur_node->getData()->getChild();
                cur_node = cur_child->getHead();
                tmp = "";
            }
            else tmp += path[i];
        }
        return nullptr;
    }
    TreeNode<T> *search(D path)
    {
        LinkedList<TreeNode<T> *> *cur_child = this->root->getChild();
        Node<TreeNode<T> *> *cur_node = cur_child->getHead();
        int size = path.size();
        string tmp = "";
        for(int i = 1 ; i <= size ; ++i)
        {
            if(i == size || path[i] == '/')
            {
                if(cur_node == nullptr) return nullptr;
                while(cur_node->getNext() != nullptr && ((GeneralTreeNode<T> *)(cur_node->getNext()->getData()))->getPath() <= tmp) cur_node = cur_node->getNext();
                if(((GeneralTreeNode<T> *)(cur_node->getData()))->getPath() != tmp) return nullptr;
                if(i == size) return cur_node->getData();
                cur_child = cur_node->getData()->getChild();
                cur_node = cur_child->getHead();
                tmp = "";
            }
            else tmp += path[i];
        }
        return nullptr;
    }
    TreeNode<T> *remove(D path)
    {
        LinkedList<TreeNode<T> *> *cur_child = this->root->getChild();
        Node<TreeNode<T> *> *cur_node = cur_child->getHead();
        int size = path.size();
        string tmp = "";
        for(int i = 1 ; i <= size ; ++i)
        {
            if(i == size || path[i] == '/')
            {
                if(cur_node == nullptr) return nullptr;
                while(cur_node->getNext() != nullptr && ((GeneralTreeNode<T> *)(cur_node->getNext()->getData()))->getPath() <= tmp) cur_node = cur_node->getNext();
                if(((GeneralTreeNode<T> *)(cur_node->getData()))->getPath() != tmp) return nullptr;
                if(i == size)
                {
                    TreeNode<T> *tmp2 = cur_node->getData();
                    cur_child->deleteNode(cur_node);
                    return tmp2;
                }
                cur_child = cur_node->getData()->getChild();
                cur_node = cur_child->getHead();
                tmp = "";
            }
            else tmp += path[i];
        }
        return nullptr;
    }
    TreeNode<T> *treeCopy(TreeNode<T> *t)
    {
        if(t == nullptr) return nullptr;
        TreeNode<T> *tmp = new GeneralTreeNode<T>((GeneralTreeNode<T> *)t);
        for(Node<TreeNode<T> *> *cur_node = t->getChild()->getHead() ; cur_node != nullptr ; cur_node = cur_node->getNext())
            tmp->getChild()->addToTail((GeneralTreeNode<T> *)treeCopy(cur_node->getData()));
        return tmp;
    }
    void print(TreeNode<T> *r)
    {
        if(r == this->getRoot()) cout << "{\"root\":";
        bool hasdata = false;
        if(((GeneralTreeNode<T> *)r)->getType() == "file") hasdata = true;
        if(!hasdata)
        {
            cout << "{\"children\":[";
            for(Node<TreeNode<T> *> *cur = r->getChild()->getHead() ; cur != nullptr ; cur = cur->getNext())
            {
                print(cur->getData());
                if(cur->getNext() != nullptr) cout << ",";
            }
            cout << "],";
        }
        else cout << "{\"data\":\"" << r->getData() << "\",";
        cout << "\"path\":\"" << ((GeneralTreeNode<T> *)r)->getPath() << "\",";
        cout << "\"type\":\"" << ((GeneralTreeNode<T> *)r)->getType() << "\"";
        cout << "}";
        if(r == this->getRoot()) cout << "}";
    }
};

int main()
{
    GeneralTree<string, string> t;
    string tree, gcc;
    getline(cin, tree);
    int idx = tree.size() - 1;
    t.setRoot(t.deserialized(new GeneralTreeNode<string>(), tree, idx));
    while(cin >> gcc) t.run(gcc);
    t.print(t.getRoot());
    return 0;
}