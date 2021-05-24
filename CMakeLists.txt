cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)

include_directories(bomberman lib/Ray/sources)
include_directories(bomberman lib/wal/sources)
include_directories(bomberman sources)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Ray)

add_executable(bomberman
               sources/main.cpp
               sources/Component/Drawable/RectangleDrawable2DComponent.cpp
               sources/Component/Drawable/RectangleDrawable2DComponent.hpp
               sources/Component/Drawable/Drawable2DComponent.hpp
               sources/Component/Drawable/Drawable2DComponent.cpp
               sources/Component/Movable/MovableComponent.cpp
               sources/Component/Movable/MovableComponent.hpp
               sources/Component/Position/PositionComponent.cpp
               sources/Component/Position/PositionComponent.hpp
               sources/System/Movable/MovableSystem.cpp
               sources/System/Movable/MovableSystem.hpp
               sources/System/Renderer/RendererSystem.cpp
               sources/System/Renderer/RendererSystem.hpp
               )

target_link_libraries(bomberman wal ray)