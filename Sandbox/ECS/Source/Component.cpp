#include "Component.h"

#include <atomic>

namespace ECS {
namespace Internal {

uint64_t MakeComponentTypeIndex() noexcept
{
	static std::atomic<uint64_t> index = 0;
	return index++;
}

} // namespace Internal
} // namespace ECS
