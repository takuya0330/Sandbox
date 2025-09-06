#include <array>
#include <iostream>
#include <string>

namespace {

template<typename T>
constexpr T xorshift(uint32_t seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return static_cast<T>(seed & std::numeric_limits<T>::max());
}

template<typename T, size_t N>
constexpr auto to_hex(const T (&str)[N], bool is_xor = false, bool upper = false)
{
	constexpr std::array<char, 16> k_lower = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};
	constexpr std::array<char, 16> k_upper = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	const auto&      hex     = upper ? k_upper : k_lower;
	constexpr size_t size    = sizeof(T);
	constexpr size_t hex_len = size * 2;

	std::array<char, N * hex_len + 1> ret;
	for (size_t i = 0; i < N; ++i)
	{
		auto v = static_cast<std::make_unsigned_t<T>>(str[i]);
		for (size_t j = 0; j < size; ++j)
		{
			auto c = static_cast<unsigned char>(v >> (8 * j));
			if (is_xor)
				c ^= xorshift<unsigned char>(static_cast<uint32_t>(i * size + j + 1));

			ret[i * hex_len + j * 2]     = hex[c >> 4];
			ret[i * hex_len + j * 2 + 1] = hex[c & 0x0F];
		}
	}
	ret[N * hex_len] = '\0';
	return ret;
}

constexpr unsigned char hex_to_val(char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	if ('a' <= c && c <= 'f')
		return c - 'a' + 10;
	if ('A' <= c && c <= 'F')
		return c - 'A' + 10;
	return 0;
}

template<typename T>
T from_hex_one(std::string_view sv, size_t i, bool is_xor = false)
{
	constexpr size_t size = sizeof(T);
	if (sv.size() % size * 2 != 0)
	{
		return {};
	}

	T v = {};
	for (size_t j = 0; j < size; ++j)
	{
		unsigned char c = (hex_to_val(sv[j * 2]) << 4) | (hex_to_val(sv[j * 2 + 1]));
		if (is_xor)
			c ^= xorshift<unsigned char>(static_cast<uint32_t>(i * size + j + 1));

		v |= static_cast<T>(c) << (j * 8);
	}
	return v;
}

template<typename T>
std::basic_string<T> from_hex(std::string_view sv, bool is_xor = false)
{
	constexpr size_t size     = sizeof(T);
	constexpr size_t hex_len  = size * 2;
	const size_t     str_size = sv.size() - 1;
	if (str_size % hex_len != 0)
	{
		return {};
	}

	size_t               num_element = str_size / hex_len;
	std::basic_string<T> ret;
	ret.reserve(num_element);
	for (size_t i = 0; i < num_element; ++i)
	{
		ret.push_back(from_hex_one<T>(sv.substr(i * hex_len, hex_len), i, is_xor));
	}
	return ret;
}

template<size_t N>
class encrypted_string
{
public:
	constexpr explicit encrypted_string(const std::array<char, N>& str)
	    : m_value(str)
	{
	}

	constexpr std::string_view to_string_view() const noexcept
	{
		return { m_value.data(), m_value.size() };
	}

	template<size_t N2>
	constexpr bool operator==(const encrypted_string<N2>& rhs) const noexcept
	{
		return N == N2 && hash() == rhs.hash();
	}

	template<size_t N2>
	constexpr bool operator!=(const encrypted_string<N2>& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	constexpr bool empty() const noexcept
	{
		return m_value.empty();
	}

	constexpr const char* data() const noexcept
	{
		return m_value.data();
	}

	constexpr size_t size() const noexcept
	{
		return m_value.size();
	}

	constexpr uint64_t hash() const noexcept
	{
		return 0;
	}

private:
	std::array<char, N> m_value;
};

template<typename T, size_t N>
constexpr auto make_encrypted_string(const T (&str)[N])
{
	return encrypted_string(to_hex(str, true));
}

template<typename T, size_t N>
const auto make_decrypted_string(const encrypted_string<N>& encrypted)
{
	return from_hex<T>(encrypted.to_string_view(), true);
}

} // namespace

int main(int, char**)
{
	{
		std::cout << "[TEST] char hex" << std::endl;
		constexpr auto hex = to_hex("skeletal_mesh_component");
		std::cout << hex.data() << std::endl;
		std::cout << from_hex<char>(std::string_view(hex.data(), hex.size())) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "[TEST] wchar_t hex" << std::endl;
		constexpr auto hex = to_hex(L"skeletal_mesh_component");
		std::cout << hex.data() << std::endl;
		std::wcout << from_hex<wchar_t>(std::string_view(hex.data(), hex.size())) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "[TEST] hex and xor" << std::endl;
		constexpr auto hex = to_hex("SkeletalMeshComponent", true);
		std::cout << hex.data() << std::endl;
		std::cout << from_hex<char>(std::string_view(hex.data(), hex.size()), true) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "[TEST] encrypted_string" << std::endl;
		constexpr auto encrypted = make_encrypted_string("GameWorld");
		std::cout << encrypted.data() << std::endl;
		std::cout << make_decrypted_string<char>(encrypted) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "[TEST] compare encrypted_string" << std::endl;
		constexpr auto encrypted1 = make_encrypted_string("GameWorld");
		std::cout << encrypted1.data() << std::endl;
		std::cout << make_decrypted_string<char>(encrypted1) << std::endl;
		constexpr auto encrypted2 = make_encrypted_string("GameWorld");
		std::cout << encrypted2.data() << std::endl;
		std::cout << make_decrypted_string<char>(encrypted2) << std::endl;
		constexpr auto encrypted3 = make_encrypted_string("GameWorld3");
		std::cout << encrypted3.data() << std::endl;
		std::cout << make_decrypted_string<char>(encrypted3) << std::endl;
		constexpr auto check1 = (encrypted1 == encrypted2) ? "equal" : "not equal";
		std::cout << check1 << std::endl;
		constexpr auto check2 = (encrypted1 != encrypted3) ? "not equal" : "equal";
		std::cout << check2 << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
