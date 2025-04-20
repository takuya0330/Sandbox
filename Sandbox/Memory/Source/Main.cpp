#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

template<typename T>
constexpr T Alignment(T size, T align)
{
	return (size + (align - 1)) & ~(align - 1);
}

class BlockAllocator
{
public:
	BlockAllocator()
	    : m_memory(nullptr)
	    , m_head(nullptr)
	{
	}

	bool Initialize(size_t size, size_t alignment, size_t count)
	{
		size_t aligned_size = Alignment(size, alignment);

		m_memory = std::malloc(aligned_size * count);
		if (!m_memory)
			return false;

		for (size_t i = 0; i < count; ++i)
			Deallocate(static_cast<Node*>(m_memory) + i * aligned_size);

        return true;
	}

	void Finalize()
	{
		std::free(m_memory);
	}

	void* Allocate()
	{
		auto node = m_head;
		m_head    = node->next;
		return node;
	}

	void Deallocate(void* ptr)
	{
		auto node  = static_cast<Node*>(ptr);
		node->next = m_head;
		m_head     = node;
	}

private:
	struct Node
	{
		Node* next;
	};

private:
	void* m_memory;
	Node* m_head;
};

int main(int, char**)
{
#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	BlockAllocator block;
	if (!block.Initialize(sizeof(int), 16, 5))
		return -1;

	int* p[5] = { 0 };

	p[0] = new (block.Allocate()) int(0);
	p[1] = new (block.Allocate()) int(1);
	p[2] = new (block.Allocate()) int(2);

	std::cout << "address = " << p[0] << ", value = " << *p[0] << std::endl;
	std::cout << "address = " << p[1] << ", value = " << *p[1] << std::endl;
	std::cout << "address = " << p[2] << ", value = " << *p[2] << std::endl;

	block.Deallocate(p[1]);
	p[1] = nullptr;

	p[1] = new (block.Allocate()) int(3);
	p[3] = new (block.Allocate()) int(4);
	p[4] = new (block.Allocate()) int(5);

	std::cout << "address = " << p[1] << ", value = " << *p[1] << std::endl;
	std::cout << "address = " << p[3] << ", value = " << *p[3] << std::endl;
	std::cout << "address = " << p[4] << ", value = " << *p[4] << std::endl;

     for (int i = 0; i < 5; ++i)
		block.Deallocate(p[i]);

    block.Finalize();

	return 0;
}
