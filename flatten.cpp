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

/* My variant */

// template<typename T>
// void flatten(const Array<T> &array, std::ostream &os) {
//     for (int i = 0; i < array.size(); i++) {
//         os << array[i] << " ";
//     }
// }

// template<typename T>
// void flatten(const Array<Array<T> > &array, std::ostream &os) {
//     for (int i = 0; i < array.size(); i++) {
//         flatten(array[i], os);
//     }
// }

/* More interest variant */

template <typename T>
void flatten(const T& a, std::ostream& out)
{
    out << a << " ";
}

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{
    for (size_t i = 0; i < array.size(); i++)
        flatten(array[i], out);
        out << std::endl;
}

int main() {

    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    // flatten(ints, std::cout); // выводит на экран строку "10 20"

    // Array< Array<int> > array_of_ints(10, ints);
    // flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"

Array<std::string> str(3, "Chebureck");
str[0] = "LoL";
str[1] = "KeK";

Array<Array<std::string> > arr(5, str);

Array<Array<Array<std::string> > > the3d(4, arr);

Array<Array<Array<Array<std::string> > > > the4d(2, the3d);

flatten(the4d, std::cout); // работать должно не только для типа int

    return 0;
}