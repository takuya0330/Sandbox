#pragma once

template<typename T>
constexpr T Alignment(T size, T align)
{
    return (size + (align - 1)) & ~(align - 1);
}

class IAllocator
{
public:
    IAllocator() = default;

    IAllocator(const IAllocator&) = delete;

    IAllocator(IAllocator&&) = delete;

    IAllocator& operator=(const IAllocator&) = delete;

    IAllocator& operator=(IAllocator&&) = delete;

    virtual ~IAllocator() = default;

    virtual void* Allocate(size_t size, size_t align) = 0;

    virtual void* Reallocate(void* ptr, size_t size, size_t align) = 0;

    virtual void Deallocate(void* ptr, size_t size, size_t align) = 0;

    virtual void SetMaxMemorySize(size_t max_memory_size) = 0;

    virtual size_t GetMaxMemorySize() const = 0;

    virtual size_t GetUsedMemorySize() const = 0;
};

template<class Allocator>
class AllocatorInstance
{
public:
    AllocatorInstance() = delete;

    ~AllocatorInstance() = delete;

    AllocatorInstance(const AllocatorInstance&) = delete;

    AllocatorInstance(AllocatorInstance&&) = delete;

    AllocatorInstance& operator=(const AllocatorInstance&) = delete;

    AllocatorInstance& operator=(AllocatorInstance&&) = delete;

    static IAllocator* Get()
    {
        static Allocator allocator;
        return &allocator;
    }
};
