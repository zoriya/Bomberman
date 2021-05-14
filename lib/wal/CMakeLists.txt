cmake_minimum_required(VERSION 3.19)
project(wal)

set(CMAKE_CXX_STANDARD 20)

add_library(wal
	sources/Entity/Entity.hpp
	sources/Component/Component.hpp
	sources/System/System.hpp
	sources/Wal.cpp
	sources/Wal.hpp
	sources/Scene/SceneManager.cpp
	sources/Scene/SceneManager.hpp
	sources/Scene/Scene.cpp
	sources/Scene/Scene.hpp
	sources/Renderer/Renderer.cpp
	sources/Renderer/Renderer.hpp
	sources/Events/EventManager.cpp
	sources/Events/EventManager.hpp
	sources/Exception/WalError.cpp
	sources/Exception/WalError.hpp
)

target_include_directories(wal PUBLIC sources)