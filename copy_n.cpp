#include <cstddef>
#include <new>
#include <iostream>

template <typename T, typename U>
void copy_n(T *dest, U *src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        // new (dest + i) T((T)(U(*(src + i))));
        dest[i] = (T)src[i];
    }
}

template <typename T>
void printBuf(T *buf, int size) {

    for (int i = 0; i < size; ++i) {
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // char src[] = "Hello world!";
    // char buf[100] = {0};
    char src[] = "Hello";
    double dest[10];

    int size = sizeof(src) / sizeof(*src);
    // copy_n(buf, src, size);
    copy_n(dest, src, size);

    // std::cout << buf << std::endl;

    printBuf(dest, size);

    return 0;
}