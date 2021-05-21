cmake_minimum_required(VERSION 3.11)
project(Bomberman)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/raylib)

add_executable(bomberman
	sources/main.cpp
)

find_package(raylib REQUIRED)
target_link_libraries(bomberman wal raylib)