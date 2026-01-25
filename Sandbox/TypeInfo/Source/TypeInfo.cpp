#include "TypeInfo/Include/TypeInfo.h"

bool TypeInfo::QueryInterface(uint64_t hash) const
{
	const TypeInfo* curr = this;
	while (curr)
	{
		if (curr->m_hash == hash)
			return true;
		curr = curr->GetSuperTypeInfo();
	}
	return false;
}

bool TypeInfo::QueryInterface(const TypeInfo* info) const
{
	if (info == nullptr)
		return false;

	const TypeInfo* curr = this;
	while (curr)
	{
		if (curr == info || curr->m_hash == info->m_hash)
			return true;
		curr = curr->GetSuperTypeInfo();
	}
	return false;
}

const TypeInfo* TypeInfo::GetSuperTypeInfo() const
{
	return m_super_type_info;
}

const std::string TypeInfo::GetName() const
{
	return FromHex<char>(m_encrypted_name, true);
}

const uint64_t TypeInfo::GetHash() const
{
	return m_hash;
}

const uint32_t TypeInfo::GetSize() const
{
	return m_size;
}
