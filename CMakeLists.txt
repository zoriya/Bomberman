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
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_DISABLE_EXCEPTION_CATCHING --shell-file ../sources/wasm/frontend.html --preload-file ../assets")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

set(SOURCES
	sources/Models/GameState.hpp
	sources/Runner/Runner.cpp
	sources/Runner/Runner.hpp
	sources/Map/Map.cpp
	sources/Map/Map.hpp
	sources/Component/Position/PositionComponent.cpp
	sources/Component/Position/PositionComponent.hpp
	sources/Component/Movable/MovableComponent.cpp
	sources/Component/Movable/MovableComponent.hpp
	sources/Component/Controllable/ControllableComponent.hpp
	sources/Component/Controllable/ControllableComponent.cpp
	sources/Component/Gamepad/GamepadComponent.cpp
	sources/Component/Gamepad/GamepadComponent.hpp
	sources/Component/Keyboard/KeyboardComponent.cpp
	sources/Component/Keyboard/KeyboardComponent.hpp
	sources/Component/Health/HealthComponent.cpp
	sources/Component/Health/HealthComponent.hpp
	sources/System/Movable/MovableSystem.hpp
	sources/System/Movable/MovableSystem.cpp
	sources/System/Controllable/ControllableSystem.cpp
	sources/System/Controllable/ControllableSystem.hpp
	sources/System/Gamepad/GamepadSystem.cpp
	sources/System/Gamepad/GamepadSystem.hpp
	sources/System/Health/HealthSystem.cpp
	sources/System/Health/HealthSystem.hpp
	sources/System/Keyboard/KeyboardSystem.cpp
	sources/System/Keyboard/KeyboardSystem.hpp
	sources/System/Movable/MovableSystem.cpp
	sources/System/Movable/MovableSystem.hpp
	sources/Models/Vector3.hpp
	sources/Component/GridCentered/GridCenteredComponent.cpp
	sources/Component/GridCentered/GridCenteredComponent.hpp
	sources/System/GridCentered/GridCenteredSystem.cpp
	sources/System/GridCentered/GridCenteredSystem.hpp
	sources/Models/Vector2.hpp
	sources/Component/Renderer/Drawable2DComponent.hpp
	sources/Component/Renderer/Drawable3DComponent.hpp
	sources/System/Renderer/RenderSystem.hpp
	sources/System/Renderer/RenderSystem.cpp
	sources/Component/Renderer/CameraComponent.cpp
	sources/Component/Renderer/CameraComponent.hpp
	sources/Component/Animation/AnimationsComponent.cpp
	sources/Component/Animation/AnimationsComponent.hpp
	sources/System/Animation/AnimationsSystem.cpp
	sources/System/Animation/AnimationsSystem.hpp
	sources/Component/Collision/CollisionComponent.cpp
	sources/Component/Collision/CollisionComponent.hpp
	sources/System/Collision/CollisionSystem.hpp
	sources/System/Collision/CollisionSystem.cpp
)
add_executable(bomberman
               sources/main.cpp
               ${SOURCES}
               )
target_include_directories(bomberman PUBLIC sources)
target_link_libraries(bomberman PUBLIC wal ray)


add_executable(unit_tests EXCLUDE_FROM_ALL
	${SOURCES}
	tests/EntityTests.cpp
	tests/MainTest.cpp
	tests/EngineTests.cpp
	tests/CallbackTest.cpp
	tests/MoveTests.cpp
	tests/CollisionTest.cpp
   )
target_include_directories(unit_tests PUBLIC sources)
target_link_libraries(unit_tests PUBLIC wal ray)

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/catch2)
	find_package(Catch2 REQUIRED)
endif()
target_link_libraries(unit_tests PRIVATE Catch2::Catch2)
