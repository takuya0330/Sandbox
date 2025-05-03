#include "TypeId.h"

#include <atomic>

namespace ECS {
namespace Internal {

TypeId MakeTypeId(Metadata meta) noexcept
{
	static std::atomic<TypeId> id;
	return id++ | static_cast<TypeId>(meta) << 28; // 上位4ビットにタグを埋め込み
}

uint32_t GetTypeIndex(TypeId id) noexcept
{
	return id & 0x0FFFFFFF; // 上位4ビットを削除
}

} // namespace Internal
} // namespace ECS
