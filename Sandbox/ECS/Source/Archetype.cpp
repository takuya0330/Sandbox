#include "Archetype.h"

#include <algorithm>
#include <numeric>

namespace ECS {
namespace {

constexpr size_t alignup(size_t value, size_t align)
{
	return (value + (align - 1)) & ~(align - 1);
}

} // namespace

Archetype::Archetype(std::initializer_list<ComponentType> components)
    : m_components(components)
    , m_offset_map()
    , m_total_size(0)
    , m_max_entity_count(0)
    , m_memory_size(0)
{
	// 昇順にソート
	std::sort(m_components.begin(), m_components.end(), [](const ComponentType& a, const ComponentType& b)
	    {
		    return a.id < b.id;
	    });

	// コンポーネントサイズの合計
	m_total_size = std::accumulate(m_components.begin(), m_components.end(), 0ull, [](size_t i, const ComponentType& c)
	    {
		    return i + alignup(c.size, c.alignment);
	    });

	// チャンク内のエンティティの最大数
	m_max_entity_count = kMaxChunkSize / m_total_size;

	// チャンク内のメモリオフセット位置とメモリ最大値を計算
	for (const auto& it : m_components)
	{
		m_memory_size                               = alignup(m_memory_size, it.alignment);
		m_offset_map[Internal::GetTypeIndex(it.id)] = m_memory_size;
		m_memory_size += it.size * m_max_entity_count;
	}
}

const size_t Archetype::GetMemoryOffset(TypeId id) const
{
	const auto& it = m_offset_map.find(Internal::GetTypeIndex(id));
	if (it == m_offset_map.end())
		return -1;

	return it->second;
}

} // namespace ECS
