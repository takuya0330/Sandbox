#pragma once

#include "TypeInfo.h"

namespace ECS {

template<typename T>
concept ComponentDataType = requires {
	requires std::is_trivially_copyable_v<T>;
	requires std::is_standard_layout_v<T>;
	requires std::is_same_v<T, std::remove_cvref_t<T>>;
};

template<ComponentDataType T>
struct ComponentTypeTraits : public TypeInfoTraits
{
	static const NameType GetTypeName() noexcept
	{
		return "Unknown ComponentType";
	}
};
template<ComponentDataType T>
using ComponentTypeInfo = TypeInfo<T, ComponentTypeTraits<T>>;

struct ComponentType
{
	const char* name;
	uint64_t    id;
	size_t      size;
	size_t      alignment;

	inline constexpr bool operator==(const ComponentType& c) const noexcept
	{
		return id == c.id && size == c.size && alignment == c.alignment;
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
		ComponentTypeInfo<T>::GetTypeName(),
		ComponentTypeInfo<T>::GetTypeIndex(),
		sizeof(T),
		alignof(T)
	};
}

class ComponentDataArray
{
public:
};

class ComponentDataGroup
{
public:
};

namespace Internal {

uint64_t MakeComponentTypeIndex() noexcept;

} // namespace Internal
} // namespace ECS

#define ECS_COMPONENT_DATA(Type)                                                    \
	template<> struct ECS::ComponentTypeTraits<Type> : public TypeInfoTraits        \
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
