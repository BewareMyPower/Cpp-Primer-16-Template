// print_args_num.cc
#include <iostream>
#include <string>
using namespace std;

template <typename T, typename... Args>
void foo(const T& t, const Args&... rest) {
  cout << sizeof...(Args) << endl;  // 类型参数数目
  cout << sizeof...(rest) << endl;  // 函数参数数目
}

int main() {
  int i = 0;
  double d = 3.14;
  string s = "how now brown cow";
  foo(i, s, 42, d);
  foo(s, 42, "hi");
  foo(d, s);
  foo("hi");
}
