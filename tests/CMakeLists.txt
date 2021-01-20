project(EZ_WINDOW_TESTS
VERSION 0.1.1
LANGUAGES C CXX)

if(NOT TARGET "ez-window")
	find_package(ez-window CONFIG REQUIRED)
endif()

add_subdirectory("basic_test")