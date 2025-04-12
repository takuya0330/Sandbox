#include "Archetype.h"

#include <algorithm>
#include <numeric>

namespace ECS {

Archetype::Archetype(std::initializer_list<ComponentType> components)
    : m_components(components)
    , m_memory_size(0)
{
	// 昇順にソート
	std::sort(m_components.begin(), m_components.end(), [](const ComponentType& a, const ComponentType& b)
	    {
		    return a.id < b.id;
	    });

	// このアーキタイプが持つコンポーネントサイズの合計値
	m_memory_size = std::accumulate(m_components.begin(), m_components.end(), 0, [](int i, const ComponentType& c)
	    {
		    return i + c.size;
	    });
}

} // namespace ECS
