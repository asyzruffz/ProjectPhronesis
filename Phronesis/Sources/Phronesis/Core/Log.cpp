
#include "StdAfx.hpp"
#include "Log.hpp"

#define SPDLOG_NO_NAME
#define SPDLOG_NO_THREAD_ID
#define SPDLOG_NO_ATOMIC_LEVELS
#define SPDLOG_DISABLE_DEFAULT_LOGGER

#define SPDLOG_LEVEL_NAMES { " ", "DEBUG", "INFO", "CMD", "ERROR", "CRITICAL", "OFF" }
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace Phronesis;

std::unique_ptr<Log> Log::instance = nullptr;

void Log::init()
{
	// create a console log sink (stdout, multi-threaded, colored)
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_pattern("[%^%=5l%$] %v");

	// create a file log sink
	std::filesystem::create_directory("Logs");
	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/game.log", true);
	file_sink->set_pattern("[%D %X.%e] [%l] %v");

	std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
	inst()->engineLogger = std::make_shared<spdlog::logger>("engine_logger", sinks.begin(), sinks.end());
	//inst()->engineLogger->set_level(spdlog::level::trace);

	// create an in-game gui log sink
	//auto gui_sink = std::make_shared<spdlog::sinks::gui_sink_mt>();
	//gui_sink->set_pattern("[%=7l] %v");

	//sinks.push_back(gui_sink);
	inst()->gameLogger = std::make_shared<spdlog::logger>("game_logger", sinks.begin(), sinks.end());
	//inst()->gameLogger->set_level(spdlog::level::trace);
}

template<typename... Args>
void Log::info(const std::string& msg, const Args& ...args)
{
	inst()->engineLogger->info(msg.c_str(), args...);
}

template<typename... Args>
void Log::error(const std::string& msg, const Args& ...args)
{
	inst()->engineLogger->error(msg.c_str(), args...);
}

template<typename... Args>
void Log::debug(const std::string& msg, const Args& ...args)
{
	inst()->gameLogger->debug(msg.c_str(), args...);
}

template<typename... Args>
void Log::print(const std::string& msg, const Args& ...args)
{
	inst()->gameLogger->trace(msg.c_str(), args...);
}

void Log::echo(const std::string& msg)
{
	inst()->gameLogger->warn(msg.c_str());
}

Log* Log::inst()
{
	if(instance == nullptr)
	{
		instance = std::unique_ptr<Log>(new Log);
	}
	return instance.get();
}

void solveLinkingIssue()
{
	Log::info("Info");
	Log::error("Error");
	Log::debug("Debug");
	Log::print("Print");

	Log::info("Info {}", 1);
	Log::error("Error {}", 1);
	Log::debug("Debug {}", 1);
	Log::print("Print {}", 1);

	Log::info("Info {}", 0.1);
	Log::error("Error {}", 0.1);
	Log::debug("Debug {}", 0.1);
	Log::print("Print {}", 0.1);

	Log::info("Info {}", "!");
	Log::error("Error {}", "!");
	Log::debug("Debug {}", "!");
	Log::print("Print {}", "!");

	const char* cstr = "!";
	Log::info("Info {}", cstr);
	Log::error("Error {}", cstr);
	Log::debug("Debug {}", cstr);
	Log::print("Print {}", cstr);

	std::string s = "!";
	Log::info("Info {}", s);
	Log::error("Error {}", s);
	Log::debug("Debug {}", s);
	Log::print("Print {}", s);
}