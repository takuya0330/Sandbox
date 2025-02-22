#include "DirectXMathHelper.h"

int main(int, char**)
{
	using namespace XMH;

	constexpr XMFLOAT2 a(0, 0), b(1, 1);
	constexpr auto     c = a + b;
	auto               d = a + 1;
	d += c;

	return 0;
}
