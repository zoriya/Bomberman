cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)

add_executable(bomberman
	sources/main.cpp
	sources/Models/GameState.hpp
	sources/Runner/Runner.cpp
	sources/Runner/Runner.hpp
)
target_include_directories(bomberman PUBLIC sources)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/raylib)
	find_package(raylib REQUIRED)
endif()
target_link_libraries(bomberman wal raylib)
