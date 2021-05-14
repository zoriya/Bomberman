cmake_minimum_required(VERSION 3.19)
project(wal)

set(CMAKE_CXX_STANDARD 20)

add_library(wal
		Entity/Entity.hpp
		Component/Component.hpp
		System/System.hpp
		Wal.cpp
		Wal.hpp
)