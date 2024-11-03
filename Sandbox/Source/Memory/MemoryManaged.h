#pragma once

#include "Allocator.h"

#include <cassert>

template<class T, class Allocator>
class MemoryManaged
{
public:
    virtual ~MemoryManaged() = default;

    // placement operators

    inline static void* operator new(size_t, void* p)
    {
        return p;
    }

    inline static void operator delete(void*, void*)
    {
    }

    inline static void* operator new[](size_t, void* p)
    {
        return p;
    }

    inline static void operator delete[](void*, void*)
    {
    }

    // usual operators

    inline static void* operator new(size_t size)
    {
        assert(size == sizeof(T));
        return AllocatorInstance<Allocator>::Get()->Allocate(size, alignof(T));
    }

    inline static void operator delete(void* p, size_t size)
    {
        AllocatorInstance<Allocator>::Get()->Deallocate(p, size, alignof(T));
    }

    // array operators

    inline static void* operator new[](size_t)
    {
        assert(false);
        return nullptr;
    }

    inline static void operator delete[](void*)
    {
        assert(false);
    }

};
