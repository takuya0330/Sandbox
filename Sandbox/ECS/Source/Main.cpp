#include "Archetype.h"
#include "ComponentType.h"

#include <iostream>

struct A : ECS::IComponentData
{
	ECS_COMPONENT_DATA(A);

	int value;
};

struct B : ECS::IComponentData
{
	ECS_COMPONENT_DATA(B);
};

struct C : ECS::IComponentData
{
	ECS_COMPONENT_DATA(C);
};

struct D : ECS::ISharedComponentData
{
	ECS_COMPONENT_DATA(D);
};

struct E : ECS::ISharedComponentData
{
	ECS_COMPONENT_DATA(E);
};

struct F : ECS::ISharedComponentData
{
	ECS_COMPONENT_DATA(F);

	int values[100];
};

int main(int, char**)
{
	// 型識別子の重複チェック
	if constexpr (1)
	{
		std::printf("--- [Test] TypeId ---\n");

		const auto c0   = ECS::GetComponentTypeId<A>();
		const auto c1   = ECS::GetComponentTypeId<B>();
		const auto c2   = ECS::GetComponentTypeId<C>();
		const auto c0_1 = ECS::GetComponentTypeId<A>();

		std::printf("[IComponentData] ComponentTypeId<A>: 0x%08X\n", c0);
		std::printf("[IComponentData] ComponentTypeId<B>: 0x%08X\n", c1);
		std::printf("[IComponentData] ComponentTypeId<C>: 0x%08X\n", c2);
		std::printf("[IComponentData] ComponentTypeId<A>: 0x%08X\n", c0_1);

		const auto c3   = ECS::GetComponentTypeId<D>();
		const auto c4   = ECS::GetComponentTypeId<E>();
		const auto c5   = ECS::GetComponentTypeId<F>();
		const auto c3_1 = ECS::GetComponentTypeId<D>();

		std::printf("[ISharedComponentData] ComponentTypeId<D>: 0x%08X\n", c3);
		std::printf("[ISharedComponentData] ComponentTypeId<E>: 0x%08X\n", c4);
		std::printf("[ISharedComponentData] ComponentTypeId<F>: 0x%08X\n", c5);
		std::printf("[ISharedComponentData] ComponentTypeId<D>: 0x%08X\n", c3_1);
	}

	// コンポーネント型テスト
	if constexpr (1)
	{
		std::printf("--- [Test] ComponentType ---\n");

		const auto a = ECS::GetComponentType<A>();
		const auto f = ECS::GetComponentType<F>();

		std::printf("A: id = 0x%08X, size = %llu, alignment = %llu, name = %s\n", a.id, a.size, a.alignment, a.name);
		std::printf("F: id = 0x%08X, size = %llu, alignment = %llu, name = %s\n", f.id, f.size, f.alignment, f.name);
	}

	// アーキタイプテスト
	if constexpr (1)
	{
		std::printf("--- [Test] Archetype ---\n");

		ECS::Archetype ar0({
		    ECS::GetComponentType<D>(),
		    ECS::GetComponentType<B>(),
		    ECS::GetComponentType<F>(),
		    ECS::GetComponentType<E>(),
		    ECS::GetComponentType<A>(),
		});
	}

	return 0;
}
