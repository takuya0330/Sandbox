#include <iostream>

#include "ComponentType.h"

int main(int, char**)
{
	// 型識別子の重複チェック
	if constexpr (1)
	{
		auto c0   = ECS::GetComponentTypeId< int8_t >();
		auto c1   = ECS::GetComponentTypeId< int16_t >();
		auto c2   = ECS::GetComponentTypeId< int32_t >();
		auto c0_1 = ECS::GetComponentTypeId< int8_t >();

		std::printf("ComponentTypeId<int8> : 0x%08X\n", c0);
		std::printf("ComponentTypeId<int16>: 0x%08X\n", c1);
		std::printf("ComponentTypeId<int32>: 0x%08X\n", c2);
		std::printf("ComponentTypeId<int8> : 0x%08X\n", c0_1);

		auto sc0   = ECS::GetSharedComponentTypeId< int8_t >();
		auto sc1   = ECS::GetSharedComponentTypeId< int16_t >();
		auto sc2   = ECS::GetSharedComponentTypeId< int32_t >();
		auto sc0_1 = ECS::GetSharedComponentTypeId< int8_t >();

		std::printf("SharedComponentTypeId<int8> : 0x%08X\n", sc0);
		std::printf("SharedComponentTypeId<int16>: 0x%08X\n", sc1);
		std::printf("SharedComponentTypeId<int32>: 0x%08X\n", sc2);
		std::printf("SharedComponentTypeId<int8> : 0x%08X\n", sc0_1);
	}

	return 0;
}
