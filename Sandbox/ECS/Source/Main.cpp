#include "EntityManager.h"

#include <cassert>
#include <iostream>

struct Position
{
	float value[3];
};
ECS_TYPE_INFO(Position);

struct Rotation
{
	float value[4];
};
ECS_TYPE_INFO(Rotation);

struct Scale
{
	float value[3];
};
ECS_TYPE_INFO(Scale);

int main(int, char**)
{
	// 型識別子の重複チェック、型名の取得
#if 1
	{
		std::printf("[TEST] TypeIndex\n");

		constexpr ECS::TypeIndex pid1 = ECS::TypeInfo<Position>::GetTypeIndex();
		constexpr ECS::TypeIndex rid1 = ECS::TypeInfo<Rotation>::GetTypeIndex();
		constexpr ECS::TypeIndex sid1 = ECS::TypeInfo<Scale>::GetTypeIndex();

		std::printf("[TEST] - %s: 0x%08X\n", ECS::TypeInfo<Position>::GetTypeName(), pid1);
		std::printf("[TEST] - %s: 0x%08X\n", ECS::TypeInfo<Rotation>::GetTypeName(), rid1);
		std::printf("[TEST] - %s: 0x%08X\n", ECS::TypeInfo<Scale>::GetTypeName(), sid1);

		assert(pid1 != rid1);
		assert(pid1 != sid1);
		assert(rid1 != sid1);

		std::printf("\n");
	}
#endif

	// 型情報の取得
#if 1
	{
		std::printf("[TEST] ComponentType\n");

		constexpr ECS::ComponentType p1 = ECS::GetComponentType<Position>();
		constexpr ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		constexpr ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		std::printf("[TEST] - Position: name = %s, id = 0x%08X, size = %llu, alignment = %llu\n", p1.name, p1.index, p1.size, p1.alignment);
		std::printf("[TEST] - Rotation: name = %s, id = 0x%08X, size = %llu, alignment = %llu\n", r1.name, r1.index, r1.size, r1.alignment);
		std::printf("[TEST] - Scale   : name = %s, id = 0x%08X, size = %llu, alignment = %llu\n", s1.name, s1.index, s1.size, s1.alignment);

		assert(p1 != r1);
		assert(p1 != s1);
		assert(r1 != s1);

		std::printf("\n");
	}
#endif

    // アーキタイプ
#if 1
	{
		std::printf("[TEST] Archetype\n");

		constexpr ECS::ComponentType p1 = ECS::GetComponentType<Position>();
		constexpr ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		constexpr ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		ECS::Archetype ar({ p1, r1, s1 });

		std::printf("[TEST] - EntityCapacity = %llu\n", ar.GetEntityCapacity());
		std::printf("[TEST] - ChunkSize = %llu\n", ar.GetChunkSize());
		std::printf("[TEST] - %s: ChunkOffset = %llu\n", p1.name, ar.GetChunkOffset(p1.index));
		std::printf("[TEST] - %s: ChunkOffset = %llu\n", r1.name, ar.GetChunkOffset(r1.index));
		std::printf("[TEST] - %s: ChunkOffset = %llu\n", s1.name, ar.GetChunkOffset(s1.index));

		std::printf("\n");
	}
#endif

    // エンティティ
#if 1
    {
		std::printf("[TEST] Entity\n");

        ECS::EntityManager em;

        ECS::Archetype* ar = em.GetOrCreateArchetype<Position, Rotation, Scale>();
		ECS::Entity     e0 = em.CreateEntity(ar);
		ECS::Entity     e1 = em.CreateEntity(ar);
		ECS::Entity     e2 = em.CreateEntity(ar);

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

        std::printf("[TEST] - GetComponentData\n");

        for (const auto& e : { e0, e1, e2 })
		{
			std::printf("[TEST] -- Entity(%u, %u)\n", e.index, e.version);
			if (auto v = em.GetComponentData<Position>(e))
			{
				std::printf("[TEST] -- Position: %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
			}
			if (auto v = em.GetComponentData<Rotation>(e))
			{
				std::printf("[TEST] -- Rotation: %f, %f, %f, %f\n", v->value[0], v->value[1], v->value[2], v->value[3]);
			}
			if (auto v = em.GetComponentData<Scale>(e))
			{
				std::printf("[TEST] -- Scale   : %f, %f, %f\n", v->value[0], v->value[1], v->value[2]);
			}
		}

		std::printf("[TEST] - GetComponentDataArray\n");

        const auto p = em.GetComponentDataArray<Position>();
		const auto r = em.GetComponentDataArray<Rotation>();
		const auto s = em.GetComponentDataArray<Scale>();

		for (uint32_t i = 0; i < 3; ++i)
		{
			std::printf("[TEST] -- Position(%u): %f, %f, %f\n", i, p[i].value[0], p[i].value[1], p[i].value[2]);
			std::printf("[TEST] -- Rotation(%u): %f, %f, %f, %f\n", i, r[i].value[0], r[i].value[1], r[i].value[2], r[i].value[3]);
			std::printf("[TEST] -- Scale(%u)   : %f, %f, %f\n", i, s[i].value[0], s[i].value[1], s[i].value[2]);
		}

        std::printf("\n");
    }
#endif

	return 0;
}
