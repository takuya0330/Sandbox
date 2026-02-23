#include "../Include/Allocator.h"

namespace {

template<typename T>
T alignup(T value, size_t alignment)
{
	return (value + alignment - 1) & ~(alignment - 1);
}

} // namespace

LinearAllocator::LinearAllocator(size_t capacity)
    : m_buffer(new uint8_t[capacity])
    , m_capacity(capacity)
    , m_offset(0)
{
}

LinearAllocator::~LinearAllocator()
{
}

void* LinearAllocator::Allocate(size_t size, size_t alignment)
{
	size_t current = reinterpret_cast<size_t>(m_buffer.get() + m_offset);
	size_t aligned = alignup(current, alignment);

    size_t new_offset = aligned - reinterpret_cast<size_t>(m_buffer.get()) + size;

	if (new_offset > m_capacity)
		return nullptr;

	m_offset = new_offset;

	return reinterpret_cast<void*>(aligned);
}

void LinearAllocator::Deallocate(void* ptr)
{
	(void)ptr;
}

void LinearAllocator::Reset()
{
	m_offset = 0;
}
