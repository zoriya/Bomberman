cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)

include_directories(bomberman lib/Ray/sources)
include_directories(bomberman lib/wal/sources)
include_directories(bomberman sources)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/wal)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Ray)

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
	sources/Component/Collision/CollisionComponent.cpp
	sources/Component/Collision/CollisionComponent.hpp
	sources/System/Collision/CollisionSystem.hpp
	sources/System/Collision/CollisionSystem.cpp
	sources/Component/Button/ButtonComponent.cpp
	sources/Component/Button/ButtonComponent.hpp
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
	tests/CollisionTest.cpp
	tests/MoveTests.cpp
)
target_include_directories(unit_tests PUBLIC sources)
target_link_libraries(unit_tests PUBLIC wal ray)

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/catch2)
	find_package(Catch2 REQUIRED)
endif()
target_link_libraries(unit_tests PRIVATE Catch2::Catch2)
