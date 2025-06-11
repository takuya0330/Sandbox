#pragma once

#include "TypeInfo.h"

#include <type_traits>

namespace ECS {

template<typename T>
concept ComponentDataType = requires {
	requires std::is_trivially_copyable_v<T>;
	requires std::is_standard_layout_v<T>;
};

template<ComponentDataType T, typename = std::enable_if_t<std::is_same_v<T, std::remove_cvref_t<T>>>>
struct ComponentTypeInfoTraits : public TypeInfoTraits
{
	static const NameType GetTypeName() noexcept
	{
		return "Unknown ComponentType";
	}
};
template<ComponentDataType T>
using ComponentTypeInfo = TypeInfo<T, ComponentTypeInfoTraits<T>>;

struct ComponentType
{
	TypeIndex id;
	uint32_t  size;

	inline constexpr bool operator==(const ComponentType& c) const noexcept
	{
		return id == c.id && size == c.size;
	}

	inline constexpr bool operator!=(const ComponentType& c) const noexcept
	{
		return !(*this == c);
	}
};

template<ComponentDataType T>
ComponentType GetComponentType() noexcept
{
	return {
		ComponentTypeInfo<T>::GetTypeIndex(),
		sizeof(T),
	};
}

namespace Internal {

TypeIndex MakeComponentTypeIndex() noexcept;

} // namespace Internal
} // namespace ECS

#define ECS_COMPONENT_DATA(Type)                                                    \
	template<> struct ECS::ComponentTypeInfoTraits<Type> : public TypeInfoTraits    \
	{                                                                               \
		static const NameType GetTypeName() noexcept                                \
		{                                                                           \
			return #Type;                                                           \
		}                                                                           \
		static const IndexType GetTypeIndex() noexcept                              \
		{                                                                           \
			static const IndexType index = ECS::Internal::MakeComponentTypeIndex(); \
			return index;                                                           \
		}                                                                           \
	}
