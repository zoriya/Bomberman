cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(bomberman
	sources/main.cpp
)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/raylib)
	find_package(raylib REQUIRED)
endif()
target_link_libraries(bomberman wal raylib)
