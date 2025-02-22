#pragma once

#include <type_traits>
#include <vector>

#include "Entity.h"

namespace ECS {

template< class T >
concept ComponentType = requires {
	requires std::is_trivial_v< T >;
	requires std::is_trivially_destructible_v< T >;
	requires std::is_move_constructible_v< T >;
};

class IComponentDataArray
{
public:
	virtual ~IComponentDataArray() = default;

	virtual bool Empty() const noexcept = 0;

	virtual bool Has(const Entity& entity) const noexcept = 0;

	virtual void Remove(const Entity& entity) = 0;

	virtual size_t Size() const noexcept = 0;
};

template< ComponentType T >
class ComponentDataArray : public IComponentDataArray
{
public:
	using Type = T;

	ComponentDataArray() = default;

	bool Empty() const noexcept override
	{
		return m_dense.empty();
	}

	bool Has(const Entity& entity) const noexcept override
	{
		return entity.index < m_sparse.size() && getIndex(entity) != kMaxSparseValue && m_dense.at(getIndex(entity)) == entity.index;
	}

	void Clear()
	{
		m_dense.clear();
		m_sparse.clear();
		m_packed.clear();
	}

	void ShrinkToFit()
	{
		m_dense.shrink_to_fit();
		m_sparse.shrink_to_fit();
		m_packed.shrink_to_fit();
	}

	bool Add(const Entity& entity, const Type& value)
	{
		if (Has(entity))
		{
			return false;
		}

		// コンポーネントを持つエンティティの登録
		if (entity.index >= m_sparse.size())
		{
			m_sparse.resize(static_cast< size_t >(entity.index) + 1, kMaxSparseValue);
		}
		m_sparse.at(entity.index) = m_dense.size(); // 実体の数を添え字とする
		m_dense.emplace_back(entity.index);

		// コンポーネントの追加
		m_packed.emplace_back(value);

		return true;
	}

	void Remove(const Entity& entity) override
	{
		if (!Has(entity))
		{
			return;
		}

		// 末尾と添え字の位置を入れ替えて末尾を削除する
		std::swap(m_packed.at(getIndex(entity)), m_packed.back());
		m_packed.pop_back();

		// エンティティも同様に削除
		const auto back = m_dense.back();
		std::swap(m_dense.at(getIndex(entity)), m_dense.back());
		std::swap(m_sparse.at(back), m_sparse.at(entity.index));
		m_dense.pop_back();
		m_sparse.at(entity.index) = kMaxSparseValue; // 無効値を入れて使用できないようにする
	}

	const Type* Get(const Entity& entity) const
	{
		if (!Has(entity))
		{
			return nullptr;
		}

		return &m_packed.at(getIndex(entity));
	}

	Type* Get(const Entity& entity)
	{
		return const_cast< Type* >(std::as_const(*this).Get(entity));
	}

	void Set(const Entity entity, const Type& value)
	{
		if (!Has(entity))
		{
			return;
		}

		m_packed.at(getIndex(entity)) = value;
	}

	size_t Size() const noexcept override
	{
		return m_dense.size();
	}

private:
	static constexpr auto kMaxSparseValue = std::numeric_limits< size_t >::max();

	size_t getIndex(const Entity& entity) const
	{
		return m_sparse.at(entity.index);
	}

	std::vector< EntityIndexType > m_dense;
	std::vector< size_t >          m_sparse;
	std::vector< Type >            m_packed;
};

} // namespace ECS
