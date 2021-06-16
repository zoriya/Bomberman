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
include_directories(${LUA_INCLUDE_DIR})

add_library(LuaGate STATIC ${SRC} ${HEADERS})
target_link_libraries(LuaGate ${LUA_LIBRARIES})
