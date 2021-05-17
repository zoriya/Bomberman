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
	sources/Entity/Entity.cpp
	sources/Component/Component.cpp
	sources/Component/Basics/PositionComponent.cpp
	sources/Component/Basics/PositionComponent.hpp
	sources/Models/Vector2.hpp
	sources/Models/Vector3.hpp
)

target_include_directories(wal PUBLIC sources)

add_executable(wal_tests
	tests/EntityTests.cpp
	tests/MainTest.cpp)

target_link_libraries(wal_tests PRIVATE wal)
find_package(Catch2 REQUIRED)
target_link_libraries(wal_tests PRIVATE Catch2::Catch2)