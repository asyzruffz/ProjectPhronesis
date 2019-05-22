#pragma once

#include <memory>

#define SPDLOG_NO_NAME
#define SPDLOG_NO_THREAD_ID
#define SPDLOG_NO_ATOMIC_LEVELS
#define SPDLOG_DISABLE_DEFAULT_LOGGER

#define SPDLOG_LEVEL_NAMES { " ", "DEBUG", "INFO", "CMD", "ERROR", "CRITICAL", "OFF" }
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "spdlog/spdlog.h"

namespace Phronesis
{
	class Log
	{
	public:
		static void init();

		// log into console and file
		template<typename... Args>
		static void info(const std::string& msg, const Args& ...args)
		{
			inst()->engineLogger->info(msg.c_str(), args...);
		}

		template<typename T>
		static void info(const T& msg)
		{
			inst()->engineLogger->info(msg);
		}

		template<typename... Args>
		static void error(const std::string& msg, const Args& ...args)
		{
			inst()->engineLogger->error(msg.c_str(), args...);
		}

		template<typename T>
		static void error(const T& msg)
		{
			inst()->engineLogger->error(msg);
		}

		// in addition to console & file, also log in-game
		template<typename... Args>
		static void debug(const std::string& msg, const Args& ...args)
		{
			inst()->gameLogger->debug(msg.c_str(), args...);
		}

		template<typename T>
		static void debug(const T& msg)
		{
			inst()->gameLogger->debug(msg);
		}

		template<typename... Args>
		static void print(const std::string& msg, const Args& ...args)
		{
			inst()->gameLogger->trace(msg.c_str(), args...);
		}

		template<typename T>
		static void print(const T& msg)
		{
			inst()->gameLogger->trace(msg);
		}

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
