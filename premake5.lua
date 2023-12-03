workspace "Elastic"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "Elastic/vendor/spdlog/include"
IncludeDir["GLFW"] = "Elastic/vendor/GLFW/include"
IncludeDir["ImGui"] = "Elastic/vendor/imgui"
IncludeDir["Glad"] = "Elastic/vendor/Glad/include"

include "Elastic/vendor/GLFW"
include "Elastic/vendor/Glad"
include "Elastic/vendor/imgui"

project "Elastic"
	location "Elastic"
	kind "SharedLib"
	language "C++"

	buildoptions { "-g" }

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"GL"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}
	
	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EL_DIST"
		optimize "On"

	pchheader "elpch.h"
	pchsource "src/elpch.cpp"


	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{wks.location}/Elastic/vendor",
		"Elastic/src"
	}

	links
	{
		"Elastic"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EL_DIST"
		optimize "On"