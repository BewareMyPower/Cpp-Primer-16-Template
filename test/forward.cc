// forward.cc
#include <iostream>
using namespace std;

template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
  f(t2, t1);
}

void f(int v1, int& v2) { cout << v1 << " " << ++v2 << endl; }

template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2) {
  f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2) {
  f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void myforward_test();

int main() {
  int i = 0;
  flip1(f, i, 42);
  // 输出0，因为flip1中接受的是右值，将右值传入左值引用
  // ++v2修改的不过右值的引用，即i的拷贝，而并未修改i
  cout << i << endl;

  i = 0;
  flip2(f, i, 42);
  // 输出1，因为int传入T&&，T&&会被推断为int&，T被推断为int&
  // 进而T2 t2即int& t2，传递引用
  cout << i << endl;
  // 问题是如果f是接受右值引用参数的函数则会编译报错
  // i = 0;
  // error: no match for call to ‘(main()::<lambda(int&&, int&)>) (int&, int&)
  // flip2的类型推断后，t1和t2的类型均为int&，函数f则接受右值引用作为参数
  // 而无法直接将左值引用传递给右值引用的参数
  // 注意，这里的问题是，本来42是int&&类型，在传入flip2时却被改变成了int&类型
  // 所以我们传入的lambda表达式本来没错，只是没有保留42的类型
  // flip2([](int&& i, int& j) { cout << i << " " << j << endl; }, i, 42);
  // cout << i << endl;

  // 采用完美转发保留类型
  i = 0;
  flip(f, i, 42);
  cout << i << endl;
  flip([](int&& i, int& j) { cout << i << " " << j << endl; }, i, 42);

  cout << "----myforward_test----" << endl;
  myforward_test();
}

// 标准库forward的实现

// 1. 转发左值
template <typename T>
constexpr T&& myforward(typename std::remove_reference<T>::type& t) noexcept {
  return static_cast<T&&>(t);
}

// 2. 转发右值
template <typename T>
constexpr T&& myforward(typename std::remove_reference<T>::type t) noexcept {
  static_assert(!std::is_lvalue_reference<T>::value,
                "template argument substituting T is an lvalue reference type");
  return static_cast<T&&>(t);
}

void myforward_test() {
  int i = 0;
  using type_i = decltype(std::forward<decltype(i)>(i));
  if (is_rvalue_reference<type_i>::value) cout << "int OK!" << endl;

  int& ri = i;
  using type_ri = decltype(std::forward<decltype(ri)>(ri));
  if (is_lvalue_reference<type_ri>::value) cout << "int& OK!" << endl;

  const int& cri = i;
  using type_cri = decltype(std::forward<decltype(cri)>(cri));
  if (is_lvalue_reference<type_cri>::value &&
      is_const<typename remove_reference<type_cri>::type>::value)
    cout << "const int& OK!" << endl;

  int&& rri = std::move(i);
  using type_rri = decltype(std::forward<decltype(rri)>(rri));
  if (is_rvalue_reference<type_rri>::value &&
      !is_const<typename remove_reference<type_rri>::type>::value)
    cout << "int&& OK!" << endl;
}
