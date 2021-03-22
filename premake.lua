workspace "Hazel"
	architecture "x64"

	configuratioins{
		"Debug",
		"Release",
		"Dist"
	}

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" //Debug windows x64

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	files{

	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp"


	}

	include
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filters "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
				"HZ_PLATFORM_WINDOWS",
				"HZ_BUILD_DLL"
		}
		
