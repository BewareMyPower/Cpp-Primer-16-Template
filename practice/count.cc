// count.cc
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
size_t count(const std::vector<T>& v, const T& target) {
  cout << "count<T>(const vector<T>&, const T&)" << endl;
  size_t n = 0;
  for (auto const& x : target) {
    if (x == target) ++n;
  }
  return n;
}

template <>
size_t count(const std::vector<const char*>& v, const char* const& target) {
  cout << "count<const char*>(...)" << endl;
  size_t n = 0;
  for (auto const& x : v) {
    if (strcmp(x, target) == 0) ++n;
  }
  return n;
}

int main() {
  vector<int> vi = {1, 4, 3, 2, 5, 6, 2, 5, 6, 2};
  cout << count(vi, 2) << endl;  // 3
  vector<double> vd = {1.0, 1.01, 2.0, 3.0, 2.01, 2.0};
  cout << count(vd, 2.0) << endl;  // 2
  vector<string> vs = {"xyz", "hello", "hello", "hello"};
  cout << count(vs, string("hello")) << endl;  // 3
  vector<const char*> vcs = {"xyz", "hello", "hello", "hello"};
  cout << count(vcs, static_cast<const char*>("hello")) << endl;
}
