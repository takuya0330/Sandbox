#include <iostream>

#include "ComponentType.h"

struct A : ECS::IComponentData
{
	int value;
};

struct B : ECS::IComponentData
{
};

struct C : ECS::IComponentData
{
};

struct D : ECS::ISharedComponentData
{
};

struct E : ECS::ISharedComponentData
{
};

struct F : ECS::ISharedComponentData
{
	int values[100];
};

int main(int, char**)
{
	// 型識別子の重複チェック
	if constexpr (1)
	{
		std::printf("--- [Test] TypeId ---\n");

		const auto c0   = ECS::GetComponentTypeId< A >();
		const auto c1   = ECS::GetComponentTypeId< B >();
		const auto c2   = ECS::GetComponentTypeId< C >();
		const auto c0_1 = ECS::GetComponentTypeId< A >();

		std::printf("[IComponentData] ComponentTypeId<A>: 0x%08X\n", c0);
		std::printf("[IComponentData] ComponentTypeId<B>: 0x%08X\n", c1);
		std::printf("[IComponentData] ComponentTypeId<C>: 0x%08X\n", c2);
		std::printf("[IComponentData] ComponentTypeId<A>: 0x%08X\n", c0_1);

		const auto c3   = ECS::GetComponentTypeId< D >();
		const auto c4   = ECS::GetComponentTypeId< E >();
		const auto c5   = ECS::GetComponentTypeId< F >();
		const auto c3_1 = ECS::GetComponentTypeId< D >();

		std::printf("[ISharedComponentData] ComponentTypeId<D>: 0x%08X\n", c3);
		std::printf("[ISharedComponentData] ComponentTypeId<E>: 0x%08X\n", c4);
		std::printf("[ISharedComponentData] ComponentTypeId<F>: 0x%08X\n", c5);
		std::printf("[ISharedComponentData] ComponentTypeId<D>: 0x%08X\n", c3_1);
	}

	// コンポーネント型テスト
	if constexpr (1)
	{
		std::printf("--- [Test] ComponentType ---\n");

		const auto a = ECS::GetComponentType< A >();
		const auto f = ECS::GetComponentType< F >();

		std::printf("A: id = 0x%08X, size = %llu, alignment = %llu\n", a.id, a.size, a.alignment);
		std::printf("F: id = 0x%08X, size = %llu, alignment = %llu\n", f.id, f.size, f.alignment);
	}

	return 0;
}
