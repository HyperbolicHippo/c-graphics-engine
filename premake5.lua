workspace "GameEngine"
	configurations {"Debug", "Release"}

project "Engine"
	kind "ConsoleApp"
	language "C"
	cdialect "C17"

	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"

	files {"**.c", "**.h"}

	includedirs {"libs/glfw/include/", "libs/glew/include/"}
	libdirs {"libs/glfw/", "libs/glew/"}

	links {"glfw3", "X11", "GLEW", "GL", "m"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"
