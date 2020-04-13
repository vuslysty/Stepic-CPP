#include "string.hpp"
#include <iostream>
#include <cstring>

String::String(const char *str = "") {
    if (!str)
        str = "";
    
    this->size = strlen(str);
    this->str = new char[size + 1];
    memcpy(this->str, str, this->size + 1);
}

String::String(size_t n, char c) {
    this->size = n;
    this->str = new char[n + 1];
    memset(this->str, c, n);
    this->str[n] = '\0';
}

String::String(const char *str, size_t i, size_t j) {
    this->size = j - i;
    this->str = new char[this->size + 1];
    memcpy(this->str, str + i, this->size);
    this->str[this->size] = '\0';
}

String::~String() {
    delete [] str;
}

String::String(const String &other) {
    str = nullptr;
    *this = other;
}

String &String::operator=(const String &other) {
    if (this != &other)
    {
        if (str)
            delete [] str;
        size = other.size;
        str = new char[size + 1];
        memcpy(str, other.str, size + 1);
    }
    return *this;
}

void String::append(const String &other) {
    char    *new_str;
    size_t  new_size;

    new_size = this->size + other.size;
    new_str = new char[new_size + 1];

    memcpy(new_str, this->str, this->size);
    memcpy(new_str + this->size, other.str, other.size + 1);
    delete [] this->str;
    this->str = new_str;
    this->size = new_size;
}

int main() {
    String s  = "Hello ";
    String s2 = "world!";

    s.append(s2);
    s.append(" Lol");

    std::cout << s << " " << s.size << std::endl;
    std::cout << s[1][10] << std::endl;



    return (0);
}