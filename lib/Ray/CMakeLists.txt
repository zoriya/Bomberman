#Definition of CMake version to use
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)

set(BIN_NAME "ray")

project("${BIN_NAME}")
include_directories("./include")

FIND_PACKAGE(raylib REQUIRED)
TARGET_LINK_LIBRARIES(target_name raylib)

if (NOT raylib_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/master.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        SET(raylib_FOUND TRUE)
    endif()
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_STANDARD 11)
    set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow -lray")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()


set(HEADERS
    include/Canvas.hpp
    include/Color.hpp
    include/Font.hpp
    include/Matrix.hpp
    include/Vector.hpp
    include/Window.hpp
    include/Audio/IAudio.hpp
    include/Audio/Music.hpp
    include/Audio/Sound.hpp
    include/Camera/Camera2D.hpp
    include/Camera/Camera3D.hpp
    include/Camera/CameraMode.hpp
    include/Camera/CameraProjection.hpp
    include/Camera/ICamera.hpp
    include/Controllers/Gamepad.hpp
    include/Controllers/Keyboard.hpp
    include/Controllers/Mouse.hpp
    include/Drawables/ADrawable2D.hpp
    include/Drawables/ADrawable3D.hpp
    include/Drawables/Image.hpp
    include/Drawables/Texture.hpp
    include/Drawables/2D/Circle.hpp
    include/Drawables/2D/Line.hpp
    include/Drawables/2D/Point.hpp
    include/Drawables/2D/Rectangle.hpp
    include/Drawables/2D/Text.hpp
    include/Drawables/2D/Triangle.hpp
    include/Drawables/3D/Circle.hpp
    include/Drawables/3D/Cylinder.hpp
    include/Drawables/3D/Line.hpp
    include/Drawables/3D/Plane.hpp
    include/Drawables/3D/Point.hpp
    include/Drawables/3D/Ray.hpp
    include/Drawables/3D/Sphere.hpp
    include/Drawables/3D/Triangle.hpp
)

set(SRC

)

add_library(${BIN_NAME} STATIC ${SRC} ${HEADERS})
