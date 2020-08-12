#pragma once

#include "Phronesis/SceneManagement/Component.hpp"

class TestScript : public Phronesis::Component
{
public:

	void start() override;
	void update() override;

private:
	float val;
	int dir;
};
