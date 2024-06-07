#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


namespace LJG
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_DXLogger;

	void Logger::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Set Core Logger
		s_CoreLogger = spdlog::stdout_color_mt("Jacob Core");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Set DirectX Logger
		s_DXLogger = spdlog::stdout_color_mt("------DX------");
		s_DXLogger->set_level(spdlog::level::trace);
	}
}
