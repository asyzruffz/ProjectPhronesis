#pragma once

#include "ModuleHandler.hpp"

namespace Phronesis
{
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		void run();

		template<typename T>
		bool hasModule() const { return modules.has<T>(); }

		template<typename T>
		T* getModule() const { return modules.get<T>(); }

		static const int WIDTH;
		static const int HEIGHT;

	protected:
		void init();
		void mainLoop();
		void dispose();

	private:
		ModuleHandler modules;
	};
}
