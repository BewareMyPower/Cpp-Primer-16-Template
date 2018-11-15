// error_msg.cc
#include <string>
#include "debug_rep.h"
#include "print.h"
using namespace std;

template <typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... args) {
  return print(os, debug_rep(args)...);
}

int main() {
  int i = 1;
  double d = 3.14;
  string s1 = "hello";
  const char* s2 = "world";
  auto p = &d;
  errorMsg(cerr, i, d, s1, s2, p);
}
