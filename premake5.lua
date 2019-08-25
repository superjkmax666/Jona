workspace "Jona"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Jona/vendor/GLFW/include"
IncludeDir["Glad"] = "Jona/vendor/Glad/include"
IncludeDir["Imgui"] = "Jona/vendor/imgui"
IncludeDir["glm"] = "Jona/vendor/glm"
IncludeDir["stb_image"] = "Jona/vendor/stb_image"

group "Dependencies"
	include "Jona/vendor/GLFW"
	include "Jona/vendor/Glad"
	include "Jona/vendor/imgui"

group ""

project "Jona"
	location "Jona"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jnpch.h"
	pchsource "Jona/src/jnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JN_PLATFORM_WINDOWS",
			"JN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JN_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Jona/vendor/spdlog/include",
		"Jona/src",
		"Jona/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Jona"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JN_DIST"
		runtime "Release"
		optimize "on"
