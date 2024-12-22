#include "DirectXMathHelper.h"

int main(int, char**)
{
    using namespace XMH;

    XMFLOAT2 a(0, 0), b(1, 1);
    auto c = a + b;
    auto d = a + 1;
    c += d;

    return 0;
}
