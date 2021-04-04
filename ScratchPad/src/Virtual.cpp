#include <iostream>
using namespace std;

class Base
{
public:
	virtual void func1() {
		cout << "Base:func1()" << endl;
	}

	void func2() {
		cout << "Base:func2()" << endl;
	}
};

class Derived : public Base
{
public:
	void func1() {
		cout << "Derived:func1()" << endl;
	}

	void func2() {
		cout << "Derived:func2()" << endl;
	}
};

int mainv()
{
	Base* a = new Base();

	a->func1();
	a->func2();

	a = new Derived();
	a->func1();
	a->func2();

	Derived* b = new Derived();
	Base *c = (Base*)b;
	c->func1();

	return 0;
}