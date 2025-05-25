#include "Include/Archetype.h"
#include "Include/ComponentData.h"

#include <cassert>
#include <iostream>

ECS_DECLARE_COMPONENT_DATA(
    Position,
    float value[3];);
ECS_DECLARE_COMPONENT_DATA(
    Rotation,
    float value[4];);
ECS_DECLARE_COMPONENT_DATA(
    Scale,
    float value[3];);

int main(int, char**)
{
	// 型識別子の重複チェック、型名の取得
#if 1
	{
		std::printf("[TEST] TypeId\n");

		constexpr ECS::TypeId pid1 = ECS::TypeIdOf<Position>();
		constexpr ECS::TypeId pid2 = ECS::TypeIdOf<const Position>();
		constexpr ECS::TypeId rid1 = ECS::TypeIdOf<Rotation>();
		constexpr ECS::TypeId sid1 = ECS::TypeIdOf<Scale>();

		std::printf("[TEST] - %s: 0x%08X\n", ECS::TypeNameOf<Position>(), pid1);
		std::printf("[TEST] - %s: 0x%08X\n", ECS::TypeNameOf<Rotation>(), rid1);
		std::printf("[TEST] - %s: 0x%08X\n", ECS::TypeNameOf<Scale>(), sid1);

		assert(pid1 == pid2);
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
		constexpr ECS::ComponentType p2 = ECS::GetComponentType<const Position>();
		constexpr ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		constexpr ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		std::printf("[TEST] - Position: name = %s, id = 0x%08X, size = %llu, alignment = %llu\n", p1.name, p1.id, p1.size, p1.alignment);
		std::printf("[TEST] - Rotation: name = %s, id = 0x%08X, size = %llu, alignment = %llu\n", r1.name, r1.id, r1.size, r1.alignment);
		std::printf("[TEST] - Scale   : name = %s, id = 0x%08X, size = %llu, alignment = %llu\n", s1.name, s1.id, s1.size, s1.alignment);

		assert(p1 == p2);
		assert(p1 != r1);
		assert(p1 != s1);
		assert(r1 != s1);

		std::printf("\n");
	}
#endif

#if 1
	{
		std::printf("[TEST] Archetype\n");

		constexpr ECS::ComponentType p1 = ECS::GetComponentType<Position>();
		constexpr ECS::ComponentType r1 = ECS::GetComponentType<Rotation>();
		constexpr ECS::ComponentType s1 = ECS::GetComponentType<Scale>();

		ECS::Archetype ar({ p1, r1, s1 });

		std::printf("[TEST] - EntityCapacity = %llu\n", ar.GetEntityCapacity());
		std::printf("[TEST] - ChunkSize = %llu\n", ar.GetChunkSize());
		std::printf("[TEST] - %s: ChunkOffset = %llu\n", p1.name, ar.GetChunkOffset(p1.id));
		std::printf("[TEST] - %s: ChunkOffset = %llu\n", r1.name, ar.GetChunkOffset(r1.id));
		std::printf("[TEST] - %s: ChunkOffset = %llu\n", s1.name, ar.GetChunkOffset(s1.id));

		std::printf("\n");
	}
#endif

#if 0
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
