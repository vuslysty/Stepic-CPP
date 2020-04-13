#include <type_traits>
#include <iostream>

int main() {
    std::string s = "Compiler";

    auto sz = s.size();


    auto c1 = s[0];

    decltype(s[0]) c2 = s[7];

    decltype(s[0] + s[7]) c3 = s[1];
    std::cout << std::__is_integer<decltype((c3))>::__value << "\n";

    decltype((c3)) ref = c3;
    std::cout << c3 << "\n";
    ref = 43;
    std::cout << c3 << "\n";

    decltype(s)   sa = s;

    decltype((s)) sb = s;

    c1 = 'K';
    c2 = '!';

    std::cout << s << std::endl;

    int *lol = new int(10);

    decltype((lol)) kek = lol;
    std::cout << typeid(*lol).name() << "\n";
    std::cout << *lol << std::endl;
    std::cout << *kek << std::endl;

    return 0;
}