// debug_delete.cc
#include "debug_delete.h"
#include <iostream>
#include <memory>
#include <string>
using namespace std;

int main() {
  unique_ptr<int, DebugDelete> pi(new int(1024), DebugDelete());
  cout << *pi << endl;
  unique_ptr<string, DebugDelete> ps(new string("hello"), DebugDelete());
  cout << *ps << endl;
  return 0;
}
