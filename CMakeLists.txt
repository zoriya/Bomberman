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
	sources/Items/Bonus.cpp
	sources/Items/Bonus.hpp
	sources/Component/Position/PositionComponent.cpp
	sources/Component/Position/PositionComponent.hpp
	sources/Component/Movable/MovableComponent.cpp
	sources/Component/Movable/MovableComponent.hpp
	sources/Component/Controllable/ControllableComponent.hpp
	sources/Component/Controllable/ControllableComponent.cpp
	sources/Component/BombHolder/BombHolderComponent.cpp
	sources/Component/BombHolder/BombHolderComponent.hpp
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
	sources/System/BombHolder/BombHolderSystem.cpp
	sources/System/BombHolder/BombHolderSystem.hpp
	sources/Component/Timer/TimerComponent.cpp
	sources/Component/Timer/TimerComponent.hpp
	sources/System/Timer/TimerSystem.cpp
	sources/System/Timer/TimerSystem.hpp
	sources/System/Event/EventSystem.cpp
	sources/System/Event/EventSystem.hpp
	sources/Component/Animation/AnimationsComponent.cpp
	sources/Component/Animation/AnimationsComponent.hpp
	sources/System/Animation/AnimationsSystem.cpp
	sources/System/Animation/AnimationsSystem.hpp
	sources/Component/Collision/CollisionComponent.cpp
	sources/Component/Collision/CollisionComponent.hpp
	sources/System/Collision/CollisionSystem.hpp
	sources/System/Collision/CollisionSystem.cpp
	sources/Component/Button/ButtonComponent.hpp
	sources/System/MenuControllable/MenuControllableSystem.cpp
	sources/System/MenuControllable/MenuControllableSystem.hpp
	sources/System/Levitate/LevitateSystem.hpp
	sources/System/Levitate/LevitateSystem.cpp
	sources/Component/Levitate/LevitateComponent.cpp
	sources/Component/Levitate/LevitateComponent.cpp
	sources/Component/Animator/AnimatorComponent.cpp
	sources/Component/Animator/AnimatorComponent.hpp
	sources/System/Animator/AnimatorSystem.cpp
	sources/System/Animator/AnimatorSystem.hpp
	sources/Component/Shaders/ShaderComponent.cpp
	sources/Component/Shaders/ShaderComponent.hpp
	sources/Component/Bomb/BasicBombComponent.cpp
	sources/Component/Bomb/BasicBombComponent.hpp
	sources/Component/Bonus/PlayerBonusComponent.hpp
	sources/Component/Bonus/PlayerBonusComponent.cpp
	sources/System/Bonus/PlayerBonusSystem.hpp
	sources/System/Bonus/PlayerBonusSystem.cpp
	sources/Component/Tag/TagComponent.hpp
	sources/Component/Music/MusicComponent.cpp
	sources/Component/Music/MusicComponent.hpp
	sources/Component/Sound/SoundComponent.hpp
	sources/Component/Sound/SoundComponent.cpp
	sources/System/Sound/MenuSoundManagerSystem.cpp
	sources/System/Sound/MenuSoundManagerSystem.hpp
	sources/System/Sound/PlayerSoundManagerSystem.cpp
	sources/System/Sound/PlayerSoundManagerSystem.hpp
	sources/System/Music/MusicSystem.hpp
	sources/System/Music/MusicSystem.cpp
	sources/Component/Gravity/GravityComponent.hpp
	sources/Component/Gravity/GravityComponent.cpp
	sources/System/Gravity/GravitySystem.hpp
	sources/System/Gravity/GravitySystem.cpp
	sources/Component/BumperTimer/BumperTimerComponent.hpp
	sources/Component/BumperTimer/BumperTimerComponent.cpp
	sources/System/BumperTimer/BumperTimerSystem.hpp
	sources/System/BumperTimer/BumperTimerSystem.cpp
	sources/System/Bomb/BombSystem.cpp
	sources/System/Bomb/BombSystem.hpp
	sources/Component/IntroAnimation/IntroAnimationComponent.hpp
	sources/Component/IntroAnimation/IntroAnimationComponent.cpp
	sources/System/IntroAnimation/IntroAnimationSystem.hpp
	sources/System/IntroAnimation/IntroAnimationSystem.cpp
	sources/Runner/SplashScreenScene.cpp
	sources/Runner/TitleScreenScene.cpp
	sources/Runner/MainMenuScene.cpp
	sources/Runner/GameScene.cpp
	sources/Runner/PauseMenuScene.cpp
	sources/Runner/SettingsMenuScene.cpp
	sources/Runner/CreditScene.cpp
	sources/Component/Score/ScoreComponent.cpp
	sources/Component/Score/ScoreComponent.hpp
)
add_executable(bomberman
               sources/main.cpp
               ${SOURCES}
)
target_include_directories(bomberman PUBLIC sources)
target_link_libraries(bomberman PUBLIC wal ray)


add_executable(unit_tests EXCLUDE_FROM_ALL
               ${SOURCES}
			   tests/CacheTest.cpp
               tests/EntityTests.cpp
               tests/MainTest.cpp
               tests/EngineTests.cpp
               tests/CallbackTest.cpp
               tests/MoveTests.cpp
               tests/ViewTest.cpp
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
