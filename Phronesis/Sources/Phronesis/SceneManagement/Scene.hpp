#pragma once

#include <memory>

#include "Entity.hpp"

namespace Phronesis
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		typedef std::unique_ptr<Scene> Ptr;

		virtual void start();
		virtual void update();

		Entity::Ptr createEntity(const char* name = "Unnamed Entity");

	private:
		friend class Scenes;

		bool hasStarted();
		void setStarted();
		void internalStart();
		void internalUpdate();

		Entity::Ptr addToRoot(Entity* newEntity);

	private:
		bool isStarted;

		Entity::Ptr root;
		Component::Ptr mainCamera;
	};
}
