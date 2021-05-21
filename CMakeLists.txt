cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)

include_directories(bomberman lib/Ray/sources)
include_directories(bomberman lib/wal/sources)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/raylib)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Ray)

add_executable(bomberman
	sources/main.cpp
)

target_link_libraries(bomberman wal ray)
