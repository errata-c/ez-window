# Much of this code comes from wxWidgets, as it has good cross platform support.

if(CMAKE_OSX_SYSROOT MATCHES iphoneos)
    set(IPHONE ON)

    # workaround a bug where try_compile (and functions using it,
    # like find_package, check_c_source_compiles) fails
    #set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
# Linux app
# clipboard, cursors
find_package(X11 REQUIRED)
# Creates variables:
# X11_FOUND  X11_INCLUDE_DIR  X11_LIBRARIES    

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
# Windows app
# clipboard, cursors

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin") # Mac
# Mac OSX app
# clipboard, cursors

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS")
# ios app
# clipboard, no cursor

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "tvOS")
# Apple tv app

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "watchOS")
# Apple watch app

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Android")
# Android app
# clipboard, no cursor

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore" AND "${CMAKE_SYSTEM_VERSION}" STREQUAL "10.0")
# Windows 10 universal app

endif()