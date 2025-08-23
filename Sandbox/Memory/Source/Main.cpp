#include "BlockAllocator.h"
#include "LinearAllocator.h"

#include <bit>
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

class ClassBase
{
public:
	virtual ~ClassBase() = default;

public:
	static void* operator new(size_t size)
	{
		std::cout << "ClassBase::operator new, size = " << size << "\n";

		void* ptr = std::malloc(size);
		if (ptr == nullptr)
			throw std::bad_alloc();

		return ptr;
	}

	static void operator delete(void* ptr) noexcept
	{
		std::cout << "ClassBase::operator delete\n";

		std::free(ptr);
	}

	static void* operator new[](size_t size)
	{
		std::cout << "ClassBase::operator new[], size = " << size << "\n";

		void* ptr = std::malloc(size);
		if (ptr == nullptr)
			throw std::bad_alloc();

		return ptr;
	}

	static void operator delete[](void* ptr) noexcept
	{
		std::cout << "ClassBase::operator delete[]\n";

		std::free(ptr);
	}

public:
	static void* operator new(size_t size, std::align_val_t alignment)
	{
#if defined(_MSC_VER)
		std::cout << "ClassBase::operator new with alignment, size = " << size << ", alignment = " << static_cast<size_t>(alignment) << "\n";
		void* ptr = _aligned_malloc(size, static_cast<size_t>(alignment));
#else
		std::cout << "ClassBase::operator new with alignment, size = " << size << ", alignment = " << static_cast<size_t>(alignment) << "\n";
		void* ptr = std::aligned_alloc(static_cast<size_t>(alignment), size);
#endif
		if (ptr == nullptr)
			throw std::bad_alloc();

		return ptr;
	}

	static void operator delete(void* ptr, std::align_val_t) noexcept
	{
#if defined(_MSC_VER)
		std::cout << "ClassBase::operator delete with alignment\n";
		_aligned_free(ptr);
#else
		std::cout << "ClassBase::operator delete with alignment\n";
		std::free(ptr);
#endif
	}

	static void* operator new[](size_t size, std::align_val_t alignment)
	{
#if defined(_MSC_VER)
		std::cout << "ClassBase::operator new[] with alignment, size = " << size << ", alignment = " << static_cast<size_t>(alignment) << "\n";
		void* ptr = _aligned_malloc(size, static_cast<size_t>(alignment));
#else
		std::cout << "ClassBase::operator new[] with alignment, size = " << size << ", alignment = " << static_cast<size_t>(alignment) << "\n";
		void* ptr = std::aligned_alloc(static_cast<size_t>(alignment), size);
#endif
		if (ptr == nullptr)
			throw std::bad_alloc();

		return ptr;
	}

	static void operator delete[](void* ptr, std::align_val_t) noexcept
	{
#if defined(_MSC_VER)
		std::cout << "ClassBase::operator delete[] with alignment\n";
		_aligned_free(ptr);
#else
		std::cout << "ClassBase::operator delete[] with alignment\n";
		std::free(ptr);
#endif
	}

public:
	int value;
};

static int g_count = 0;

class ClassDerivedA : public ClassBase
{
public:
	ClassDerivedA()
	{
		value = g_count++;
		std::cout << "ClassDerivedA constructor: value = " << value << "\n";
	}
	~ClassDerivedA()
	{
		std::cout << "ClassDerivedA destructor\n";
	}
};

class alignas(64) ClassDerivedB : public ClassBase
{
public:
	ClassDerivedB()
	{
		value = g_count++;
		std::cout << "ClassDerivedB constructor: value = " << value << "\n";
	}
	~ClassDerivedB()
	{
		std::cout << "ClassDerivedB destructor\n";
	}
};

void* operator new(size_t size, std::align_val_t alignment)
{
#if defined(_MSC_VER)
	std::cout << "::operator new with alignment, size = " << size << ", alignment = " << static_cast<size_t>(alignment) << "\n";
	void* ptr = _aligned_malloc(size, static_cast<size_t>(alignment));
#else
	std::cout << "ClassBase::operator new with alignment, size = " << size << ", alignment = " << static_cast<size_t>(alignment) << "\n";
	void* ptr = std::aligned_alloc(static_cast<size_t>(alignment), size);
#endif
	if (ptr == nullptr)
		throw std::bad_alloc();

	return ptr;
}

