#include "Assert.h"

int main(int, char**)
{
	Log::Outputf("[Test] OutputA: %d\n", 0);
	Log::Outputf(L"[Test] OutputW: %d\n", 1);
	Log::Output("[Test] ", "Output: ", 2, "\n");

    Log::Output(__FILE__, "(", __LINE__, "): ERROR: ", "Format Test");
    Log::Output(__FILE__, "(", __LINE__, "): WARNING: ", "Format Test");

    _ASSERT(0);

	return 0;
}
