#Definition of CMake version to use
cmake_minimum_required(VERSION 3.17)

set(BIN_NAME "libray.a")

project("${BIN_NAME}")
include_directories("./include")
set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow -lray")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(HEADERS
    include/Color.hpp
    include/Controllers
    include/Drawables
    include/Vector.hpp
    include/Window.hpp
    include/Controllers/Gamepad.hpp
    include/Controllers/Keyboard.hpp
    include/Controllers/Mouse.hpp
    include/Drawables/Drawable.hpp
    include/Drawables/Basic/Circle.hpp
    include/Drawables/Basic/Line.hpp
    include/Drawables/Basic/Pixel.hpp
)

set(SRC

)

add_library(${BIN_NAME} LIBRARY ${SRC} ${HEADERS})

set_target_properties(${BIN_NAME} PROPERTIES PREFIX "")
set_target_properties(${BIN_NAME} PROPERTIES SUFFIX "")
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME "${BIN_NAME}")
set_target_properties(${BIN_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")include:
