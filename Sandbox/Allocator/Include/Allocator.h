#pragma once

#include <memory>

class LinearAllocator
{
public:
	LinearAllocator(size_t capacity);
	~LinearAllocator();
	void* Allocate(size_t size, size_t alignment);
	void  Deallocate(void* ptr);
	void  Reset();

private:
	std::unique_ptr<uint8_t[]> m_buffer;
	size_t                     m_capacity;
	size_t                     m_offset;
};
