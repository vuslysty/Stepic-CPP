#include <iostream>

template<typename T, typename U>
bool compare(T const &a, T const &b, U (T::*mptr)() const)
{
    return (a.*mptr)() < (b.*mptr)();
}

int main() {
    std::string s1("Elf");
    std::string s2("Archer");

    // сравнение строк по длине
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

    return 0;
}