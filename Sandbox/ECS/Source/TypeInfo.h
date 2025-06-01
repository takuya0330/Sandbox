#pragma once

#include <cstdint>

namespace ECS {
namespace Internal {

// https://stackoverflow.com/a/74453799/475145

template<typename T, T Index>
struct IndexCounter
{
	using Tag = IndexCounter;

	struct Generator
	{
		friend constexpr auto _Check(Tag)
		{
			return true;
		}
	};
	friend constexpr auto _Check(Tag);

	template<typename T = Tag, auto = _Check(T())>
	static constexpr auto Exists(auto)
	{
		return true;
	}

	static constexpr auto Exists(...)
	{
#pragma warning(disable : 6319)
		return Generator(), false;
#pragma warning(default : 6319)
	}
};

template<typename T, typename U, U Index = U()>
constexpr U TypeIndexOf() noexcept
{
	if constexpr (Internal::IndexCounter<U, Index>::Exists(Index))
	{
		return TypeIndexOf<T, U, Index + 1>();
	}
	return Index;
}

} // namespace Internal

using TypeIndex = uint32_t;

template<typename T, typename = void>
struct TypeInfo
{
	static constexpr const char* GetTypeName() noexcept
	{
		return "";
	}

	static constexpr TypeIndex GetTypeIndex() noexcept
	{
		return 0xFFFFFFFF;
	}
};

} // namespace ECS

#define ECS_TYPE_INFO(Type)                                                                                  \
	template<> struct ECS::TypeInfo<Type, std::enable_if_t<std::is_same_v<Type, std::remove_cvref_t<Type>>>> \
	{                                                                                                        \
		static constexpr const char* GetTypeName() noexcept                                                  \
		{                                                                                                    \
			return #Type;                                                                                    \
		}                                                                                                    \
		static constexpr ECS::TypeIndex GetTypeIndex() noexcept                                              \
		{                                                                                                    \
			return ECS::Internal::TypeIndexOf<Type, ECS::TypeIndex>();                                       \
		}                                                                                                    \
	}
