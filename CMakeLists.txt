cmake_minimum_required(VERSION 3.19)
project(Bomberman)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)

add_executable(bomberman
		sources/main.cpp
)

target_link_libraries(bomberman wal)