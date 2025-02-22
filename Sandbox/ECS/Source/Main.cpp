#include <any>
#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>

#include "ComponentDataArray.h"
#include "EntityManager.h"
#include "TypeInfo.h"

#define TEST_COMPONENT_DATA_ARRAY 0
#define TEST_TYPE_ID              0
#define TEST_ENTITY_MANAGER       1

namespace Test {

class Benchmark
{
public:
	Benchmark(const char* title)
	    : m_title(title)
	    , m_start(std::chrono::system_clock::now())
	{
	}

	~Benchmark()
	{
		auto stop = std::chrono::system_clock::now();
		std::cout << "[Benchmark] " << m_title << ": " << static_cast< double >(std::chrono::duration_cast< std::chrono::microseconds >(stop - m_start).count() / 1000.0) << "(ms)" << std::endl;
	}

private:
	const char*                           m_title;
	std::chrono::system_clock::time_point m_start;
};

struct A
{
	char value;
};

struct B
{
	short value;
};

struct C
{
	int value;
};

} // namespace Test

int main(int argc, char** argv)
{
#if TEST_COMPONENT_DATA_ARRAY
	{
		using namespace Test;

		ECS::ComponentDataArray< A > ca;

		ECS::Entity e1 = { 0, 0 };
		ECS::Entity e2 = { 1, 0 };
		ECS::Entity e3 = { 2, 0 };
		assert(ca.Add(e1, A { 0 }));
		assert(ca.Add(e2, A { 1 }));

		assert(ca.Has(e1));
		assert(ca.Get(e1));
		ca.Remove(e1);
		assert(!ca.Has(e1));

		assert(ca.Has(e2));
		assert(ca.Get(e2));
		ca.Remove(e2);
		assert(!ca.Has(e2));

		assert(!ca.Has(e3));
		assert(!ca.Get(e3));

		assert(ca.Empty());
	}
#endif

#if TEST_TYPE_ID
	{
		using namespace Test;
#if ECS_TYPEID_STATIC
		assert(ECS::GetTypeID< GoodA >() == 0);
		assert(ECS::GetTypeID< GoodB >() == 1);
		assert(ECS::GetTypeID< GoodA >() == 0);
#elif ECS_TYPEID_CONSTEXPR
#elif ECS_TYPEID_HASH_FNV
		constexpr auto a = ECS::GetTypeID< A >();
		static_assert(a == ECS::GetTypeID< A >());
		constexpr auto b = ECS::GetTypeID< B >();
		static_assert(b == ECS::GetTypeID< B >());
		static_assert(a != b);
		assert(ECS::GetTypeName< A >() == "struct Test::A");
		assert(ECS::GetTypeName< B >() == "struct Test::B");
#endif
	}
#endif

#if TEST_ENTITY_MANAGER
	{
		using namespace Test;
		ECS::EntityManager manager;

		ECS::Entity e1 = manager.CreateEntity();
		ECS::Entity e2 = manager.CreateEntity();

		assert(manager.AddComponentData(e1, A {}));
		assert(manager.AddComponentData(e1, B {}));
		assert(manager.AddComponentData(e1, C {}));
		assert(manager.GetComponentData< A >(e1));
		assert(manager.GetComponentData< B >(e1));
		assert(manager.GetComponentData< C >(e1));

		manager.DestroyEntity(e1);
		manager.DestroyEntity(e2);

		ECS::Entity e3 = manager.CreateEntity();
		manager.AddComponents< A, B, C >(e3);
		manager.RemoveComponentData< B >(e3);
		manager.DestroyEntity(e3);
	}
#endif

	return 0;
}
