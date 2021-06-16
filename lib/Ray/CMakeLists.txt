#Definition of CMake version to use
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(LIB_NAME "ray")

project("${LIB_NAME}")
include_directories(${LIB_NAME} ./sources)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif ()

set(HEADERS
    sources/Color.hpp
    sources/Font.hpp
    sources/Matrix.hpp
    sources/Mesh.hpp
    sources/TraceLog.hpp
    sources/Window.hpp
    sources/Audio/IAudio.hpp
    sources/Audio/Music.hpp
    sources/Audio/Sound.hpp
    sources/Camera/Camera2D.hpp
    sources/Camera/Camera3D.hpp
    sources/Camera/CameraMode.hpp
    sources/Camera/CameraProjection.hpp
    sources/Camera/ICamera.hpp
    sources/Controllers/Gamepad.hpp
    sources/Controllers/Keyboard.hpp
    sources/Controllers/Mouse.hpp
    sources/Drawables/ADrawable2D.hpp
    sources/Drawables/ADrawable3D.hpp
    sources/Drawables/IDrawable.hpp
    sources/Drawables/Image.hpp
    sources/Drawables/Texture.hpp
    sources/Drawables/2D/Circle.hpp
    sources/Drawables/2D/Line.hpp
    sources/Drawables/2D/Point.hpp
    sources/Drawables/2D/Rectangle.hpp
    sources/Drawables/2D/Text.hpp
    sources/Drawables/2D/Triangle.hpp
    sources/Drawables/3D/Circle.hpp
    sources/Drawables/3D/Cube.hpp
    sources/Drawables/3D/Cylinder.hpp
    sources/Drawables/3D/Grid.hpp
    sources/Drawables/3D/Line.hpp
    sources/Drawables/3D/Plane.hpp
    sources/Drawables/3D/Point.hpp
    sources/Drawables/3D/Ray.hpp
    sources/Drawables/3D/Sphere.hpp
    sources/Drawables/3D/Triangle.hpp
    sources/Exceptions/RayError.hpp
    sources/Model/Model.hpp
    sources/Model/ModelAnimation.hpp
    sources/Model/ModelAnimations.hpp
    sources/Vector/Vector2.hpp
    sources/Vector/Vector3.hpp
    sources/Utils/Cache.hpp
	sources/Meshes/AMesh.hpp
	sources/Meshes/MeshSphere.hpp
	sources/Shaders/Shaders.hpp
)

set(SRC
    sources/Color.cpp
    sources/Font.cpp
    sources/TraceLog.cpp
    sources/Window.cpp
    sources/Audio/Music.cpp
    sources/Audio/Sound.cpp
    sources/Camera/Camera2D.cpp
    sources/Camera/Camera3D.cpp
    sources/Controllers/Gamepad.cpp
    sources/Controllers/Keyboard.cpp
    sources/Controllers/Mouse.cpp
    sources/Drawables/2D/Circle.cpp
    sources/Drawables/2D/Line.cpp
    sources/Drawables/2D/Point.cpp
    sources/Drawables/2D/Rectangle.cpp
    sources/Drawables/2D/Text.cpp
    sources/Drawables/2D/Triangle.cpp
    sources/Drawables/3D/Circle.cpp
    sources/Drawables/3D/Cube.cpp
    sources/Drawables/3D/Cylinder.cpp
    sources/Drawables/3D/Grid.cpp
    sources/Drawables/3D/Line.cpp
    sources/Drawables/3D/Plane.cpp
    sources/Drawables/3D/Point.cpp
    sources/Drawables/3D/Ray.cpp
    sources/Drawables/3D/Sphere.cpp
    sources/Drawables/3D/Triangle.cpp
    sources/Drawables/ADrawable2D.cpp
    sources/Drawables/ADrawable3D.cpp
    sources/Drawables/Image.cpp
    sources/Drawables/Texture.cpp
    sources/Exceptions/RayError.cpp
    sources/Model/Model.cpp
    sources/Model/ModelAnimation.cpp
    sources/Model/ModelAnimations.cpp
    sources/Vector/Vector2.cpp
    sources/Vector/Vector3.cpp
    sources/Shaders/Shaders.cpp
	sources/Meshes/MeshSphere.cpp
	sources/Meshes/AMesh.cpp
	)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../raylib)
	find_package(raylib REQUIRED)
endif()

add_library(${LIB_NAME} STATIC ${SRC} ${HEADERS})
target_compile_definitions(${LIB_NAME} INTERFACE INTERNAL=private PRIVATE INTERNAL=public)
target_link_libraries(${LIB_NAME} raylib)
