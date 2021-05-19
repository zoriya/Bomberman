#Definition of CMake version to use
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(LIB_NAME "ray")

project("${LIB_NAME}")
include_directories("./include")
target_link_libraries(${LIB_NAME} raylib)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif ()

set(HEADERS
    include/Canvas.hpp
    include/Color.hpp
    include/Font.hpp
    include/IRessource.hpp
    include/Matrix.hpp
    include/Mesh.hpp
    include/Model.hpp
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
    include/Drawables/IDrawable.hpp
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
    include/Drawables/3D/Grid.hpp
    include/Drawables/3D/Line.hpp
    include/Drawables/3D/Plane.hpp
    include/Drawables/3D/Point.hpp
    include/Drawables/3D/Ray.hpp
    include/Drawables/3D/Sphere.hpp
    include/Drawables/3D/Triangle.hpp
    )

set(SRC
    src/Color.cpp
    src/Font.cpp
    src/Model.cpp
    src/Window.cpp
    src/Audio/Music.cpp
    src/Audio/Sound.cpp
    src/Camera/Camera2D.cpp
    src/Camera/Camera3D.cpp
    src/Controllers/Gamepad.cpp
    src/Controllers/Keyboard.cpp
    src/Controllers/Mouse.cpp
    )

add_library(${LIB_NAME} STATIC ${SRC} ${HEADERS})
