#pragma once

#include "Phronesis/SceneManagement/Scene.hpp"

class Scene1 : public Phronesis::Scene
{
public:
	Scene1();

	void start() override;
	void update() override;
};
