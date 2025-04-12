#include "TypeId.h"

#include <atomic>

namespace ECS {
namespace Internal {

template<TypeIdTag Tag>
TypeId MakeTypeId<Tag>() noexcept
{
	static std::atomic<TypeId> id;
	return id++ | static_cast<TypeId>(Tag) << 28; // 最上位ビットにタグを埋め込み
}

uint32_t GetTypeIndex(TypeId id) noexcept
{
	return ((id << 4) >> 4); // 最上位ビットを削除
}

} // namespace Internal
} // namespace ECS
