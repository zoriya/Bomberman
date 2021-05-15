#Definition of CMake version to use
cmake_minimum_required(VERSION 3.17)

set(BIN_NAME "libray.a")

project("${BIN_NAME}")
include_directories("./include")

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_STANDARD 11)
    set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow -lray")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()

set(HEADERS
    include/Color.hpp
    include/Controllers
    include/Drawables
    include/Vector.hpp
    include/Window.hpp
    include/Controllers/Gamepad.hpp
    include/Controllers/Keyboard.hpp
    include/Controllers/Mouse.hpp
    include/Drawables/ADrawable.hpp
    include/Drawables/Basic/Circle.hpp
    include/Drawables/Basic/Line.hpp
    include/Drawables/Basic/Point.hpp
)

set(SRC

)

add_library(${BIN_NAME} STATIC ${SRC} ${HEADERS})
