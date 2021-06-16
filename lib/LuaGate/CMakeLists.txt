CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(LIB_NAME "LuaGate")

project("${LIB_NAME}")
include_directories(${LIB_NAME} ./sources)

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

add_library(${LIB_NAME} STATIC ${SRC} ${HEADERS})


include(FindLua)
include_directories(${LIB_NAME} ${LUA_INCLUDE_DIR})
target_link_libraries(${LIB_NAME} ${LUA_LIBRARIES})
