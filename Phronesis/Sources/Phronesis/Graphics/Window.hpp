#pragma once

#include <vector>

#include "Phronesis/Core/Module.hpp"

namespace Phronesis
{
	class Window : public Module
	{
	public:
		void init(int width, int height, const char* title);
		void update() override;
		
		std::vector<const char*> getRequiredExtensions() const;

	private:

	};
}
