
#include "StdAfx.hpp"
#include "SandboxGame.hpp"

#include "Phronesis/SceneManagement/Scenes.hpp"
#include "Scene1.hpp"

SandboxGame::SandboxGame()
{
	setFpsLimit(120);
}

void SandboxGame::init()
{
	Phronesis::Game::init();
	getModule<Phronesis::Scenes>()->setScene(new Scene1);
}
