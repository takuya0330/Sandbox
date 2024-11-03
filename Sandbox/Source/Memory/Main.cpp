#include "MemoryManaged.h"
#include "DefaultAllocator.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>

class Test1 : public MemoryManaged<Test1, DefaultAllocator>
{
public:
    Test1(int value)
        : m_value1(value)
    {
        std::cout << "Test1 construct. m_value1 = " << m_value1 << std::endl;
    }

    ~Test1()
    {
        std::cout << "Test1 destruct. m_value1 = " << m_value1 << std::endl;
    }

private:
    int m_value1;
};


int main(int, char**)
{
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    AllocatorInstance<DefaultAllocator>::Get()->SetMaxMemorySize(1024);

    // コンストラクタ、デストラクタが呼び出されない
    // 自前で呼び出す必要がある
    std::cout << "--- malloc/free ---" << std::endl;
    auto t1_m = (Test1*)malloc(sizeof(Test1));
    free(t1_m);

    std::cout << "--- new/delete ---" << std::endl;
    auto t1 = new Test1(10);
    delete t1;

    std::cout << "--- unique_ptr ---" << std::endl;
    {
        std::unique_ptr<Test1> t1_u1(new Test1(20));
        std::unique_ptr<Test1> t1_u2 = std::make_unique<Test1>(30);
    }

    return 0;
}
