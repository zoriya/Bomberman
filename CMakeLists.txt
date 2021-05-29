cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)

include_directories(bomberman lib/Ray/sources)
include_directories(bomberman lib/wal/sources)
include_directories(bomberman sources)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Ray)

if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

set(SOURCES
	sources/Models/GameState.hpp
	sources/Runner/Runner.cpp
	sources/Runner/Runner.hpp
	sources/Component/Position/PositionComponent.cpp
	sources/Component/Position/PositionComponent.hpp
	sources/Component/Movable/MovableComponent.cpp
	sources/Component/Movable/MovableComponent.hpp
	sources/System/Movable/MovableSystem.hpp
	sources/System/Movable/MovableSystem.cpp
	sources/Models/Vector3.hpp
	sources/Models/Vector2.hpp
	sources/Component/Renderer/Drawable3DComponent.hpp
	sources/Component/Renderer/Drawable2DComponent.hpp
	sources/System/Renderer/Renderer3DSystem.hpp
	sources/System/Renderer/Renderer2DSystem.hpp
	sources/System/Renderer/RenderScreenSystem.hpp
	sources/System/Renderer/RenderScreenSystem.cpp
	sources/Component/Renderer/CameraComponent.cpp
	sources/Component/Renderer/CameraComponent.hpp
	sources/System/Renderer/Render2DScreenSystem.cpp
	sources/System/Renderer/Render2DScreenSystem.hpp
)

add_executable(bomberman
               sources/main.cpp
               ${SOURCES})
target_include_directories(bomberman PUBLIC sources)
target_link_libraries(bomberman PUBLIC wal ray)


add_executable(unit_tests EXCLUDE_FROM_ALL
	${SOURCES}
	tests/EntityTests.cpp
	tests/MainTest.cpp
	tests/EngineTests.cpp
	tests/CallbackTest.cpp
)
target_include_directories(unit_tests PUBLIC sources)
target_link_libraries(unit_tests PUBLIC wal ray)

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/catch2)
	find_package(Catch2 REQUIRED)
endif()
target_link_libraries(unit_tests PRIVATE Catch2::Catch2)
