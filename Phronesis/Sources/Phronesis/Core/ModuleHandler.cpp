
#include "StdAfx.hpp"
#include "ModuleHandler.hpp"

#include "Phronesis/Graphics/Renderer.hpp"

using namespace Phronesis;


ModuleHandler::ModuleHandler()
{
}

ModuleHandler::~ModuleHandler()
{
}

void ModuleHandler::updateStage(const Module::Stage & stage)
{
	for(const auto &typeId : modules)
	{
		if(typeId.second.stage != stage) continue;

		auto& module = typeId.second.module;
		if(module) module->update();
	}
}
