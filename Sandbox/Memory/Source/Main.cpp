#include <iostream>
#include <source_location>

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
	    , m_block_size(0)
	    , m_block_alignment(0)
	    , m_block_count(0)
	    , m_meta_size(0)
	{
	}

	bool Initialize(size_t size, size_t alignment, size_t count)
	{
		m_block_size      = size;
		m_block_alignment = alignment;
		m_block_count     = count;

#if defined(_DEBUG)
		m_meta_size = Alignment(sizeof(Metadata), m_block_alignment);
#endif

		size_t aligned_size = Alignment(m_block_size, m_block_alignment) + m_meta_size;
		m_memory            = std::malloc(aligned_size * m_block_count);
		if (!m_memory)
			return false;

		auto base = reinterpret_cast<uint8_t*>(m_memory);
		for (size_t i = 0; i < m_block_count; ++i)
		{
#if defined(_DEBUG)
			auto meta  = reinterpret_cast<Metadata*>(base + i * aligned_size);
			meta->used = false;
			meta->file = "";
			meta->line = -1;
#endif

			auto node  = reinterpret_cast<Node*>(base + i * aligned_size + m_meta_size);
			node->next = m_head;
			m_head     = node;
		}

		return true;
	}

	void Finalize()
	{
		dump();
		std::free(m_memory);
	}

	void* Allocate(
#if defined(_DEBUG)
	    const std::source_location& location = std::source_location::current()
#endif
	)
	{
		if (!m_head)
			return nullptr;

		auto p = reinterpret_cast<uint8_t*>(m_head);

#if defined(_DEBUG)
		auto meta  = reinterpret_cast<Metadata*>(p - m_meta_size);
		meta->used = true;
		meta->file = location.file_name();
		meta->line = location.line();
#endif

		auto node = reinterpret_cast<Node*>(p);
		m_head    = node->next;

		return node;
	}

	void Deallocate(void* ptr)
	{
#if defined(_DEBUG)
		auto meta  = reinterpret_cast<Metadata*>(reinterpret_cast<uint8_t*>(ptr) - m_meta_size);
		meta->used = false;
#endif

		auto node  = reinterpret_cast<Node*>(reinterpret_cast<uint8_t*>(ptr));
		node->next = m_head;
		m_head     = node;
	}

private:
	struct Node
	{
		Node* next;
	};

#if defined(_DEBUG)
	struct Metadata
	{
		bool        used;
		const char* file;
		int         line;
	};
#endif

private:
	void dump()
	{
#if defined(_DEBUG)
        const auto base         = reinterpret_cast<const uint8_t*>(m_memory);
		size_t     aligned_size = Alignment(m_block_size, m_block_alignment) + m_meta_size;
		for (size_t i = 0; i < m_block_count; ++i)
		{
			const auto meta = reinterpret_cast<const Metadata*>(base + i * aligned_size);
			if (meta->used)
			{
				std::cout << "[WARNING] " << meta->file << "(" << meta->line << "): Leaked!" << std::endl; 
			}
		}
#endif
	}

private:
	void*  m_memory;
	Node*  m_head;
	size_t m_block_size;
	size_t m_block_alignment;
	size_t m_block_count;
	size_t m_meta_size;
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

	for (int i = 0; i < 4; ++i)
		block.Deallocate(p[i]);

	block.Finalize();

	return 0;
}
