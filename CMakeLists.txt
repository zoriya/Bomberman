CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
project(Bomberman)
set(CMAKE_CXX_STANDARD 20)

add_executable(bomberman
		sources/main.cpp
)

target_link_libraries(bomberman raylib)