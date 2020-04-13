#include <iostream>

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder : ICloneable { // дальше самостоятельно

    T data_;

    ValueHolder(T const &p) : data_(p) {}

    virtual ValueHolder* clone() const {
        return new ValueHolder<T>(data_);
    }
};

int main() {

    ValueHolder<int> vHold(58);

    ValueHolder<int> *clone = vHold.clone();



    std::cout << clone->data_ << std::endl;
    vHold.data_ = 43;
    std::cout << clone->data_ << std::endl;
    std::cout << vHold.data_ << std::endl;

    delete clone;
    // int *a = 

    return 0;
}