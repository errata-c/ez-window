
find_package(rt-loader CONFIG REQUIRED COMPONENTS glew)

find_package(fmt CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(basic_test "main.cpp")
target_link_libraries(basic_test PRIVATE ez-window SDL2::SDL2 SDL2::SDL2main rt::loader-glew fmt::fmt)

file(GENERATE OUTPUT "genex.txt" INPUT "genex.txt")