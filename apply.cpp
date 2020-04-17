#include <utility>
#include <iostream>
#include <functional>

template<class F, typename... Arg>
auto apply(F func, Arg&&... args) -> decltype(func(std::forward<Arg>(args)...)) {
    return func(std::forward<Arg>(args)...);
}

/* not mine, but lolkek, this macros works correctly!!
#define apply(func, ...) func(__VA_ARGS__)
*/

int main() {

    auto fun = [](std::string a, std::string const& b) { return a += b; };

    std::string s("World!");

    // s передаётся по lvalue ссылке,
    // а временный объект по rvalue ссылке 
    // s = apply(fun, "Hello, ", s);
    s = apply(fun, s, " Hello=)");

    std::cout << s << std::endl;
}