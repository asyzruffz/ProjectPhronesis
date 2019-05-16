
#include "StdAfx.hpp"
#include "ModuleHandler.hpp"

using namespace Phronesis;


void ModuleHandler::updateStage(const Module::Stage & stage)
{
	for(const auto &typeId : modules)
	{
		if(typeId.second.stage != stage) continue;

		auto& module = typeId.second.module;
		if(module) module->update();
	}
}
