cmake_minimum_required(VERSION 3.15)

project(EZ_WINDOW
VERSION 0.2.0
LANGUAGES C CXX
)

option(BUILD_TESTS "Build the tests for the ez-window library" ON)

include(GNUInstallDirs)
find_package(ez-cmake CONFIG REQUIRED)

find_package(ez-input CONFIG REQUIRED)
find_package(ez-glcompat CONFIG REQUIRED)

find_package(SDL2 CONFIG REQUIRED)

add_library(ez-window STATIC 
	"src/Engine.cpp"
	"src/Style.cpp"
	"src/RenderSettings.cpp"
	"src/Window.cpp"
	"src/Core.cpp"
	"src/Cursor.cpp"
	#"$<$<PLATFORM_ID:Windows>:src/intern/msw.cpp>"
	#"$<$<PLATFORM_ID:Linux>:src/intern/x11.cpp>"
	#"$<$<PLATFORM_ID:iOS>:src/intern/ios.cpp>"
	#"$<$<PLATFORM_ID:Android>:src/intern/android.cpp>"
	#"$<$<PLATFORM_ID:Darwin>:src/intern/darwin.cpp>"
)
target_link_libraries(ez-window PUBLIC ez-input ez-glcompat SDL2::SDL2 SDL2::SDL2main)

target_include_directories(ez-window PUBLIC 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:include>"
)
target_compile_features(ez-window PUBLIC cxx_std_17)

if(${BUILD_TESTS})
	add_subdirectory("tests")
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/ez-window)

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
    RUNTIME DESTINATION "bin/$<CONFIG>")

install_package(
	NAME "ez-window"
	EXPORT "ez-window-targets"
	VERSION "${EZ_WINDOW_VERSION}"
	COMPATIBILITY "SameMajorVersion"
	DESTINATION DEFAULT
	PRECONFIG "preconfig.cmake"
)