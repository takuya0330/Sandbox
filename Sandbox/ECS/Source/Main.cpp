#include "Archetype.h"
#include "Chunk.h"
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

struct Position : ECS::IComponentData
{
	ECS_COMPONENT_DATA(Position);

	float value[3];
};

struct Rotation : ECS::IComponentData
{
	ECS_COMPONENT_DATA(Rotation);

	float value[4];
};

struct Scale : ECS::IComponentData
{
	ECS_COMPONENT_DATA(Scale);

	float value[3];
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

	// アーキタイプ/チャンクテスト
	if constexpr (1)
	{
		std::printf("--- [Test] Archetype/Chunk ---\n");

		ECS::Archetype ar0({
		    ECS::GetComponentType<Position>(),
		    ECS::GetComponentType<Rotation>(),
		    ECS::GetComponentType<Scale>(),
		});

        ECS::Chunk ch0(&ar0);

        if (auto v = ch0.GetData<Position>(0))
        {
			v->value[0] = 1;
			v->value[1] = 1;
			v->value[2] = 1;
        }
		if (auto v = ch0.GetData<Rotation>(0))
		{
			v->value[0] = 2;
			v->value[1] = 2;
			v->value[2] = 2;
			v->value[3] = 2;
		}
		if (auto v = ch0.GetData<Scale>(0))
		{
			v->value[0] = 3;
			v->value[1] = 3;
			v->value[2] = 3;
		}
		if (auto v = ch0.GetData<Position>(1))
		{
			v->value[0] = 4;
			v->value[1] = 4;
			v->value[2] = 4;
		}

        if (auto v = ch0.GetData<Position>(0))
		{
			std::printf("Position(0): %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
		}
		if (auto v = ch0.GetData<Rotation>(0))
		{
			std::printf("Rotation(0): %f, %f, %f, %f\n", v->value[0], v->value[1], v->value[2], v->value[3]);
		}
		if (auto v = ch0.GetData<Scale>(0))
		{
			std::printf("Scale(0): %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
		}
		if (auto v = ch0.GetData<Position>(1))
		{
			std::printf("Position(1): %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
		}
	}

	return 0;
}
