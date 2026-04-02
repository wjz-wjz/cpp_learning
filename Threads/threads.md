# std::thread 的基本用法

## 注意事项
正常情况下简单编译只需要执行
```bash
g++ xxx.cpp -o xxx
```
但是如果使用了std::thread，就需要手动将pthread线程库链接进去（-pthread）：
```bash
g++ threads.cpp -std=c++17 -pthread -o threads
```

## 常见用法
```cpp
//创建线程
std::thread t(work); //其中work是函数
```