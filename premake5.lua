workspace "Elastic"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Elastic"
	location "Elastic"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
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
		"Elastic/vendor/spdlog/include",
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
	
	filter "configurations:Debug"
		defines "EL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EL_DIST"
		optimize "On"