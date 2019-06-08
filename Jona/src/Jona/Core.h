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