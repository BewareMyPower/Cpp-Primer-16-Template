// construct_inplace.cc: 使用可变模板参数就地构造对象
#include <iostream>
#include <string>
using namespace std;

constexpr size_t kSize = sizeof(string);
inline void* allocate() { return malloc(kSize); }
inline void deallocate(void* p) { free(p); }

template <typename... Args>
inline void construct(void* p, Args&&... args) {
  new (p) string(std::forward<Args>(args)...);
}

inline void destruct(void* p) { static_cast<string*>(p)->~string(); }

int main() {
  auto p = allocate();
  construct(p, "hello, world, this is c++, welcome to my world!", 34);  // hel

  cout << *static_cast<string*>(p) << endl;

  destruct(p);  // 完成析构
  cout << *static_cast<string*>(p) << endl;  // undefined behaviour
  deallocate(p);
}
