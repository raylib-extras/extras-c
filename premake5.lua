workspace "extras"
	configurations { "Debug","Debug.DLL", "Release", "Release.DLL" }
	platforms { "x64"}
	defaultplatform "x64"
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Debug.DLL"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter "configurations:Release.DLL"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
		
	targetdir "bin/%{cfg.buildcfg}/"
		
project "raylib"
	filter "configurations:Debug.DLL OR Release.DLL"
		kind "SharedLib"
		defines {"BUILD_LIBTYPE_SHARED"}
		
	filter "configurations:Debug OR Release"
		kind "StaticLib"
		
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		links {"winmm"}
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
				
	filter{}
	
	location "build"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	includedirs { "raylib/src", "raylib/src/external/glfw/include"}
	vpaths 
	{
		["Header Files"] = { "raylib/src/**.h"},
		["Source Files/*"] = {"raylib/src/**.c"},
	}
	files {"raylib/src/*.h", "raylib/src/*.c"}
	
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}

project "rlFPCamera"
	kind "StaticLib"
	
	location "build"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	includedirs { "raylib/src"}
	vpaths 
	{
		["Header Files"] = { "cameras/rlFPCamera/*.h"},
		["Source Files"] = {"cameras/rlFPCamera/*.c"},
	}
	files {"cameras/rlFPCamera/*.c","cameras/rlFPCamera/*.h"}

project "rlTPCamera"
	kind "StaticLib"
	
	location "build"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	includedirs { "raylib/src"}
	vpaths 
	{
		["Header Files"] = { "cameras/rlTPCamera/*.h"},
		["Source Files"] = {"cameras/rlTPCamera/*.c"},
	}
	files {"cameras/rlTPCamera/*.c","cameras/rlTPCamera/*.h"}
	
project "path_utils"
	kind "StaticLib"
	
	location "build"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	vpaths 
	{
		["Header Files"] = { "path_utils/*.h"},
		["Source Files"] = {"path_utils/*.c"},
	}
	files {"path_utils/*.c","path_utils/*.h"}

group "Examples"
project "rlFPCamera_sample"
	kind "ConsoleApp"
	location "cameras/rlFPCamera/samples"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	vpaths 
	{
		["Header Files"] = { "cameras/rlFPCamera/samples/*.h"},
		["Source Files"] = {"cameras/rlFPCamera/samples/*.c" },
	}
	files {"cameras/rlFPCamera/samples/*.c"}

	links {"raylib", "rlFPCamera"}
	
	includedirs {"raylib/src", "cameras/rlFPCamera" }
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		links {"winmm"}
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
				
	filter{}
	
project "rlTPCamera_sample"
	kind "ConsoleApp"
	location "cameras/rlTPCamera/samples"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	vpaths 
	{
		["Header Files"] = { "cameras/rlTPCamera/samples/*.h"},
		["Source Files"] = {"cameras/rlTPCamera/samples/*.c" },
	}
	files {"cameras/rlTPCamera/samples/*.c"}

	links {"raylib", "rlTPCamera"}
	
	includedirs {"raylib/src", "cameras/rlTPCamera" }
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		links {"winmm"}
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
				
	filter{}
	
project "application_dir_sample"
	kind "ConsoleApp"
	location "path_utils/samples"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	vpaths 
	{
		["Header Files"] = { "path_utils/samples/application_dir/*.h"},
		["Source Files"] = {"path_utils/samples/application_dir/*.c" },
	}
	files {"path_utils/samples/application_dir/*.c"}

	links {"raylib", "path_utils"}
	
	includedirs {"raylib/src", "path_utils" }
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		links {"winmm"}
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
				
	filter{}
