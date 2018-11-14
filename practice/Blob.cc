// Blob.cc
#include "Blob.h"
#include <iostream>
using namespace std;

int main() {
  Blob<string> articles = {"java", "c++", "go"};
  try {
    for (size_t i = 0; i <= articles.size(); i++)
      cout << i << " => " << articles[i] << endl;
  } catch (std::exception& e) {
    cout << e.what() << endl;
  }

  Blob<int> numbers = {1, 1, 2, 3, 5, 8};
  BlobPtr<int> p{numbers, 0};
  auto q = p;
  ++p;
  try {
    while (true) {
      cout << *p++ - *q++ << endl;
    }
  } catch (std::out_of_range&) {
    // 用异常停止迭代
  }
  int k = 2;
//  p = BlobPtr<int>{numbers, k};  // 大括号初始化无法转换类型
  p = BlobPtr<int>(numbers, k);
  cout << p[numbers.size() - 1 - k] << endl;

  return 0;
}
