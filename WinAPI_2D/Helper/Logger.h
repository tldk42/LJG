#pragma once
#include <spdlog/spdlog.h>

namespace LJG
{
	class Logger
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetDXLogger()
		{
			return s_DXLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_DXLogger;
	};

#define LOG_CORE_TRACE(...)	  Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)     Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)     Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)    Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...)    Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_DX_TRACE(...)	  Logger::GetDXLogger()->trace(__VA_ARGS__)
#define LOG_DX_INFO(...)     Logger::GetDXLogger()->info(__VA_ARGS__)
#define LOG_DX_WARN(...)     Logger::GetDXLogger()->warn(__VA_ARGS__)
#define LOG_DX_ERROR(...)    Logger::GetDXLogger()->error(__VA_ARGS__)
#define LOG_DX_FATAL(...)    Logger::GetDXLogger()->critical(__VA_ARGS__)
}
