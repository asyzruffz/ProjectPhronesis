#pragma once

#include "Phronesis/Core/Module.hpp"
#include "Scene.hpp"

namespace Phronesis
{
	class Scenes : public Module
	{
	public:
		void init();
		void update() override;
		void dispose();

		void setScene(Scene* newScene);
		Scene& getCurrentScene();

	private:
		Scene::Ptr currentScene;

	};
}
