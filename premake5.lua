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

group "Dependencies"
	include "Jona/vendor/GLFW"
	include "Jona/vendor/Glad"
	include "Jona/vendor/imgui"

group ""

project "Jona"
	location "Jona"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jnpch.h"
	pchsource "Jona/src/jnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"JN_PLATFORM_WINDOWS",
			"JN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JN_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Jona"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"JN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JN_DIST"
		runtime "Release"
		optimize "On"