#pragma once

#include "Allocator.h"

class DefaultAllocator : public IAllocator
{
public:
    DefaultAllocator();

    ~DefaultAllocator();

    void* Allocate(size_t size, size_t align) override;

    void* Reallocate(void* ptr, size_t size, size_t align) override;

    void Deallocate(void* ptr, size_t size, size_t align) override;

    void SetMaxMemorySize(size_t max_memory_size) override;

    size_t GetMaxMemorySize() const override;

    size_t GetUsedMemorySize() const override;

private:
    size_t m_max_memory_size;
    size_t m_used_memory_size;
};
