#pragma once

#include "Test1.h"

struct DLL_API Test2 : public Test1
{
	TYPE_INFO_2(Test2, Test1);
};
