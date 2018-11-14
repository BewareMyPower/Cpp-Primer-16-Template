// debug_rep.cc
#include "debug_rep.h"
#include <iostream>
using namespace std;

int main() {
  // 1. string debug_rep<string>(const string&)
  // 需要进行一次从单构造参数到类的转换
  // 2. string debug_rep<const char*>(const char*)
  // 数组转换成指针，可以看成精确匹配
  // 3. string debug_rep(const string&)
  // 需要进行一次从单构造参数到类的转换
  // 根据精确匹配(2)>类型提升>隐式类型转换>类类型转换(1,3)
  // 重载2被认为是最佳匹配。
  // 因此如果要调用重载3，需要定义新的重载debug_rep(const char*)，
  // 并在其中调用重载3，同等匹配程度下，非模板函数>模板函数，
  cout << debug_rep("hello") << endl;
  return 0;
}
