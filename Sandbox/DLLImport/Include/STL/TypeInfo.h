#pragma once

#include "DLLImport/Include/DLL.h"

namespace STL {

struct TypeInfo
{
	const char* name;
};

} // namespace STL

#define STRING_IMPL(x) #x
#define STRING(x)      STRING_IMPL(x)

#define TYPE_INFO_1(This)                           \
	static const STL::TypeInfo* GetTypeInfo()       \
	{                                               \
		static STL::TypeInfo info { STRING(This) }; \
		return &info;                               \
	}
