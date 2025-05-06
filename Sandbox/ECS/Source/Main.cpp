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

		std::printf("[IComponentData] ComponentTypeId<A>: 0x%08X, GetTypeIndex<A>: %u\n", c0, ECS::Internal::GetTypeIndex(c0));
		std::printf("[IComponentData] ComponentTypeId<B>: 0x%08X, GetTypeIndex<B>: %u\n", c1, ECS::Internal::GetTypeIndex(c1));
		std::printf("[IComponentData] ComponentTypeId<C>: 0x%08X, GetTypeIndex<C>: %u\n", c2, ECS::Internal::GetTypeIndex(c2));
		std::printf("[IComponentData] ComponentTypeId<A>: 0x%08X, GetTypeIndex<A>: %u\n", c0_1, ECS::Internal::GetTypeIndex(c0_1));

		const auto c3   = ECS::GetComponentTypeId<D>();
		const auto c4   = ECS::GetComponentTypeId<E>();
		const auto c5   = ECS::GetComponentTypeId<F>();
		const auto c3_1 = ECS::GetComponentTypeId<D>();

		std::printf("[ISharedComponentData] ComponentTypeId<D>: 0x%08X, GetTypeIndex<D>: %u\n", c3, ECS::Internal::GetTypeIndex(c3));
		std::printf("[ISharedComponentData] ComponentTypeId<E>: 0x%08X, GetTypeIndex<E>: %u\n", c4, ECS::Internal::GetTypeIndex(c4));
		std::printf("[ISharedComponentData] ComponentTypeId<F>: 0x%08X, GetTypeIndex<F>: %u\n", c5, ECS::Internal::GetTypeIndex(c5));
		std::printf("[ISharedComponentData] ComponentTypeId<D>: 0x%08X, GetTypeIndex<D>: %u\n", c3_1, ECS::Internal::GetTypeIndex(c3_1));
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

		ECS::Chunk& ch0 = *ar2->GetOrCreateChunk();

		const auto pid = ECS::GetComponentTypeId<Position>();
		const auto rid = ECS::GetComponentTypeId<Rotation>();
		const auto sid = ECS::GetComponentTypeId<Scale>();

		auto p = reinterpret_cast<Position*>(ch0.GetDataArray(pid));
		auto r = reinterpret_cast<Rotation*>(ch0.GetDataArray(rid));
		auto s = reinterpret_cast<Scale*>(ch0.GetDataArray(sid));

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
			if (auto v = reinterpret_cast<Position*>(ch0.GetDataArray(pid)) + i)
			{
				std::printf("Position(%u): %f, %f, %f\n", i, v->value[0], v->value[1], v->value[2]);
			}
			if (auto v = reinterpret_cast<Rotation*>(ch0.GetDataArray(rid)) + i)
			{
				std::printf("Rotation(%u): %f, %f, %f, %f\n", i, v->value[0], v->value[1], v->value[2], v->value[3]);
			}
			if (auto v = reinterpret_cast<Scale*>(ch0.GetDataArray(sid)) + i)
			{
				std::printf("Scale(%u)   : %f, %f, %f\n", i, v->value[0], v->value[1], v->value[2]);
			}
		}
	}

#if 0
	// エンティティテスト
	if constexpr (0)
	{
		std::printf("--- [Test] Entity ---\n");

		ECS::EntityManager em;
		auto               ar1 = em.GetOrCreateArchetype<Position, Rotation, Scale>();
		auto               e0  = em.CreateEntity(ar1);
		auto               e1  = em.CreateEntity(ar1);
		auto               e2  = em.CreateEntity(ar1);

		int i = 0;
		for (const auto& e : { e0, e1, e2 })
		{
			if (auto v = em.GetComponentData<Position>(e))
			{
				v->value[0] = static_cast<float>(i);
				v->value[1] = static_cast<float>(i);
				v->value[2] = static_cast<float>(i);
				++i;
			}
			if (auto v = em.GetComponentData<Rotation>(e))
			{
				v->value[0] = static_cast<float>(i);
				v->value[1] = static_cast<float>(i);
				v->value[2] = static_cast<float>(i);
				v->value[3] = static_cast<float>(i);
				++i;
			}
			if (auto v = em.GetComponentData<Scale>(e))
			{
				v->value[0] = static_cast<float>(i);
				v->value[1] = static_cast<float>(i);
				v->value[2] = static_cast<float>(i);
				++i;
			}
		}
		for (const auto& e : { e0, e1, e2 })
		{
			std::printf("Entity(%u, %u)\n", e.index, e.version);
			if (auto v = em.GetComponentData<Position>(e))
			{
				std::printf("Position: %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
			}
			if (auto v = em.GetComponentData<Rotation>(e))
			{
				std::printf("Rotation: %f, %f, %f, %f\n", v->value[0], v->value[1], v->value[2], v->value[3]);
			}
			if (auto v = em.GetComponentData<Scale>(e))
			{
				std::printf("Scale   : %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
			}
		}

		std::printf("GetComponentDataArray\n");

		const auto p = em.GetComponentDataArray<Position>();
		const auto r = em.GetComponentDataArray<Rotation>();
		const auto s = em.GetComponentDataArray<Scale>();

		for (uint32_t i = 0; i < 3; ++i)
		{
			std::printf("Position(%u): %f, %f, %f\n", i, p[i].value[0], p[i].value[1], p[i].value[2]);
			std::printf("Rotation(%u): %f, %f, %f, %f\n", i, r[i].value[0], r[i].value[1], r[i].value[2], r[i].value[3]);
			std::printf("Scale(%u)   : %f, %f, %f\n", i, s[i].value[0], s[i].value[1], s[i].value[2]);
		}
	}
#endif

	return 0;
}
