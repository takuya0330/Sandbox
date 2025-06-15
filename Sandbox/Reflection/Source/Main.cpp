#include "Reflection.h"

#include <iostream>

struct A
{
	int   i;
	float f;
	char  c;

	REFLECTION(
	    A,
	    REFLECT_FIELD(i),
	    REFLECT_FIELD(f),
	    REFLECT_FIELD(c));
};

struct B
{
	double      d;
	std::string s;

	REFLECTION(
	    B,
	    REFLECT_FIELD(d),
	    REFLECT_FIELD(s));
};

struct C
{
	A a { 42, 3.14f, 'x' };
	B b { 0.001, "reflection test" };

	REFLECTION(
	    C,
	    REFLECT_FIELD(a),
	    REFLECT_FIELD(b));
};

struct D
{
	C c0 {};
	C c1 { A { 1, 2.0f, 'a' }, B { 3.14, "hello" } };

    REFLECTION(
	    D,
	    REFLECT_FIELD(c0),
	    REFLECT_FIELD(c1));
};

int main(int, char**)
{
	D d {};

    Reflect(d, [](auto name, auto& field)
        {
		    std::cout << "name: " << name << ", field: " << field << std::endl;
	    });

	return 0;
}
