#include "ComponentGroup.h"

#include "EntityManager.h"

namespace ECS {
namespace {

void makeQueryData(std::vector<ComponentType>& outs, std::vector<ComponentType>&& components)
{
	if (components.empty())
		return;

	if (outs.empty())
	{
		outs = std::move(components);
	}
	else
	{
		for (auto& it : components)
		{
			// 重複している場合は無視する
			if (std::find(outs.begin(), outs.end(), it) != outs.end())
				continue;

			outs.emplace_back(it);
		}
	}
}

} // namespace

ComponentDataGroup::ComponentDataGroup()
    : m_query()
    , m_archetypes()
{
}

ComponentDataGroup& ComponentDataGroup::Include(std::initializer_list<ComponentType> components)
{
	std::vector<ComponentType> includes;
	Internal::MakeSortedComponentTypes(includes, components);

    makeQueryData(m_query.any, std::move(includes));
	
	return *this;
}

ComponentDataGroup& ComponentDataGroup::Exclude(std::initializer_list<ComponentType> components)
{
	std::vector<ComponentType> exclude;
	Internal::MakeSortedComponentTypes(exclude, components);

	makeQueryData(m_query.none, std::move(exclude));

	return *this;
}

void ComponentDataGroup::Build(EntityManager& entity_manager)
{
	m_archetypes.clear();
	entity_manager.FindMatchingArchetypes(m_archetypes, m_query);
}

size_t ComponentDataGroup::GetSize() const
{
	return m_archetypes.size();
}

} // namespace ECS
