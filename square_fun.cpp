#include <iostream>
#include <functional>

template<class F>
void for_each_int(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        f(*p);
}

int main() {

    int m[10] = {1,2,3,4,5,6,7,8,9,10};
    int size = sizeof(m) / sizeof(*m);

    auto square_fun = [](int &n) -> void { 
        n *= n;
    };

    
    auto printArray = [&]() -> void { 

        std::cout << m << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << m[i] << " ";
        std::cout << std::endl;
    };

    printArray();

    for_each_int(m, m + 10, square_fun); // теперь m = {1,4,9,16,25,36,49,64,81,100};

    printArray();

    return 0;
}