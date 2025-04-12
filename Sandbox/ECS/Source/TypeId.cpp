#include "TypeId.h"

#include <atomic>

namespace ECS {
namespace Internal {

template< TypeIdTag Tag >
TypeId MakeTypeId<Tag>() noexcept
{
	static std::atomic< TypeId > id;
	return id++ | static_cast< TypeId >(Tag) << 28; // 最上位ビットにタグを埋め込み
}

} // namespace Internal
} // namespace ECS
