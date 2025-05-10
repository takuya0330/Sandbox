#pragma once

#include "TypeId.h"

namespace ECS {
namespace Internal {

enum class TypeIdMetadata
{
	kComponentData       = 0x01,
	kSharedComponentData = 0x02,
	kSystem              = 0x04,
};

template<TypeIdMetadata Meta>
TypeId MakeTypeId() noexcept;

uint32_t GetTypeIndex(TypeId id) noexcept;

template<typename T, TypeIdMetadata Meta>
struct TypeIdResolver
{
	inline static const TypeId id = MakeTypeId<Meta>();
};

} // namespace Internal
} // namespace ECS
