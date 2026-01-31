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

TYPE_INFO_PRIMITIVE(int);

int main(int, char**)
{
	Base    base;
	Derived derived;

    auto b_to_d = Cast<Derived>(&base);

    auto bti = GetTypeInfo<Base>();
	auto dti = GetTypeInfo<Derived>();
	auto iti = GetTypeInfo<int>();
	auto sti = GetTypeInfo<int32_t>();
	// auto fti = GetTypeInfo<float>(); // error

	return 0;
}
