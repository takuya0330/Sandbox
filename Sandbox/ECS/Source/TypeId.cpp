#include "../Include/TypeId.h"

#include <atomic>

namespace ECS {
namespace Internal {

template<TypeIdMetadata Meta>
TypeId MakeTypeId() noexcept
{
	static std::atomic<TypeId> id;
	return id++ | static_cast<TypeId>(Meta) << 28; // 上位4ビットにタグを埋め込み
}

uint32_t GetTypeIndex(TypeId id) noexcept
{
	return id & 0x0FFFFFFF; // 上位4ビットを削除
}

template TypeId MakeTypeId<TypeIdMetadata::kComponentData>() noexcept;
template TypeId MakeTypeId<TypeIdMetadata::kSharedComponentData>() noexcept;
template TypeId MakeTypeId<TypeIdMetadata::kSystem>() noexcept;

} // namespace Internal
} // namespace ECS
