#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Jona {

	class JONA_API Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define JN_CORE_TRACE(...)		::Jona::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JN_CORE_INFO(...)		::Jona::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JN_CORE_WARN(...)		::Jona::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JN_CORE_ERROR(...)		::Jona::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JN_CORE_FATAL(...)		::Jona::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define JN_TRACE(...)			::Jona::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JN_INFO(...)			::Jona::Log::GetClientLogger()->info(__VA_ARGS__)
#define JN_WARN(...)			::Jona::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JN_ERROR(...)			::Jona::Log::GetClientLogger()->error(__VA_ARGS__)
#define JN_FATAL(...)			::Jona::Log::GetClientLogger()->critical(__VA_ARGS__)