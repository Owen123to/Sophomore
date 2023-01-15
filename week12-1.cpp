#include<iostream>
using namespace std;
template<class K,class V>
struct Pair {
    Pair() {}
    Pair(K key, V value) 
    {
      first = key;
      second = value;
    }
    Pair(const Pair& other) 
    {
      this->first = other.first;
      this->second = other.second;
    }
    friend ostream& operator<<(ostream& os, const Pair& p) {
      os << p.first << " " << p.second;
      return os;
    }
    K first;
    V second;
};

int main() {
  Pair<string, string> p1("Hello", "World");
  cout << p1 << endl; // excepted output: Hello World
  Pair<string, string> p2(p1);
  cout << p2 << endl; // excepted output: Hello World
  Pair<double, int> p3(123.1, 'A');
  cout << p3 << endl; // excepted output: 123.1 65
  Pair<int, double> p4;
  p4.first = 'z';
  p4.second = 12.3;
  cout << p4 << endl; // excepted output: 122 12.3
}