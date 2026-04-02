#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

void func1() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "func1: " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void func2(int x) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "func2: " << x + i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void func3(int& x) {
    x += 100;
}

int main() {
    int a = 10;

    std::thread t1(func1);
    std::thread t2(func2, 5);
    std::thread t3(func3, std::ref(a));

    t1.join();
    t2.join();
    t3.join();

    std::cout << "a = " << a << "\n";
    return 0;
}