#include "Component.h"

#include <atomic>

namespace ECS {
namespace Internal {

TypeIndex MakeComponentTypeIndex() noexcept
{
	static std::atomic<TypeIndex> index = 0;
	return index++;
}

} // namespace Internal
} // namespace ECS
