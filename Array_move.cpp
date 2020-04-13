#include <cstddef>
#include <iostream>

template <typename T>
class Array
{

    T       *data_;
    size_t  size_;

public:
    // Список операций:
    //
    explicit Array(size_t size = 0, const T& value = T()) {
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
        size_ = size;
        data_ = new T[size_];
        for(size_t i = 0; i < size_; i++) {
            data_[i] = value;
        }
    }
    Array(const Array &src) {
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
        data_ = nullptr;
        size_ = 0;

        *this = src;
    }
    ~Array() {
    //   деструктор, если он вам необходим.
    std::cout << "Destructor" << std::endl;
        delete [] data_;
        data_ = nullptr;
    }
    //
    Array& operator=(const Array &src) {
    //   оператор присваивания.
        if (this != &src) {
            delete [] data_;
            data_ = nullptr;
            this->size_ = src.size_;
            this->data_ = new T[this->size_];
            for (size_t i = 0; i < this->size_; i++)
                this->data_[i] = src.data_[i];
        }
        return *this;
    }
    size_t size() const {
    //   возвращает размер массива (количество
    //                              элементов).
        return size_;
    }
    T& operator[](size_t index) {
        return data_[index];
    }
    const T& operator[](size_t index) const {
        return data_[index];
    }

    void swap(Array &rhs) {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
    }

    // реализуйте перемещающий конструктор
    Array(Array && a) : Array() {
        std::cout << "Move copy" << std::endl;
        swap(a);
    }

    // реализуйте перемещающий оператор присваивания
    Array & operator=(Array && a) {
        std::cout << "Move =" << std::endl;
        swap(a);
        return *this;
    }


    //   две версии оператора доступа по индексу.
    void print() {
        for (size_t i = 0; i < size_; i++) {
            std::cout << (*this)[i] << " ";
        }
        std::cout << std::endl;
    }
};

Array<int> f(Array<int> f) {
    return f;
}

int main() {
    Array<int> intArr1(20, 4);
    Array<int> intArr2;

    intArr2 = f(intArr1);

    intArr2 = f(intArr1);
}