#include <iostream>
#include <functional>



int main(int argc, char **argv) {

    std::function<int (int, int)> op = [](int x, int y) -> int { return x / y; };

    std::cout << op(14, 6) << std::endl;
    
    
}