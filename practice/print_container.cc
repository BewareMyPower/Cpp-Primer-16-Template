// print_container.cc
#include <deque>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename C>
void printContainer1(const C& c) {
  typename C::size_type i = 0;
  while (i < c.size()) {
    cout << c[i] << " ";
    i++;
  }
  cout << endl;
}

template <typename C>
void printContainer2(const C& c) {
  typename C::const_iterator it = c.cbegin();
  while (it != c.cend()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

int main() {
  vector<int> v = {1, 2, 3, 4};
  list<int> l = {5, 6, 7};
  deque<int> dq = {8, 9, 10};

  printContainer1(v);
  printContainer1(dq);

  v.begin();
  printContainer2(v);
  printContainer2(l);
  printContainer2(dq);
  return 0;
}
