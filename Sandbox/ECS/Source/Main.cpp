#include "Archetype.h"
#include "Chunk.h"
#include "ComponentType.h"
#include "EntityManager.h"

#include <cassert>
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
	if constexpr (0)
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
	if constexpr (0)
	{
		std::printf("--- [Test] ComponentType ---\n");

		const auto a = ECS::GetComponentType<A>();
		const auto f = ECS::GetComponentType<F>();

		std::printf("A: id = 0x%08X, size = %llu, alignment = %llu, name = %s\n", a.id, a.size, a.alignment, a.name);
		std::printf("F: id = 0x%08X, size = %llu, alignment = %llu, name = %s\n", f.id, f.size, f.alignment, f.name);
	}

	// アーキタイプ/チャンク/エンティティマネージャーテスト
	if constexpr (1)
	{
		std::printf("--- [Test] Archetype/Chunk/EntityManager ---\n");

		ECS::EntityManager em;
		auto               ar1 = em.GetOrCreateArchetype<Position, Rotation, Scale>();
		auto               ar2 = em.GetOrCreateArchetype<Rotation, Scale, Position>();
		assert(ar1 == ar2);

		ECS::Chunk ch0(ar2);

		auto p = ch0.GetDataArray<Position>();
		auto r = ch0.GetDataArray<Rotation>();
		auto s = ch0.GetDataArray<Scale>();

		for (uint32_t i = 0; i < ar2->GetMaxEntityCount(); ++i)
		{
			p[i].value[0] = static_cast<float>(i + 1);
			p[i].value[1] = static_cast<float>(i + 1);
			p[i].value[2] = static_cast<float>(i + 1);

			r[i].value[0] = static_cast<float>(i + 2);
			r[i].value[1] = static_cast<float>(i + 2);
			r[i].value[2] = static_cast<float>(i + 2);
			r[i].value[3] = static_cast<float>(i + 2);

			s[i].value[0] = static_cast<float>(i + 3);
			s[i].value[1] = static_cast<float>(i + 3);
			s[i].value[2] = static_cast<float>(i + 3);
		}

		for (uint32_t i = 0; i < ar2->GetMaxEntityCount(); ++i)
		{
			if (auto v = ch0.GetData<Position>(i))
			{
				std::printf("Position(%u): %f, %f, %f\n", i, v->value[0], v->value[1], v->value[2]);
			}
			if (auto v = ch0.GetData<Rotation>(i))
			{
				std::printf("Rotation(%u): %f, %f, %f, %f\n", i, v->value[0], v->value[1], v->value[2], v->value[3]);
			}
			if (auto v = ch0.GetData<Scale>(i))
			{
				std::printf("Scale(%u)   : %f, %f, %f\n", i, v->value[0], v->value[1], v->value[2]);
			}
		}
	}

	return 0;
}
