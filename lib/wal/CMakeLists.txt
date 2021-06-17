cmake_minimum_required(VERSION 3.11)
project(wal)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wshadow -W -Werror -Wno-unused-parameter -g")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(wal
	sources/Entity/Entity.hpp
	sources/Component/Component.hpp
	sources/System/System.hpp
	sources/Wal.hpp
	sources/Scene/Scene.cpp
	sources/Scene/Scene.hpp
	sources/Exception/WalError.cpp
	sources/Exception/WalError.hpp
	sources/Entity/Entity.cpp
	sources/Component/Component.cpp
	sources/Models/Callback.hpp
	sources/View/View.hpp
	sources/System/ISystem.hpp
	sources/Models/TypeHolder.hpp
)

target_include_directories(wal PUBLIC sources)