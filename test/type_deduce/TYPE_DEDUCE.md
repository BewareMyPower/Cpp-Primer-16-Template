## 1. 顶层const会被忽略
```
template <typename T> void f(T t);

int i = 0; const int ci = i;
int* p = nullptr; int* const q = p;
```
`f(i)`和`f(ci)`中`T`均会被推断为`int`。
`f(p)`和`f(q)`中`T`均会被推断为`int*`。

# 2. 类型转换
## 2.1 const转换
非const对象的引用或指针可以传递给const对象的引用或指针形参。
```
template <typename T> void f(const T&);

int i = 0; int& ri = i;
f(ri);  // ok
```
## 2.2 数组或函数指针转换
若函数形参不是引用类型，则数组和函数可以完成相应的指针转换，如下所示。
```
template <typename T>
void f(T t) {
  cout << sizeof(T) << endl;
}

void g() {}

int x[10];
f(x);  // 8，数组x转换成指向x[0]的指针，64位系统上指针8字节
f(g);  // 8，函数g转换成指向g的函数指针
f([](int){});  // 1，lambda表达式实际上是函数对象
```
