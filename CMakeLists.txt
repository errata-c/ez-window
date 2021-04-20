cmake_minimum_required(VERSION 3.15)

project(EZ_WINDOW
VERSION 0.2.1
LANGUAGES C CXX
)

include(GNUInstallDirs)
include("cmake/ez-cmake/install-package.cmake")

option(BUILD_TESTS "Build the test executables" ON)
option(SEPARATE_DIRECTORY "Install the package into its own directory" ON)
set(CONFIG_DIR "${CMAKE_INSTALL_DATAROOTDIR}/ez-window" CACHE STRING "The relative directory to install package config files.")



find_package(ez-bitflags CONFIG REQUIRED)
find_package(ez-input CONFIG REQUIRED)
find_package(rt-loader CONFIG REQUIRED)

find_package(SDL2 CONFIG REQUIRED)

add_library(ez-window STATIC 
	"src/Engine.cpp"
	"src/RenderSettings.cpp"
	"src/Window.cpp"
	"src/Core.cpp"
	"src/Cursor.cpp"
	"src/Display.cpp"
	
	# Maybe I'll make some platform specific stuff later.
	#"$<$<PLATFORM_ID:Windows>:src/intern/msw.cpp>"
	#"$<$<PLATFORM_ID:Linux>:src/intern/x11.cpp>"
	#"$<$<PLATFORM_ID:iOS>:src/intern/ios.cpp>"
	#"$<$<PLATFORM_ID:Android>:src/intern/android.cpp>"
	#"$<$<PLATFORM_ID:Darwin>:src/intern/darwin.cpp>"
)
target_link_libraries(ez-window 
	PUBLIC 
		ez::bitflags 
		ez::input 
		rt::loader 
	PRIVATE 
		SDL2::SDL2
)
target_include_directories(ez-window PUBLIC 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:include>"
)
target_compile_features(ez-window PUBLIC cxx_std_17)
set_target_properties(ez-window PROPERTIES 
	WIN32_EXECUTABLE "$<IF:$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Windows>>,TRUE,FALSE>"
	EXPORT_NAME "window"
)



if(BUILD_TESTS)
	add_subdirectory("tests")
endif()

if(SEPARATE_DIRECTORY)
	set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/ez-window)
endif()



install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	TYPE INCLUDE
	FILES_MATCHING
	PATTERN "*.h" PATTERN "*.hpp"
)

install(TARGETS "ez-window"
    EXPORT "ez-window-targets"
    PUBLIC_HEADER DESTINATION "include"
    ARCHIVE DESTINATION "lib/$<CONFIG>"
    LIBRARY DESTINATION "lib/$<CONFIG>"
    RUNTIME DESTINATION "bin/$<CONFIG>"
)

install_package(
	NAME "ez-window"
	NAMESPACE "ez::"
	EXPORT "ez-window-targets"
	VERSION "${EZ_WINDOW_VERSION}"
	COMPATIBILITY "SameMajorVersion"
	DESTINATION "${CONFIG_DIR}"
	PRECONFIG "cmake/preconfig.cmake"
)