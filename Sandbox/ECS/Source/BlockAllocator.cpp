#include "BlockAllocator.h"

#include <iostream>

namespace {

template<typename T>
constexpr T Alignment(T size, T align)
{
	return (size + (align - 1)) & ~(align - 1);
}

} // namespace

BlockAllocator::BlockAllocator()
    : m_memory(nullptr)
    , m_head(nullptr)
    , m_alignment(0)
    , m_block_size(0)
    , m_block_count(0)
    , m_meta_size(0)
{
}

bool BlockAllocator::Initialize(size_t alignment, size_t block_size, size_t block_count)
{
	m_alignment   = alignment;
	m_block_size  = block_size;
	m_block_count = block_count;

#if defined(_DEBUG)
	m_meta_size = Alignment(sizeof(Metadata), m_alignment);
#endif

	size_t aligned_size = Alignment(m_block_size, m_alignment) + m_meta_size;
	m_memory            = std::malloc(aligned_size * m_block_count);
	if (!m_memory)
		return false;

	auto base = reinterpret_cast<uint8_t*>(m_memory);
	for (size_t i = 0; i < m_block_count; ++i)
	{
#if defined(_DEBUG)
		auto meta  = reinterpret_cast<Metadata*>(base + i * aligned_size);
		meta->file = "";
		meta->line = -1;
		meta->used = false;
#endif

		auto node  = reinterpret_cast<Node*>(base + i * aligned_size + m_meta_size);
		node->next = m_head;
		m_head     = node;
	}

	return true;
}

void BlockAllocator::Finalize()
{
	if (!m_memory)
		return;

	dump();
	std::free(m_memory);
}

void* BlockAllocator::Allocate(
#if defined(_DEBUG)
    const std::source_location& location
#endif
)
{
	if (!m_head)
		return nullptr;

	auto p = reinterpret_cast<uint8_t*>(m_head);

#if defined(_DEBUG)
	auto meta  = reinterpret_cast<Metadata*>(p - m_meta_size);
	meta->file = location.file_name();
	meta->line = location.line();
	meta->used = true;
#endif

	auto node = m_head;
	m_head    = node->next;

	return node;
}

void BlockAllocator::Deallocate(void* ptr)
{
	auto base = reinterpret_cast<uint8_t*>(ptr);

#if defined(_DEBUG)
	auto meta  = reinterpret_cast<Metadata*>(base - m_meta_size);
	meta->used = false;
#endif

	auto node  = reinterpret_cast<Node*>(base);
	node->next = m_head;
	m_head     = node;
}

void BlockAllocator::dump()
{
#if defined(_DEBUG)
	const auto base         = reinterpret_cast<const uint8_t*>(m_memory);
	size_t     aligned_size = Alignment(m_block_size, m_alignment) + m_meta_size;
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
