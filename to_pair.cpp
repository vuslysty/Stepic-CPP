#include <tuple>
#include <iostream>

// принимает std::tuple произвольного размера
/* тут должен быть заголовок to_pair */
template<int N, int M, typename T>
auto to_pair(T const &t) -> decltype(std::make_pair(std::get<N>(t), std::get<M>(t)))
{
    return std::make_pair(std::get<N>(t), std::get<M>(t));
}

template<int N, int M, typename... Arg>
auto to_pair2(std::tuple<Arg...> const &t) -> decltype(std::make_pair(std::get<N>(t), std::get<M>(t)))
{
    return std::make_pair(std::get<N>(t), std::get<M>(t));
}

int main() {

    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair2<1,2>(t); 
    std::cout << p.first << " " << p.second << std::endl;
    // p содержит 3.5 и "Hello"

    return 0;
}