#pragma once

#include "ModuleHandler.hpp"
#include "Phronesis/Utilities/ElapsedTime.hpp"
#include "Phronesis/Utilities/TimeUpdate.hpp"

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
		
		/**
		 * Gets the delta (seconds) between updates.
		 * @return The delta between updates.
		 */
		const Time& getDeltaTime() const;

		/**
		 * Gets the average UPS over a short interval.
		 * @return The updates per second.
		 */
		const unsigned int& getUps() const;

		/**
		 * Gets the average FPS over a short interval.
		 * @return The frames per second.
		 */
		const unsigned int& getFps() const;

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
		Delta deltaUpdate;
		ChangePerSecond ups, fps;

		float fpsLimit;
	};
}
