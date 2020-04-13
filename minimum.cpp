#include <cstddef>
#include <iostream>

template <typename T>
class Array
{

    T       *_array;
    size_t  _size;

public:
    // Список операций:
    //
    explicit Array(size_t size = 0, const T& value = T()) {
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
        _size = size;
        _array = new T[_size];
        for(size_t i = 0; i < _size; i++) {
            _array[i] = value;
        }
    }
    Array(const Array &src) {
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
        _array = nullptr;
        _size = 0;

        *this = src;
    }
    ~Array() {
    //   деструктор, если он вам необходим.
        delete [] _array;
        _array = nullptr;
    }
    //
    Array& operator=(const Array &src) {
    //   оператор присваивания.
        if (this != &src) {
            delete [] _array;
            _array = nullptr;
            this->_size = src._size;
            this->_array = new T[this->_size];
            for (size_t i = 0; i < this->_size; i++)
                this->_array[i] = src._array[i];
        }
        return *this;
    }
    size_t size() const {
    //   возвращает размер массива (количество
    //                              элементов).
        return _size;
    }
    T& operator[](size_t index) {
        return _array[index];
    }
    const T& operator[](size_t index) const {
        return _array[index];
    }
    //   две версии оператора доступа по индексу.
    void print() {
        for (size_t i = 0; i < _size; i++) {
            std::cout << (*this)[i] << " ";
        }
        std::cout << std::endl;
    }
};

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };

template<class T, class Comp>
T minimum(Array<T> &array, Comp comp_func) {
    T *res = &array[0]; 

    for (int i = 0; i < array.size(); i++) {
        if (comp_func(array[i], *res))
            res = &array[i];
    }
    return *res;
}

int main() {

    Array<int> ints(10);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    ints[3] = 1;
    ints[4] = 4;
    ints[5] = 63;
    ints[6] = 11;
    ints[7] = 3;
    ints[8] = 15;
    ints[9] = 12;

    int min = minimum(ints, less); // в min должно попасть число 2
    int max = minimum(ints, Greater()); // в max должно попасть число 15

    std::cout << min << " " << max << std::endl;


    return 0;
}