void operator delete(void* ptr, std::align_val_t) noexcept
{
#if defined(_MSC_VER)
	std::cout << "::operator delete with alignment\n";
	_aligned_free(ptr);
#else
	std::cout << "ClassBase::operator delete with alignment\n";
	std::free(ptr);
#endif
}

class block_memory_resource : public std::pmr::memory_resource
{
public:
	block_memory_resource(size_t block_size, size_t block_count, void* memory = nullptr)
	    : m_memory(memory)
	    , m_head(nullptr)
	    , m_block_size(block_size)
	    , m_block_count(block_count)
	{
		if (memory == nullptr)
			m_memory = ::operator new(block_size * block_count, std::align_val_t(alignof(std::max_align_t)));

		auto base = reinterpret_cast<char*>(m_memory);
		for (size_t i = 0; i < m_block_count; ++i)
		{
			auto node  = reinterpret_cast<Node*>(base + i * m_block_size);
			node->next = m_head;

			m_head = node;
		}
	}

	~block_memory_resource()
	{
		::operator delete(m_memory, std::align_val_t(alignof(std::max_align_t)));
	}

	bool is_range(void* p) const noexcept
	{
		auto ptr  = reinterpret_cast<char*>(p);
		auto base = reinterpret_cast<char*>(m_memory);
		return (ptr >= m_memory) && (ptr < base + m_block_size * m_block_count);
	}

	bool is_small(size_t size) const noexcept
	{
		return size <= m_block_size;
	}

private:
	struct Node
	{
		Node* next;
	};

private:
	void* do_allocate(size_t bytes, size_t alignment) override
	{
		(void)bytes;
		(void)alignment;

		if (!m_head)
			return nullptr;

		auto p = reinterpret_cast<char*>(m_head);

		auto node = m_head;
		m_head    = node->next;

		return node;
	}

	void do_deallocate(void* p, size_t bytes, size_t alignment) override
	{
		(void)bytes;
		(void)alignment;

		auto node  = reinterpret_cast<Node*>(p);
		node->next = m_head;
		m_head     = node;
	}

	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
	{
		return this == &other;
	}

private:
	void*  m_memory;
	Node*  m_head;
	size_t m_block_size;
	size_t m_block_count;
};

class pool_memory_resource : public std::pmr::memory_resource
{
public:
	pool_memory_resource()
	{
		m_blocks[0] = std::make_unique<block_memory_resource>(4, 100);
		m_blocks[1] = std::make_unique<block_memory_resource>(8, 100);
		m_blocks[2] = std::make_unique<block_memory_resource>(16, 100);
		m_blocks[3] = std::make_unique<block_memory_resource>(32, 100);
		m_blocks[4] = std::make_unique<block_memory_resource>(64, 100);
	}

private:
	void* do_allocate(size_t bytes, size_t alignment) override
	{
		for (auto& pool : m_blocks)
		{
			if (pool->is_small(bytes))
				return pool->allocate(bytes, alignment);
		}
		return nullptr;
	}

	void do_deallocate(void* p, size_t bytes, size_t alignment) override
	{
		for (auto& pool : m_blocks)
		{
			if (pool->is_range(p))
				pool->deallocate(p, bytes, alignment);
		}
	}

	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
	{
		return this == &other;
	}

private:
	std::unique_ptr<block_memory_resource> m_blocks[5];
};

