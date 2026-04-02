#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    auto f1 = []() {
        std::cout << "f1\n";
    };

    auto f2 = [a]() {
        std::cout << "f2 a = " << a << "\n";
    };

    auto f3 = [&a]() {
        a += 5;
        std::cout << "f3 a = " << a << "\n";
    };

    auto f4 = [a, b](int x) {
        return a + b + x;
    };

    f1();
    f2();
    f3();
    std::cout << "outside a = " << a << "\n";
    std::cout << "f4 = " << f4(3) << "\n";

    {
        int c = -5;
        auto f5 = [c](int x){
            std::cout << "f5 = " << c+x+5 << std::endl;
            return x+5;
        };
        f5(5);
    }


    return 0;
}