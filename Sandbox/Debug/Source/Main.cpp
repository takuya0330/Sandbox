#include "Assert.h"

int main(int, char**)
{
	Log::Outputf("[Test] OutputA: %d\n", 0);
	Log::Outputf(L"[Test] OutputW: %d\n", 1);
	Log::Output("[Test] ", "Output: ", 2);

    //_ASSERT(0);
	//_ASSERT_MSG(0, "message");
	//_ASSERT_RETURN(0, -1);

	return 0;
}
