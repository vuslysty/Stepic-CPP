#include <iostream>

struct Base { virtual ~Base() {}; }; 

struct D1 : public Base { virtual ~D1() {}; };

struct D2 : public Base { virtual ~D2() {}; }; 

struct D3 : public D1, public D2 {};

// base указывает на экземпляр Base, соответствующий D1
// нужно вернуть указатель на экземпляр Base, соответствующий D2
Base const * D1BaseToD2Base( Base const * base )
{
    D1 *d1 = (D1*)base;
    D3 *d3 = (D3*)d1;
    D2 *d2 = (D2*)d3;

    return (const Base*)d2;
}

int main() {

    D3 *d3 = new D3;

    D1 *d1 = d3;
    D2 *d2 = d3;
    // D1 *dtest = d3;

    const Base *b_d1 = d1;
    const Base *b_d2 = d2;

    // std::cout << "Addr dtest   " << dtest << std::endl;
    std::cout << "Addr d3      " << d3 << std::endl;

    std::cout << "Addr d1      " << d1 << std::endl;
    std::cout << "Addr d2      " << d2 << std::endl;

    std::cout << "Addr Base d1 " << b_d1 << std::endl;
    std::cout << "Addr Base d2 " << b_d2 << std::endl;

    std::cout << "Bd1 -> Bd2   " << D1BaseToD2Base(b_d1) << std::endl;
    std::cout << "Bd2 -> Bd1   " << D1BaseToD2Base(b_d2) << std::endl;
    

    return 0;
}