
#include "StdAfx.hpp"
#include "Log.hpp"

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
