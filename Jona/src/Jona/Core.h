#pragma once

#include <memory>

#ifdef JN_PLATFORM_WINDOWS
#if JN_DYNAMIC_LINK
	#ifdef JN_BUILD_DLL
		#define JONA_API __declspec(dllexport)
	#else
		#define JONA_API __declspec(dllimport)
	#endif
#else
	#define JONA_API
#endif
#else
	#error Jona only supports Windows!
#endif

#ifdef JN_DEBUG
	#define JN_ENABLE_ASSERTS
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

namespace Jona {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}