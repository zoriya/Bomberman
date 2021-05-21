cmake_minimum_required(VERSION 3.19)
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
	sources/Component/Position/PositionComponent.cpp
	sources/Component/Position/PositionComponent.hpp
	sources/Models/Vector3.hpp
	sources/Component/Movable/MovableComponent.cpp
	sources/Component/Movable/MovableComponent.hpp
	sources/System/Movable/MovableSystem.cpp
	sources/System/Movable/MovableSystem.hpp
	sources/System/System.cpp
	sources/Models/Callback.hpp
)

target_include_directories(wal PUBLIC sources)

add_executable(wal_tests EXCLUDE_FROM_ALL
	tests/EntityTests.cpp
	tests/MainTest.cpp
	tests/EngineTests.cpp
)

target_link_libraries(wal_tests PRIVATE wal)

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../catch2)
	find_package(Catch2 REQUIRED)
endif()

target_link_libraries(wal_tests PRIVATE Catch2::Catch2)
