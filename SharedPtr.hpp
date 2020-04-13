struct Expression;
struct Number;
struct BinaryOperation;

#include "visitor.cpp"

struct SharedPtr
{
    // реализуйте следующие методы:
    //
    explicit SharedPtr(Expression *ptr = 0);
    ~SharedPtr();
    Expression* get() const;
    void reset(Expression *ptr = 0);
    Expression& operator*() const;
    Expression* operator->() const;

    void mesg(const char *msg) const;

    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr&);

// private:
    void remove_ref();
    void add_ref();

    Expression *ptr_;
    int *counter_;
};