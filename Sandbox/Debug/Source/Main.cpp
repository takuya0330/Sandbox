#include "Assert.h"

void hoge(const char* func, const char* file, const int line)
{
	Log::Output(file, "(", line, "): ", func);
}

int main(int, char**)
{
    hoge(__FUNCSIG__, __FILE__, __LINE__);

	Log::Outputf("[Test] OutputA: %d\n", 0);
	Log::Outputf(L"[Test] OutputW: %d\n", 1);
	Log::Output("[Test] ", "Output: ", 2);


    //_ASSERT(0);
	//_ASSERT_MSG(0, "message");
	//_ASSERT_RETURN(0, -1);

    hoge(__FUNCSIG__, __FILE__, __LINE__);

	return 0;
}
