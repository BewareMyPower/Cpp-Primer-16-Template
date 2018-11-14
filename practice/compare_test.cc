// compare_test.cc
#include "compare.h"
#include <iostream>
using namespace std;

int main() {
  cout << compare(1, 2) << endl;  // -1
  cout << compare(3, 2) << endl;  // 1
  cout << compare(2, 2) << endl;  // 0
  // ambiguous: 因为字符串字面值是指针类型const char*
  // 对应重载1，T可以被推断为char[6]；对应重载2，M和N分别推断为6和6
  //  cout << compare("hello", "world") << endl;
  cout << compare("hello", "world!") << endl;  // -15='h'-'w'
  cout << compare("z", "yz") << endl;  // 1='z'-'y'

  cout << compare<3, 4>("ab", "xyz") << endl;
  return 0;
}
