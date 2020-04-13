#include "SharedPtr.hpp"

SharedPtr::SharedPtr(Expression *ptr) : ptr_(ptr)
{
    counter_ = new int;
    *counter_ = (ptr_ == nullptr) ? 0 : 1;
}

SharedPtr::~SharedPtr()
{
    remove_ref();
}

Expression *SharedPtr::get() const
{
    return ptr_;
}

void SharedPtr::reset(Expression *ptr)
{
    if (this->ptr_ != ptr) {
        remove_ref();
        this->ptr_ = ptr;
        this->counter_ = new int(0);
        add_ref();
    }
}

Expression &SharedPtr::operator*() const
{
    return *ptr_;
}

Expression *SharedPtr::operator->() const
{
    // if (ptr_ == nullptr)
    //     throw std::logic_error("asdfasdf");
    return ptr_;
}

SharedPtr::SharedPtr(const SharedPtr &src)
{
    this->ptr_ = src.ptr_;
    this->counter_ = src.counter_;
    add_ref();
}

SharedPtr &SharedPtr::operator=(const SharedPtr &rhs)
{
    if (this != &rhs)
    {
        remove_ref();
        this->ptr_ = rhs.ptr_;
        ++(*rhs.counter_);
        if (this->ptr_)
            this->counter_ = rhs.counter_;
        else
            this->counter_ = new int(0);
    }
    return *this;
}

void SharedPtr::remove_ref() {
    if (*counter_ > 0)
        --(*counter_);
    if (*counter_ == 0) {
        delete ptr_;
        delete counter_;
        ptr_ = nullptr;
        counter_ = nullptr;
    }
}

void SharedPtr::add_ref() {
    if (ptr_ != nullptr)
        ++(*counter_);
}

#define MESG(mesg) std::cout << #mesg << " " << mesg << std::endl

int main() {

    SharedPtr n1(new Number(5));
    SharedPtr n2(new Number(23));

    MESG(*n1.counter_);
    MESG(n1.counter_);
    MESG(*n2.counter_);
    MESG(n2.counter_);

    n1 = n2;
    MESG(*n1.counter_);
    MESG(n1.counter_);
    MESG(*n2.counter_);
    MESG(n2.counter_);

    n1.reset();

    MESG(*n1.counter_);
    MESG(n1.counter_);
    MESG(*n2.counter_);
    MESG(n2.counter_);

    n1.reset();
    
    MESG(*n1.counter_);
    MESG(n1.counter_);
    MESG(*n2.counter_);
    MESG(n2.counter_);

    return 0;
}