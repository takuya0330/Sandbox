#include "TypeInfo/Include/TypeInfo.h"

struct Base
{
	TYPE_INFO_1(Base);
};

struct Derived : public Base
{
	TYPE_INFO_2(Derived, Base);
};

template<typename To, typename From>
To* Cast(From* obj)
{
	if (!obj)
		return nullptr;

	const auto a = To::GetTypeInfo();
	if (a->QueryInterface(From::GetTypeInfo()))
		return static_cast<To*>(obj);

	return nullptr;
}

int main(int, char**)
{
	Base    base;
	Derived derived;

    auto b_to_d = Cast<Derived>(&base);

	return 0;
}
