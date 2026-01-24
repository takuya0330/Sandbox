#pragma once

#include "DLLImport/Include/STL/FNV1.h"
#include "DLLImport/Include/STL/Hex.h"

namespace STL {

template<size_t N>
class TEncryptedString
{
public:
	constexpr explicit TEncryptedString(const std::array<char, N>& str)
	    : m_value(str)
	{
	}

	template<size_t N2>
	constexpr bool operator==(const TEncryptedString<N2>& rhs) const noexcept
	{
		return N == N2 && GetHash() == rhs.GetHash();
	}

	template<size_t N2>
	constexpr bool operator!=(const TEncryptedString<N2>& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	constexpr std::string_view ToStringView() const noexcept
	{
		return { m_value.data(), m_value.size() };
	}

	constexpr bool IsEmpty() const noexcept
	{
		return m_value.empty();
	}

	constexpr const char* GetData() const noexcept
	{
		return m_value.data();
	}

	constexpr size_t GetSize() const noexcept
	{
		return m_value.size();
	}

	constexpr uint64_t GetHash() const noexcept
	{
		return TFNV1<uint64_t>::Hash(m_value.data(), m_value.size() - 1);
	}

private:
	std::array<char, N> m_value;
};

template<RequiresCharType T, size_t N>
constexpr auto MakeEncryptedString(const T (&str)[N])
{
	return TEncryptedString(ToHex(str, true));
}

template<RequiresCharType T, size_t N>
const auto MakeDecryptedString(const TEncryptedString<N>& encrypted)
{
	return FromHex<T>(encrypted.ToStringView(), true);
}

} // namespace STL
