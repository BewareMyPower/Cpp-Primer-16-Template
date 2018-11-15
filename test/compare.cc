// compare.cc: 展示函数模板的重载和特化
#include <string.h>
#include <iostream>
#include <type_traits>
using namespace std;

// 模板声明必须在特例化版本之前
template <typename T>
int compare(const T& v1, const T& v2);

// 特例化，将char*当成字符数组比较而非比较指向的char
// 特例化不影响重载的函数匹配，是首先匹配到compare<T>(const T&, const&)，
// 然后再选择特例化版本。
// 如果去掉template<>，该函数就变成了重载，在调用compare("hi", "mom")时，
// 由于数组转指针可以看做直接匹配，所以和compare<N,M>提供同样好的匹配，
// 但由于该重载是非模板函数，所以优先选择该重载。
template <>
int compare(const char* const& p1, const char* const& p2) {
  cout << "compare<char* const>(const T&, const T&)" << endl;
  return strcmp(p1, p2);
}

template <typename T>
int compare(const T& v1, const T& v2) {
  cout << "compare<T>(const T&, const T&)" << endl;
  if (v1 < v2) return -1;
  if (v2 < v1) return 1;
  return 0;
}

template <size_t N, size_t M>
int compare(const char (&s1)[N], const char (&s2)[M]) {
  cout << "compare<N, M>(const char (&s1)[N], const char (&s2)[M])" << endl;
  return strcmp(s1, s2);
}

int main() {
  const char *p1 = "hi", *p2 = "mom";
  cout << compare(p1, p2) << endl;
  cout << compare("hi", "mom") << endl;
  return 0;
}
