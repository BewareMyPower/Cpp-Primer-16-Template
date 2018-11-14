// sum_promote_test.cc
#include "sum_promote.h"
#include <climits>
#include <iostream>
#include <limits>
using namespace std;

void sum_char_test() {
  char x = CHAR_MAX;
  char y = CHAR_MAX;
  auto z = ::sum(x, y);
  cout << sizeof(z) << " bytes: " << sum(x, y) << endl;
  unsigned char ux = UCHAR_MAX;
  unsigned char uy = UCHAR_MAX;
  auto uz = ::sum(ux, uy);
  cout << sizeof(uz) << " bytes: " << sum(ux, uy) << endl;
}

void sum_short_test() {
  short x = INT16_MAX;
  short y = INT16_MAX;
  auto z = ::sum(x, y);
  cout << sizeof(z) << " bytes: " << sum(x, y) << endl;
  unsigned short ux = UINT16_MAX;
  unsigned short uy = UINT16_MAX;
  auto uz = ::sum(ux, uy);
  cout << sizeof(uz) << " bytes: " << sum(ux, uy) << endl;
}

void sum_int_test() {
  int x = INT_MAX;
  int y = INT_MAX;
  auto z = ::sum(x, y);
  cout << sizeof(z) << " bytes: " << sum(x, y) << endl;
  unsigned int ux = UINT_MAX;
  unsigned int uy = UINT_MAX;
  auto uz = ::sum(ux, uy);
  cout << sizeof(uz) << " bytes: " << sum(ux, uy) << endl;
}

int main() {
  sum_char_test();
  sum_short_test();
  sum_int_test();
  // 编译错误！因为int64_t无法提升！
  //  ::sum(numeric_limits<int64_t>::max(), numeric_limits<int64_t>::max());
}
