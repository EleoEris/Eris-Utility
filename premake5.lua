workspace "Eris_Utility"
	architecture "x86_64"
	startproject "Example"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	

outputdir = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}"

project "Eris_Utility"
	kind "StaticLib"
	staticruntime "off"
	language "C++"

	targetdir ("lib/" .. outputdir .. "/%{prj.name}")
	objdir ("lib_int/" .. outputdir .. "/%{prj.name}")

	files {
		"include/%{prj.name}/**.h",
		"src/**.cpp",
		"src/**.tpp"
	}

	includedirs {
		"include"
	}

	disablewarnings {
		-- 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
		"4251" -- project will be specifically compiled for different compilers separately (will solve issue if I'll decide otherwise)
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Dist"
		optimize "On"

project "Example"
	location "Example"
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	links {
		"Eris_Utility"
	}
	
	includedirs {
		"include"
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "On"