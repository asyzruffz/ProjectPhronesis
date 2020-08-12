
#include "StdAfx.hpp"
#include "TestScript.hpp"

#include "Phronesis/SceneManagement/Component.ext.hpp"
#include "Phronesis/Components.hpp"
#include "Phronesis/Core/Log.hpp"

void TestScript::start()
{
	val = 0.0f;
	dir = 1;

	if(!has<Phronesis::Camera>())
	{
		Phronesis::Log::debug("No camera component found");
	} else Phronesis::Log::debug("Camera component found");
}

void TestScript::update()
{
	if(val >= 1 || val <= -1)
	{
		dir *= -1;
		Phronesis::Log::debug("Zoom changes to {}", (1.0f + 0.00001f * dir));
	}

	val += 0.00001f * dir;

	if(has<Phronesis::Camera>())
	{
		auto& cam = get<Phronesis::Camera>();
		cam.setZoom(1.0f + 0.00001f * dir);
	}
}
