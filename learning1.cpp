#include <iostream>
#include <cmath>
#include <chrono>
#include <cstddef>

int main() {

    // auto start std::chrono::steady_clock::now();

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < INT32_MAX; i++) {}

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << duration.count() / 1000.0 << " seconds" << std::endl;



    return 0;
}