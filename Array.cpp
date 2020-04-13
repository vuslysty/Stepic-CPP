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



int main() {
    Array<int> intArr1(20, 4);
    Array<int> intArr2(intArr1);

    intArr1[2] = 13;
    intArr2[2] = 32;

    intArr1.print();
    intArr2.print();

    intArr2 = intArr2;

    intArr1.print();
    intArr2.print();

    intArr1 = intArr2;

    intArr1.print();
    intArr2.print();
}