#pragma once

#ifdef JN_PLATFORM_WINDOWS
	#ifdef JN_BUILD_DLL
		#define JONA_API __declspec(dllexport)
	#else
		#define JONA_API __declspec(dllimport)
	#endif
#else
	#error Jona only supports Windows!
#endif

#ifdef JN_ENABLE_ASSERTS
	#define JN_ASSERT(x, ...) { if(!(x)) { JN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JN_CORE_ASSERT(x, ...) { if(!(x)) { JN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JN_ASSERT(x, ...)
	#define JN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define JN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)