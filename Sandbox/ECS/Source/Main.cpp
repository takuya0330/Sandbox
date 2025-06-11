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

		std::printf("[TEST] - Position: id = 0x%X, size = %u\n", p1.id, p1.size);
		std::printf("[TEST] - Rotation: id = 0x%X, size = %u\n", r1.id, r1.size);
		std::printf("[TEST] - Scale   : id = 0x%X, size = %u\n", s1.id, s1.size);

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
		if (auto ar = archetype.lock())
		{
			std::printf("[TEST] - entity_capacity = %zu\n", ar->entity_capacity);
			std::printf("[TEST] - chunk_size = %zu\n", ar->chunk_size);
			std::printf("[TEST] - %s: chunk_offset = %zu\n", ECS::ComponentTypeInfo<Position>::GetTypeName(), ar->chunk_offsets.at(p1.id));
			std::printf("[TEST] - %s: chunk_offset = %zu\n", ECS::ComponentTypeInfo<Rotation>::GetTypeName(), ar->chunk_offsets.at(r1.id));
			std::printf("[TEST] - %s: chunk_offset = %zu\n", ECS::ComponentTypeInfo<Scale>::GetTypeName(), ar->chunk_offsets.at(s1.id));
		}
		std::printf("\n");

		std::printf("[TEST] Entity\n");

		ECS::Entity e1 = em.CreateEntity(archetype);
		std::printf("[TEST] - e1: index = %u, version = %u\n", e1.index, e1.version);
		em.DeleteEntity(e1);

		ECS::Entity e2 = em.CreateEntity(archetype);
		std::printf("[TEST] - e2: index = %u, version = %u\n", e2.index, e2.version);
		assert(e2 == ECS::Entity());

		ECS::Entity e3 = em.CreateEntity<Position, Rotation, Scale>();
		std::printf("[TEST] - e3: index = %u, version = %u\n", e3.index, e3.version);

		ECS::Entity e4 = em.CreateEntity<Position, Rotation, Scale>();
		std::printf("[TEST] - e4: index = %u, version = %u\n", e4.index, e4.version);

		em.DeleteEntity(e3);
		em.DeleteEntity(e4);

		std::printf("\n");
	}
#endif

	return 0;
}
