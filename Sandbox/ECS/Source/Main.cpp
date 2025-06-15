#include "EntityManager.h"

#include <cassert>
#include <iostream>

#define CRT_DBG_MAP_ALLOC
#include <crtdbg.h>

struct Position
{
	float value[3];
};
ECS_COMPONENT_DATA(Position);

struct Rotation
{
	float value[4];
};
ECS_COMPONENT_DATA(Rotation);

struct Scale
{
	float value[3];
};
ECS_COMPONENT_DATA(Scale);

int main(int, char**)
{
#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// 型識別子の重複チェック、型名の取得
#if 1
	{
		std::printf("[TEST] TypeInfo\n");

		ECS::TypeIndex pid1 = ECS::ComponentTypeInfo<Position>::GetTypeIndex();
		ECS::TypeIndex rid1 = ECS::ComponentTypeInfo<Rotation>::GetTypeIndex();
		ECS::TypeIndex sid1 = ECS::ComponentTypeInfo<Scale>::GetTypeIndex();

		std::printf("[TEST] - %s: 0x%X\n", ECS::ComponentTypeInfo<Position>::GetTypeName(), pid1);
		std::printf("[TEST] - %s: 0x%X\n", ECS::ComponentTypeInfo<Rotation>::GetTypeName(), rid1);
		std::printf("[TEST] - %s: 0x%X\n", ECS::ComponentTypeInfo<Scale>::GetTypeName(), sid1);

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

		ECS::ComponentType p1 = ECS::GetComponentType<Position>();
		ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		std::printf("[TEST] - Position: id = 0x%X, size = %u\n", p1.index, p1.size);
		std::printf("[TEST] - Rotation: id = 0x%X, size = %u\n", r1.index, r1.size);
		std::printf("[TEST] - Scale   : id = 0x%X, size = %u\n", s1.index, s1.size);

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

		ECS::ComponentType p1 = ECS::GetComponentType<Position>();
		ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		auto archetype = em.GetOrCreateArchetype({ p1, r1, s1 });
		std::printf("[TEST] - entity_capacity = %zu\n", archetype->entity_capacity);
		std::printf("[TEST] - chunk_size = %zu\n", archetype->chunk_size);
		std::printf("[TEST] - %s: chunk_offset = %zu\n", ECS::ComponentTypeInfo<Position>::GetTypeName(), archetype->chunk_offsets.at(p1.index));
		std::printf("[TEST] - %s: chunk_offset = %zu\n", ECS::ComponentTypeInfo<Rotation>::GetTypeName(), archetype->chunk_offsets.at(r1.index));
		std::printf("[TEST] - %s: chunk_offset = %zu\n", ECS::ComponentTypeInfo<Scale>::GetTypeName(), archetype->chunk_offsets.at(s1.index));
		std::printf("\n");

		std::printf("[TEST] Entity\n");

		ECS::Entity e1 = em.CreateEntity(archetype);
		std::printf("[TEST] - e1: index = %u, version = %u\n", e1.index, e1.version);
		em.DeleteEntity(e1);

		ECS::Entity e2 = em.CreateEntity(archetype);
		std::printf("[TEST] - e2: index = %u, version = %u\n", e2.index, e2.version);

		ECS::Entity e3 = em.CreateEntity<Position, Rotation, Scale>();
		std::printf("[TEST] - e3: index = %u, version = %u\n", e3.index, e3.version);

		em.DeleteEntity(e3);
		em.DeleteEntity(e2);

		std::printf("\n");
	}
#endif

    // コンポーネント
#if 1
    {
		ECS::EntityManager em;

		std::printf("[TEST] ComponentDataGroup\n");

		ECS::Entity e1 = em.CreateEntity<Position, Rotation, Scale>();
		ECS::Entity e2 = em.CreateEntity<Position, Rotation>();
		ECS::Entity e3 = em.CreateEntity<Position, Scale>();
		ECS::Entity e4 = em.CreateEntity<Position>();

		ECS::ComponentDataGroup data;
		data.Include<Position>()
		    .Exclude<Scale>()
		    .Build(em);
    }
#endif

	return 0;
}
