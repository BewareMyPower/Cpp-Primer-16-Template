// placementnew.cc: 演示二段式构造
#include <stdlib.h>
#include <iostream>
using namespace std;

struct Object {
  Object(int x_) : x(x_) { cout << "ctor" << endl; }
  ~Object() {
    x = 1;
    cout << "dtor" << endl;
  }
  int x;
};

int main() {
  // 构造step 1: 申请空间
  auto p = static_cast<Object*>(malloc(sizeof(Object)));
  cout << p->x << endl;  // 0，未定义的行为
  // 构造step 2: 构造对象
  new (p) Object(2);  // 调用Object::Object(2)
  cout << p->x << endl;  // 2

  // 析构step 1: 析构对象
  p->~Object();
  cout << p->x << endl;  // 1
  // 析构step 2: 释放空间
  free(p);
  cout << p->x << endl;  // 0，未定义的行为
}
