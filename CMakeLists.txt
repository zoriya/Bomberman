CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
project(Bomberman)

FIND_PACKAGE(raylib REQUIRED)
TARGET_LINK_LIBRARIES(target_name raylib)

if (NOT raylib_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/master.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        SET(raylib_FOUND TRUE)
    endif()
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(bomberman
		sources/main.cpp
)
