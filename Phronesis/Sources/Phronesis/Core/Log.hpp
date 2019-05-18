#pragma once

#include <memory>

namespace spdlog { class logger; }

namespace Phronesis
{
	class Log
	{
	public:
		static void init();

		// log into console and file
		template<typename... Args>
		static void info(const std::string& msg, const Args& ...args);

		template<typename... Args>
		static void error(const std::string& msg, const Args& ...args);

		// in addition to console & file, also log in-game
		template<typename... Args>
		static void debug(const std::string& msg, const Args& ...args);

		template<typename... Args>
		static void print(const std::string& msg, const Args& ...args);

		static void echo(const std::string& msg); // for echoing user command

	private:
		Log() = default;
		static Log* inst();

	private:
		static std::unique_ptr<Log> instance;
		std::shared_ptr<spdlog::logger> engineLogger;
		std::shared_ptr<spdlog::logger> gameLogger; // log in-game
	};
}
