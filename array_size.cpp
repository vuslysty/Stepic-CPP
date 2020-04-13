#include <cstddef> // size_t
#include <iostream> 

// реализуйте шаблонную функцию array_size,
// которая возвращает значение типа size_t.

// put your code here

template<typename T, size_t N>
size_t array_size(T (&array)[N]) {
    return N;
}

// typedef int * (Class::*Foo)(int, double) const;

class Class {
    public:
    
};

using Foo = int * (Class::*)(int, double) const;

int main() {
    int a[34][53][8];

    std::cout << array_size(a) << std::endl;
    return 0;
}