// move.cc
#include <iostream>
#include <type_traits>
using namespace std;

struct Object {
  Object() = default;
  Object(const Object&) { cout << "copy ctor" << endl; }
  Object(Object&&) noexcept { cout << "move ctor" << endl; }
  Object& operator=(const Object&) {
    cout << "copy assigned" << endl;
    return *this;
  }
  Object& operator=(Object&&) noexcept {
    cout << "move assigned" << endl;
    return *this;
  }
  void f() {}  // avoid compile warning
};

// 错误的实现，如果T为左值引用，返回的是左值引用而非右值引用
template <typename T>
T&& mymove(T&& t) {
  return static_cast<T&&>(t);
}

int main() {
  Object obj;
  // 传递左值引用
  cout << ">> call mymove(obj)" << endl;
  auto obj1 = mymove(obj);  // 失败
  cout << ">> call std::move(obj)" << endl;
  auto obj2 = std::move(obj);
  // 传递右值引用
  cout << ">> call obj1 = mymove(std::move(obj))" << endl;
  obj1 = mymove(std::move(obj));
  cout << ">> call obj1 = std::move(std::move(obj))" << endl;
  obj2 = std::move(std::move(obj));

  obj1.f();
  obj2.f();
  return 0;
}
