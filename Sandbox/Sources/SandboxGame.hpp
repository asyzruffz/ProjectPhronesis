#pragma once

#include "Phronesis/Core.hpp"

class SandboxGame : public Phronesis::Game
{
public:
	SandboxGame(const char* title);

	void init() override;
};
