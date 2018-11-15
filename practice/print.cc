// print.cc
#include "print.h"
#include <string>
using namespace std;

using Couple = std::pair<int, int>;

ostream& operator<<(ostream& os, const Couple& c) {
  os << '(' << c.first << ", " << c.second << ')';
  return os;
}

int main() {
  int i = 0;
  double d = 3.14;
  char ch = 'x';
  string s = "hello";
  Couple couple = make_pair(3, 4);

  print(cout, couple);
  print(cout, i, s);
  print(cout, i, d, ch, s, couple);
  return 0;
}
