// hash_object.cc: 使用模板特化自定义对象的hash函数
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Person {
  string name;
};

namespace std {

bool operator==(const Person& p1, const Person& p2) {
  return p1.name == p2.name;
}

ostream& operator<<(ostream& os, const Person& p) {
  return os << "Person{name = \"" << p.name << "\"}";
}

// 特例化hash<Person>
template <>
struct hash<Person> {
  using result_type = size_t;
  using argument_type = Person;  // 需要实现operator==
  size_t operator()(const Person& p) const { return hash<string>()(p.name); }
};
};

int main() {
  unordered_map<Person, int> age_map;
  age_map[{"xyz"}] = 11;
  age_map[{"abc"}] = 23;
  for (auto const& x : age_map) cout << x.first << " => " << x.second << endl;
  return 0;
}
