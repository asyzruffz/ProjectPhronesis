
#include "StdAfx.hpp"
#include "Scene1.hpp"

#include "Phronesis/Components.hpp"

Scene1::Scene1()
{
	auto testEntity = createEntity("Test Entity");
	testEntity->addComponent<Phronesis::Render2D>();
	testEntity->addComponent<Phronesis::Circle>(50.f);
}

void Scene1::start()
{
}

void Scene1::update()
{
}
