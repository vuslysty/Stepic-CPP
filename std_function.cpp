#include <iostream>
#include <functional>

template<class A, class B, class T>
auto use_func(A a, B b, T f) -> decltype(f(a, b)) {
    f(a, b);
}

int main(int argc, char **argv) {

    std::function<int (int, int)> op = [](int x, int y) -> int { return x / y; };

    int val = 100;

    // auto foo = [](int a, int b) -> int { return a * b; };

    use_func(40, 53, [&val](int a, int b) { val = a * b; });

    std::cout << val << std::endl;
    
}