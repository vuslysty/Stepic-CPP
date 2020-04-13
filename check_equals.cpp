#include <typeinfo>

struct Number;
struct BinaryOperation;

struct Visitor {
	virtual void visitNumber(Number const * number) = 0;
	virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
	virtual ~Visitor() { }
};

struct Expression
{
public:
	virtual double evaluate() const = 0;
	virtual void visit(Visitor * vistitor) const = 0;
	virtual ~Expression() { }
};

struct Number : Expression
{
	Number(double value) : value(value) {};
	~Number() {};

	double evaluate() const { return value; };

	double get_value() const { return value; }

	void visit(Visitor * visitor) const { visitor->visitNumber(this); }

private:
	double value;
};

struct BinaryOperation : Expression
{
	BinaryOperation(Expression const * left, char op, Expression const * right) :
			left(left), right(right), op(op) {};
	~BinaryOperation() {};
	double evaluate() const { return 0; };

	Expression const * get_left() const { return left; }
	Expression const * get_right() const { return right; }
	char get_op() const { return op; }

	void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

private:
	Expression const * left;
	Expression const * right;
	char op;
};

#include <iostream>

/* Этот класс вам нужно реализовать */
struct PrintVisitor : Visitor {
	void visitNumber(Number const * number)
	{
		std::cout << number->get_value();
	}

	void visitBinaryOperation(BinaryOperation const * bop)
	{
		std::cout << "(";
		bop->get_left()->visit(this);
		std::cout << " " << bop->get_op() << " ";
		bop->get_right()->visit(this);
		std::cout << ")";
	}
};

struct PrintOperationType : Visitor {

	void visitNumber(Number const * number) {
		std::cout << "Number Type visitor called" << std::endl;
		PrintVisitor printVisitor;
		number->visit(&printVisitor);
		std::cout << std::endl;
	}

	void visitBinaryOperation(BinaryOperation const * bop) {
		std::cout << "Binary Type visitor called" << std::endl;
		PrintVisitor printVisitor;
		bop->visit(&printVisitor);
		std::cout << std::endl;
	}

};

bool check_equals(Expression const *left, Expression const *right)
{
    return typeid(*left) == typeid(*right);
}

template<class T>
bool isSameObject(T const * p, T const * q)
{
    const void *a = dynamic_cast<const void*>(p);
    const void *b = dynamic_cast<const void*>(q);

    return (a == b);
}

int main() {

    Expression *ex1 = new Number(3);
    Expression *ex2 = new BinaryOperation(new Number(13), '+', new Number(23));
    Expression *ex3 = new Number(41);

    std::cout << isSameObject(ex1, ex1) << std::endl;
}