int main(int, char**)
{
#if 0
#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	BlockAllocator block;
	if (!block.Initialize(16, sizeof(int), 5))
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

	// block.Deallocate(p[0]);
	block.Deallocate(p[1]);
	block.Deallocate(p[2]);
	// block.Deallocate(p[3]);
	block.Deallocate(p[4]);

	block.Finalize();

	{
		ClassBase* a1 = new ClassDerivedA;
		std::cout << "a1->value = " << a1->value << "\n";
		delete a1;
	}
	{
		ClassDerivedA* a2 = new ClassDerivedA[3];
		std::cout << "a2[0].value = " << a2[0].value << "\n";
		std::cout << "a2[1].value = " << a2[1].value << "\n";
		std::cout << "a2[2].value = " << a2[2].value << "\n";
		delete[] a2;
	}
	{
		std::unique_ptr<ClassBase> a3 = std::make_unique<ClassDerivedA>();
		std::cout << "a3->value = " << a3->value << "\n";
	}
	{
		std::unique_ptr<ClassDerivedA[]> a4 = std::make_unique<ClassDerivedA[]>(3);
		std::cout << "a4[0].value = " << a4[0].value << "\n";
		std::cout << "a4[1].value = " << a4[1].value << "\n";
		std::cout << "a4[2].value = " << a4[2].value << "\n";
	}
	{
		ClassBase* b1 = new ClassDerivedB();
		std::cout << "b1->value = " << b1->value << "\n";
		delete b1;
	}
	{
		ClassDerivedB* b2 = new ClassDerivedB[3];
		std::cout << "b2[0].value = " << b2[0].value << "\n";
		std::cout << "b2[1].value = " << b2[1].value << "\n";
		std::cout << "b2[2].value = " << b2[2].value << "\n";
		delete[] b2;
	}
	{
		std::unique_ptr<ClassBase> b3 = std::make_unique<ClassDerivedB>();
		std::cout << "b3->value = " << b3->value << "\n";
	}
	{
		std::unique_ptr<ClassDerivedB[]> b4 = std::make_unique<ClassDerivedB[]>(3);
		std::cout << "b4[0].value = " << b4[0].value << "\n";
		std::cout << "b4[1].value = " << b4[1].value << "\n";
		std::cout << "b4[2].value = " << b4[2].value << "\n";
	}
    {
		std::shared_ptr<ClassBase> s1 = std::make_shared<ClassDerivedA>();
		std::shared_ptr<ClassBase> s2 = s1;
    }
#endif

	LinearAllocator linear_allocator(16);
	{
		std::cout << "--- LinearAllocator ---\n";

		int* i1 = new (linear_allocator.Allocate(sizeof(int))) int(1);
		int* i2 = new (linear_allocator.Allocate(sizeof(int))) int(2);
		int* i3 = new (linear_allocator.Allocate(sizeof(int))) int(3);
		int* i4 = new (linear_allocator.Allocate(sizeof(int))) int(4);

		std::cout << "i1 = " << *i1 << ", address = " << i1 << "\n";
		std::cout << "i2 = " << *i2 << ", address = " << i2 << "\n";
		std::cout << "i3 = " << *i3 << ", address = " << i3 << "\n";
		std::cout << "i4 = " << *i4 << ", address = " << i4 << "\n";

		linear_allocator.Reset();

		double* d1 = new (linear_allocator.Allocate(sizeof(double))) double(1.1);
		double* d2 = new (linear_allocator.Allocate(sizeof(double))) double(2.2);

		_ASSERT(linear_allocator.Allocate(sizeof(double)) == nullptr);

		std::cout << "d1 = " << *d1 << ", address = " << d1 << "\n";
		std::cout << "d2 = " << *d2 << ", address = " << d2 << "\n";
	}

	pool_memory_resource pool_resource;
	{
		std::cout << "--- pool_memory_resource ---\n";

		int* p1 = static_cast<int*>(pool_resource.allocate(sizeof(int), alignof(int)));
		*p1     = 42;
		int* p2 = static_cast<int*>(pool_resource.allocate(sizeof(int) * 3, alignof(int)));
		p2[0]   = 1;
		p2[1]   = 2;
		p2[2]   = 3;
		std::cout << "p1 = " << *p1 << ", address = " << p1 << "\n";
		std::cout << "p2 = [" << p2[0] << ", " << p2[1] << ", " << p2[2] << "], address = " << p2 << "\n";
		pool_resource.deallocate(p1, sizeof(int), alignof(int));
		pool_resource.deallocate(p2, sizeof(int) * 3, alignof(int));
	}

	return 0;
}
