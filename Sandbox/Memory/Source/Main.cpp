#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

struct Block
{
	Block* next = nullptr;
};
Block* g_head   = nullptr;
void*  g_memory = nullptr;

void initialize(size_t block_size, size_t block_count)
{
	g_memory = ::operator new(block_size * block_count);
	g_head   = (Block*)g_memory;

    auto heap = g_head;
	for (size_t i = 1; i < block_count; ++i)
	{
		heap->next = (Block*)g_memory + i * block_size;
		heap       = heap->next;
	}
}

void finalize()
{
	::operator delete(g_memory);
}

void* allocate()
{
	auto block = g_head;
	g_head     = block->next;
	return block;
}

void deallocate(void* ptr)
{
	auto block  = (Block*)ptr;
	block->next = g_head;
	g_head      = block;
}

int main(int, char**)
{
#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	initialize(sizeof(int), 5);

	int* p[5];
	for (int i = 0; i < 5; ++i)
	{
		p[i]  = new (allocate()) int;
		*p[i] = i + 1;
	}

    for (int i = 0; i < 5; ++i)
		std::cout << *p[i] << std::endl;

    for (int i = 0; i < 5; ++i)
		deallocate(p[i]);

    finalize();

	return 0;
}
