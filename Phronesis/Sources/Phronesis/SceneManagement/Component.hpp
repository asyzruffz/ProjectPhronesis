#pragma once

#include <memory>

#include "Phronesis/Utilities/TypeInfo.hpp"

namespace Phronesis
{
	class Entity;

	class Component
	{
	public:
		Component();
		virtual ~Component() = default;

		typedef std::shared_ptr<Component> Ptr;

		virtual void start();
		virtual void update();

		Entity& getGameObject() const;

		template <typename T>
		bool has() const noexcept;
		template <typename T>
		T& get();

	private:
		friend class Entity;

		std::weak_ptr<Entity> owner;
	};

	template class TypeInfo<Component>;

	template<typename T>
	TypeID getComponentTypeId() noexcept
	{
		static_assert(std::is_base_of<Component, T>::value, "[ERROR] T must be a Component");
		return TypeInfo<Component>::getTypeId<T>();
	}
}
