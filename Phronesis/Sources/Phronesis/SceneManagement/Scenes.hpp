#pragma once

#include <vector>

#include "Phronesis/Core/Module.hpp"
#include "Scene.hpp"

namespace Phronesis
{
	class Scenes : public Module
	{
	public:
		void init();
		void update() override;
		void dispose() override;

		void setScene(Scene* newScene);
		Scene* getCurrentScene();

		template<typename T>
		std::vector<T*> getAll();

	private:
		Scene::Ptr currentScene;

	};

	template<typename T>
	std::vector<T*> Scenes::getAll()
	{
		std::vector<T*> comps;
		if(currentScene)
		{
			currentScene->root->getInChildren<T>(comps);
		}
		else
		{
			Log::debug("Current scene is null");
		}
		return comps;
	}
}
