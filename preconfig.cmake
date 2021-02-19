
if(NOT TARGET ez::input)
	find_dependency(ez-input CONFIG)
endif()

if(NOT TARGET ez::glcompat)
	find_dependency(ez-glcompat CONFIG)
endif()

if(NOT TARGET SDL2::SDL2)
	find_dependency(SDL2 CONFIG)
endif()


