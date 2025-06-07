#include "EntityManager.h"

#include <cassert>
#include <iostream>

#define CRT_DBG_MAP_ALLOC
#include <crtdbg.h>

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
#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

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

	// エンティティ
#if 1
	{
		ECS::EntityManager em;

		std::printf("[TEST] EntityArchetype\n");

		constexpr ECS::ComponentType p1 = ECS::GetComponentType<Position>();
		constexpr ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		constexpr ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		auto archetype = em.GetOrCreateArchetype({ p1, r1, s1 });
		if (auto ar = archetype.lock())
		{
			std::printf("[TEST] - entity_capacity = %zu\n", ar->entity_capacity);
			std::printf("[TEST] - chunk_size = %zu\n", ar->chunk_size);
			std::printf("[TEST] - %s: chunk_offset = %zu\n", p1.name, ar->chunk_offsets.at(p1.index));
			std::printf("[TEST] - %s: chunk_offset = %zu\n", r1.name, ar->chunk_offsets.at(r1.index));
			std::printf("[TEST] - %s: chunk_offset = %zu\n", s1.name, ar->chunk_offsets.at(s1.index));
		}
		std::printf("\n");

        std::printf("[TEST] Entity\n");

        ECS::Entity e1 = em.CreateEntity(archetype);
		std::printf("[TEST] - e1: index = %u, version = %u\n", ECS::GetEntityIndex(e1), ECS::GetEntityVersion(e1));
		em.DeleteEntity(e1);

        ECS::Entity e2 = em.CreateEntity(archetype);
		std::printf("[TEST] - e2: index = %u, version = %u\n", ECS::GetEntityIndex(e2), ECS::GetEntityVersion(e2));
		assert(e2 == ECS::kInvalidEntity);

        ECS::Entity e3 = em.CreateEntity<Position, Rotation, Scale>();
		std::printf("[TEST] - e3: index = %u, version = %u\n", ECS::GetEntityIndex(e3), ECS::GetEntityVersion(e3));

        ECS::Entity e4 = em.CreateEntity<Position, Rotation, Scale>();
		std::printf("[TEST] - e4: index = %u, version = %u\n", ECS::GetEntityIndex(e4), ECS::GetEntityVersion(e4));

        em.DeleteEntity(e3);
        em.DeleteEntity(e4);

		std::printf("\n");
	}
#endif

	return 0;
}
