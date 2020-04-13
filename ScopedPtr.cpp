#include "ScopedPtr.hpp"

ScopedPtr::ScopedPtr(Expression *ptr) : ptr_(ptr)
{}

ScopedPtr::~ScopedPtr()
{
    std::cout << "Destructor called" << std::endl;

    if (ptr_)
        delete ptr_;
}

Expression *ScopedPtr::get() const
{
    return ptr_;
}

Expression *ScopedPtr::release()
{
    Expression *ptr = ptr_;
    ptr_ = nullptr;

    return ptr;
}

void ScopedPtr::reset(Expression *ptr)
{
    if (ptr_)
        delete ptr_;
    ptr_ = ptr;
}

Expression &ScopedPtr::operator*() const
{
    return *ptr_;
}

Expression *ScopedPtr::operator->() const
{
    return ptr_;
}

int main() {

    ScopedPtr ptr(new Number(5));

    std::cout << ptr->evaluate() << std::endl;

    return 0;
}