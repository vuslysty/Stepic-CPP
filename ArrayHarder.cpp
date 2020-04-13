#include <cstddef>
#include <iostream>

class Number;
std::ostream &operator<<(std::ostream &o, Number const &num);

template <typename T>
class Array
{

    T       *_array;
    size_t  _size;

public:
    // Список операций:
    //
    explicit Array(size_t size, const T& value = T()) {
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Если у класса нет конструктора
    //   по умолчанию, то второй аргумент этого конструктора
    //   обязателен.
        _size = size;
        _array = reinterpret_cast<T*>(operator new[] (_size * sizeof(T)));
        for(size_t i = 0; i < _size; i++) {
            new (_array + i) T(value);
        }
    }

    Array() : _array(nullptr), _size(0) {}

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
        for(size_t i = 0; i < _size; i++) {
            _array[i].~T();
        }
        operator delete[] (_array);
        _array = nullptr;
    }
    //
    Array& operator=(const Array &src) {
    //   оператор присваивания.
        if (this != &src) {
            this->~Array();

            this->_size = src._size;
            _array = reinterpret_cast<T*>(operator new[] (_size * sizeof(T)));

            for (size_t i = 0; i < this->_size; i++)
                new (_array + i) T(src._array[i]);
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

class Number {
public:
    int _num;

    Number(int n) : _num(n) {}

    Number(Number const &num) {
        this->_num = num._num;
    }
};

std::ostream &operator<<(std::ostream &o, Number const &num) {
    return o << num._num;
}

int main() {
    Array<int> intArr1(20, 4);
    Array<int> intArr2(intArr1);

    Array<Number> numArr1(20, Number(3));
    Array<Number> numArr3(20, Number(5));

    std::cout << numArr1[2] << std::endl;

    numArr1.print();

    numArr3 = numArr1;
    numArr1[5]._num = 10;

    numArr1.print();
    numArr3.print();

    intArr1[2] = 13;
    intArr2[2] = 32;

    intArr1.print();
    intArr2.print();

    // intArr2 = intArr2;

    // intArr1.print();
    // intArr2.print();

    // intArr1 = intArr2;

    // intArr1.print();
    // intArr2.print();
}