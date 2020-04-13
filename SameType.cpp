#include <iostream>

struct Dummy { };
typedef int type;

// Определите шаблон SameType с двумя типовыми
// параметрами. В шаблоне должна быть определена
// одна статическая константа типа bool с именем
// value

template<typename T, typename U>
class SameType { public: static const bool value = false; };

template<typename T> class SameType<T, T> { public: static const bool value = true; };

int main() {
    std::cout << SameType<int, int>::value << std::endl; // выведет 1, т. е. true
std::cout << SameType<int, type>::value << std::endl; // 1, type == int
std::cout << SameType<int, int&>::value << std::endl; // 0, int и ссылка на int - различные типы
std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
std::cout << SameType<int, const int>::value << std::endl; // 0, const - часть типа
}