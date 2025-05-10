#include "Include/ComponentData.h"

#include <cassert>
#include <iostream>

struct Position : ECS::IComponentData
{
	float value[3];
};

struct Rotation : ECS::IComponentData
{
	float value[4];
};

struct Scale : ECS::IComponentData
{
	float value[3];
};

int main(int, char**)
{
	// 型識別子の重複チェック
#if 1
	{
		std::printf("[TEST] TypeId\n");

        const ECS::TypeId pid1 = ECS::GetComponentDataTypeId<Position>();
		const ECS::TypeId pid2 = ECS::GetComponentDataTypeId<const Position>();
		const ECS::TypeId rid1 = ECS::GetComponentDataTypeId<Rotation>();
		const ECS::TypeId sid1 = ECS::GetComponentDataTypeId<Scale>();

		std::printf("[TEST] - Position: 0x%08X\n", pid1);
		std::printf("[TEST] - Rotation: 0x%08X\n", rid1);
		std::printf("[TEST] - Scale   : 0x%08X\n", sid1);

        assert(pid1 == pid2);
        assert(pid1 != rid1);
        assert(pid1 != sid1);
        assert(rid1 != sid1);
	}
#endif

    // 型情報の取得
#if 1
    {
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
