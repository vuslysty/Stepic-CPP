#include <iostream>
#include <functional>

int mult(int x, int y) { return x * y; }

struct IntDiv {
    int operator()(int x, int y) { return x / y; }
};

int main(int argc, char **argv) {

    std::function<int (int, int)> op;

    char c = argv[2][0];
    if (c == '*')
        op = &mult;
    else
        op = IntDiv();

    std::string str1(argv[1]);
    std::string str2(argv[3]);

    std::cout << op(std::stoi(str1), std::stoi(str2)) << std::endl;
    
    return 0;
}