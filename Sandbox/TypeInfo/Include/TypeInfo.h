#pragma once

#include "TypeInfo/Include/EncryptedString.h"

class TypeInfo
{
public:
	template<size_t N>
	explicit TypeInfo(const TEncryptedString<N>& encrypted, const uint32_t size, const TypeInfo* super)
	    : m_encrypted_name(encrypted.ToStringView())
	    , m_hash(encrypted.GetHash())
	    , m_size(size)
	    , m_super_type_info(super)
	{
	}

	bool QueryInterface(uint64_t hash) const;

	bool QueryInterface(const TypeInfo* info) const;

	const TypeInfo* GetSuperTypeInfo() const;

	const std::string GetName() const;

	const uint64_t GetHash() const;

	const uint32_t GetSize() const;

public:
	template<typename T>
	bool QueryInterface() const
	{
		return QueryInterface(T::GetTypeInfo());
	}

private:
	std::string_view m_encrypted_name;
	const uint64_t   m_hash;
	const uint32_t   m_size;
	const TypeInfo*  m_super_type_info;
};

#define STRING_IMPL(x) #x
#define STRING(x)      STRING_IMPL(x)

#define TYPE_INFO_1(This)                                               \
	static const TypeInfo* GetTypeInfo()                                \
	{                                                                   \
		static constexpr auto name = MakeEncryptedString(STRING(This)); \
		static const TypeInfo info(name, sizeof(This), nullptr);        \
		return &info;                                                   \
	}
#define TYPE_INFO_2(This, Super)                                              \
	static const TypeInfo* GetTypeInfo()                                      \
	{                                                                         \
		static constexpr auto name = MakeEncryptedString(STRING(This));       \
		static const TypeInfo info(name, sizeof(This), Super::GetTypeInfo()); \
		return &info;                                                         \
	}
