project(EZ_WINDOW_TESTS
VERSION 0.1.1
LANGUAGES C CXX)

if(NOT TARGET "ez-window")
	find_package(ez-window CONFIG REQUIRED)
endif()

find_package(SFML CONFIG REQUIRED COMPONENTS main system window)
find_package(SDL2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)

add_library(test_interface INTERFACE)
target_link_libraries(test_interface INTERFACE ez-window fmt::fmt GLEW::GLEW)

add_executable(SFML_test "SFML_test/main.cpp")
target_link_libraries(SFML_test PRIVATE test_interface sfml-main sfml-system sfml-window)

add_executable(SDL2_test "SDL2_test/main.cpp")
target_link_libraries(SDL2_test PRIVATE test_interface SDL2::SDL2)