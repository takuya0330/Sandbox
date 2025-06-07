#include "ComponentDataGroup.h"

#include "EntityManager.h"

namespace ECS {

ComponentDataGroup::ComponentDataGroup(EntityDataLocation* location)
    : m_location(location)
{
}

} // namespace ECS
