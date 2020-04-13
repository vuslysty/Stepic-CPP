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
struct ValueHolder : ICloneable {

    T data_;

    ValueHolder(T const &p) : data_(p) {}

    virtual ICloneable* clone() const {
        return new ValueHolder<T>(data_);
    }
};

// Это класс, который вам нужно реализовать
class Any
{
    ICloneable *val_;

public:
    // В классе Any должен быть конструктор,
    // который можно вызвать без параметров,
    // чтобы работал следующий код:
    //    Any empty; // empty ничего не хранит
    Any() : val_(nullptr) {}

    // В классе Any должен быть шаблонный
    // конструктор от одного параметра, чтобы
    // можно было создавать объекты типа Any,
    // например, следующим образом:
    //    Any i(10); // i хранит значение 10
    template<typename T>
    Any(const T &src) {
        val_ = new ValueHolder<T>(src);
    }

    // Не забудьте про деструктор. Все выделенные
    // ресурсы нужно освободить.
    ~Any() {
        delete val_;
    }

    // В классе Any также должен быть конструктор
    // копирования (вам поможет метод clone
    // интерфейса ICloneable)
    Any(const Any &src) {
        if (src.val_)
            val_ = src.val_->clone();
        else
            val_ = nullptr;
    }

    // В классе должен быть оператор присваивания и/или
    // шаблонный оператор присваивания, чтобы работал
    // следующий код:
    //    Any copy(i); // copy хранит 10, как и i
    //    empty = copy; // empty хранит 10, как и copy
    //    empty = 0; // а теперь empty хранит 0
    Any &operator=(const Any &rhs) {
        if (this != &rhs) {
            delete val_;

            if (rhs.val_)
                val_ = rhs.val_->clone();
            else
                val_ = nullptr;
        }
        return *this;
    }

    template<typename T>
    Any &operator=(const T &rhs) {
        if (this != &rhs) {
            delete val_;
            val_ = new ValueHolder<T>(rhs);
        }
        return *this;
    }

    // Ну и наконец, мы хотим уметь получать хранимое
    // значение, для этого определите в классе Any
    // шаблонный метод cast, который возвращает
    // указатель на хранимое значение, или нулевой
    // указатель в случае несоответствия типов или
    // если объект Any ничего не хранит:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // потому что i хранит int, а не char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // При реализации используйте оператор dynamic_cast.
    template<typename T>
    T *cast() {
        ValueHolder<T> *val;
        val = dynamic_cast<ValueHolder<T>*>(val_);
        return val ? &(val->data_) : nullptr;
    }

    // Допустим у вас есть два наследника класса Base: Derived1 
    // и Derived2. Кроме того у вас есть указать baseptr
    // типа Base*. Как проверить указывает ли этот указатель на
    // самом деле на объект класса Derived1 или на объект 
    // класса Derived2? Для этого можно воспользоваться dynamic_cast-ом:
    //
    // Derived1 *derived1ptr = dynamic_cast<Derived1*>(baseptr);
    //
    // Если derived1ptr не равен 0, то  baseptr на самом деле
    // указывал на объект класса Derived1, если же derivedptr равен 0,
    // то baseptr на самом деле указывал на объкт какого-то другого 
    // класса (например, Derived2). Это можно проверить так:
    //
    // Derived2 *derived2ptr = dynamic_cast<Derived2*>(baseptr);
    //
    // dynamic_cast работает только, если в классе есть хотя бы
    // один виртуальный метод, и в шаблоне ValueHolder такой
    // как раз имеется.
};

int main() {

    Any empty;

    // std::cout << *d_val << std::endl;
    std::string str = "lololo";

    Any val(str);

    empty = Any(32);
    empty = val;

    std::string *s_val = val.cast<std::string>();
    
    std::cout << *s_val << std::endl;
    // std::cout <<  << std::endl;

    // delete s_val;

    return 0;
}