#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Component.hpp"

namespace Phronesis
{
	class Entity : public std::enable_shared_from_this<Entity>
	{
	public:
		Entity();
		virtual ~Entity() = default;

		typedef std::shared_ptr<Entity> Ptr;

		template <typename T, typename... Args>
		T& addComponent(Args... args);
		template <typename T>
		bool has() noexcept;
		template <typename T>
		T& get();

		Entity::Ptr setParent(const Entity::Ptr& parent);
		Entity::Ptr getParent() const;
		std::vector<Entity::Ptr>& getChildren();
		void setEnabled(bool isEnabled);
		bool isEnabled() const;
		std::string getName() const;

	private:
		friend class Scene;

		void start();
		void update();

	private:
		std::unordered_map<TypeID, Component::Ptr> components;
		std::weak_ptr<Entity> parent;
		std::vector<Entity::Ptr> children;

		std::string name;
		bool enabled;
	};

	template <typename T, typename... Args>
	T& Entity::addComponent(Args... args)
	{
		const auto typeId = getComponentTypeId<T>();

		Component::Ptr newComponent = std::make_shared<T>(args...);
		components[typeId] = newComponent;
		newComponent->owner = weak_from_this();

		return *(std::dynamic_pointer_cast<T>(newComponent));
	}

	template <typename T>
	bool Entity::has() noexcept
	{
		const auto typeId = getComponentTypeId<T>();
		return components.count(typeId) > 0;
	}

	template <typename T>
	T& Entity::get()
	{
		const auto typeId = getComponentTypeId<T>();
		return *(std::dynamic_pointer_cast<T>(components[typeId]));
	}
}
