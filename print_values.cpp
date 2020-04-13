#include <ostream>
#include <iostream>
#include <typeinfo>

/* My */
/*
void print_values(std::ostream &) 
{}

// принимает произвольное число аргументов
template<typename T, typename... Args>
void print_values(std::ostream & os, const T &value, const Args &... args) 
{
    os << typeid(value).name() << ": " << value << std::endl;
    print_values(os, args...);
}
*/

/* C++17
template <typename... Args>
void print_values(std::ostream & os, const Args&... args)
{
    ((os << typeid(args).name() << ": " << args << "\n"), ...);
}
*/

int main() {

    const std::string str = "Chebur";

    print_values(std::cout, 5, 4.5, "hello", str);

    return 0;
}