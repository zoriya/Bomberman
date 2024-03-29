cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
project(LuaGate)

include_directories(sources)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif ()

set(HEADERS
	sources/LuaGate.hpp
)

set(SRC
	sources/LuaGate.cpp
)

include(FindLua)
if (NOT LUA_FOUND)
	if (EXISTS ${CMAKE_SOURCE_DIR}/include/lua.hpp)
		message("Using local lua")
		set(LUA_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
		set(LUA_LIBRARIES ${CMAKE_SOURCE_DIR}/lua54.lib)
	else()
		message(FATAL_ERROR "Lua could not be found.")
	endif()
endif()

add_library(LuaGate STATIC ${SRC} ${HEADERS})
target_include_directories(LuaGate PUBLIC ${LUA_INCLUDE_DIR})
target_link_libraries(LuaGate ${LUA_LIBRARIES})
