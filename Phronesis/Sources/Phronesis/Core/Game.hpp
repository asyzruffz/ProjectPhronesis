#pragma once

#include "ModuleHandler.hpp"
#include "Phronesis/Utilities/ElapsedTime.hpp"

namespace Phronesis
{
	class Renderer;

	class Game
	{
	public:
		Game();
		virtual ~Game() = default;

		void run();

		/**
		 * Sets the fps limit. -1 disables limits.
		 * @param fps The new frame per second limit.
		 */
		void setFpsLimit(const float& fps) { fpsLimit = fps; }
		const float& getFpsLimit() const { return fpsLimit; }
		
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

		ElapsedTime elapsedUpdate;
		ElapsedTime elapsedRender;

		float fpsLimit;
	};
}
