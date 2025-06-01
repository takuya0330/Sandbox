#include "Archetype.h"

#include <numeric>

namespace ECS {
namespace {

constexpr uint32_t kMaxChunkSize = 16 * 1024;

constexpr size_t alignup(size_t value, size_t align)
{
	return (value + (align - 1)) & ~(align - 1);
}

} // namespace

Archetype::Archetype(const std::vector<ComponentType>& components)
    : m_components(components)
    , m_chunk_offsets()
    , m_total_size(0)
    , m_entity_capacity(0)
    , m_memory_size(0)
    , m_chunks()
{
	// MEMO: components は既にソートされている前提

	// コンポーネントサイズの合計
	m_total_size = std::accumulate(m_components.begin(), m_components.end(), 0ull, [](size_t i, const ComponentType& c)
	    {
		    return i + alignup(c.size, c.alignment);
	    });

	// チャンク内のエンティティの最大数
	m_entity_capacity = kMaxChunkSize / m_total_size;

	// チャンク内のメモリオフセット位置とメモリ最大値を計算
	for (const auto& it : m_components)
	{
		m_memory_size             = alignup(m_memory_size, it.alignment);
		m_chunk_offsets[it.index] = m_memory_size;
		m_memory_size += it.size * m_entity_capacity;
	}
}

const size_t Archetype::GetChunkOffset(TypeIndex index) const
{
	const auto& it = m_chunk_offsets.find(index);
	if (it == m_chunk_offsets.end())
		return -1;

	return it->second;
}

bool Archetype::isEqual(const std::vector<ComponentType>& components) const noexcept
{
	return std::equal(m_components.begin(), m_components.end(), components.begin(), components.end());
}

} // namespace ECS
