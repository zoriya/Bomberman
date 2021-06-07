cmake_minimum_required(VERSION 3.11)
project(wal)

set(CMAKE_CXX_STANDARD 20)

add_library(wal
	sources/Entity/Entity.hpp
	sources/Component/Component.hpp
	sources/System/System.hpp
	sources/Wal.cpp
	sources/Wal.hpp
	sources/Scene/Scene.cpp
	sources/Scene/Scene.hpp
	sources/Exception/WalError.cpp
	sources/Exception/WalError.hpp
	sources/Entity/Entity.cpp
	sources/Component/Component.cpp
	sources/System/System.cpp
	sources/Models/Callback.hpp
	sources/Models/TypeHolder.hpp)

target_include_directories(wal PUBLIC sources)