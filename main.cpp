#include <iostream>
#include <string>

class A {
private:
	virtual void hello() {std::cout << "Hello A" << std::endl; }
public:
	
	
protected:
	void call_virt() { hello(); }
};

class B : private A {
private:
	virtual void hello() {std::cout << "Hello B" << std::endl; }
public:
	
protected:

};

class C : public B {
private:

public:

protected:

};

int main()
{
	// A *a = new B();
	// C c;

	// c.
	// a->call_virt();

	return 0;
}