#pragma once

#include <source_location>

class BlockAllocator
{
public:
	BlockAllocator();

	bool Initialize(size_t alignment, size_t block_size, size_t block_count);

	void Finalize();

	void* Allocate(
#if defined(_DEBUG)
	    const std::source_location& location = std::source_location::current()
#endif
	);

    template<typename T>
    T* Allocate(
#if defined(_DEBUG)
        const std::source_location& location = std::source_location::current()
#endif
    )
    {
		return reinterpret_cast<T*>(Allocate(location));
    }

	void Deallocate(void* ptr);

private:
	struct Node
	{
		Node* next;
	};

#if defined(_DEBUG)
	struct Metadata
	{
		const char* file;
		int         line;
		bool        used;
	};
#endif

private:
	void dump();

private:
	void*  m_memory;
	Node*  m_head;
	size_t m_alignment;
	size_t m_block_size;
	size_t m_block_count;
	size_t m_meta_size;
};
