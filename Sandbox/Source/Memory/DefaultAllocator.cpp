#include "DefaultAllocator.h"

#include <new>
#include <cstdio>
#include <cassert>
#include <memory_resource>

DefaultAllocator::DefaultAllocator()
    : m_max_memory_size(0)
    , m_used_memory_size(0)
{
}

DefaultAllocator::~DefaultAllocator()
{
    assert(m_used_memory_size == 0);
}

void* DefaultAllocator::Allocate(size_t size, size_t align)
{
    auto aligned_size = Alignment(size, align);
    assert(m_max_memory_size > m_used_memory_size + aligned_size);
    m_used_memory_size += aligned_size;
    printf("[Memory] DefaultAllocator: Max = %llu, Used = %llu, Allocate = %llu\n",
        m_max_memory_size,
        m_used_memory_size,
        aligned_size);
    return std::pmr::new_delete_resource()->allocate(size, align);
}

void* DefaultAllocator::Reallocate(void* ptr, size_t size, size_t align)
{
    assert(false);
    return nullptr;
}

void DefaultAllocator::Deallocate(void* ptr, size_t size, size_t align)
{
    auto aligned_size = Alignment(size, align);
    m_used_memory_size -= aligned_size;
    printf("[Memory] DefaultAllocator: Max = %llu, Used = %llu, Deallocate = %llu\n",
        m_max_memory_size,
        m_used_memory_size,
        aligned_size);
    std::pmr::new_delete_resource()->deallocate(ptr, size, align);
}

void DefaultAllocator::SetMaxMemorySize(size_t max_memory_size)
{
    m_max_memory_size = max_memory_size;
}

size_t DefaultAllocator::GetMaxMemorySize() const
{
    return m_max_memory_size;
}

size_t DefaultAllocator::GetUsedMemorySize() const
{
    return m_used_memory_size;
}
