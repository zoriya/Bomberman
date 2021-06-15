#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "Component/Animator/AnimatorComponent.hpp"
#include "Component/Animation/AnimationsComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"
#include "Component/Bonus/PlayerBonusComponent.hpp"
#include "Component/Shaders/ShaderComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Button/ButtonComponent.hpp"
#include "Drawables/2D/Text.hpp"
#include "Component/Gravity/GravityComponent.hpp"
#include "Component/BumperTimer/BumperTimerComponent.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Model/Model.hpp"
#include "Map/Map.hpp"
#include "Component/Score/ScoreComponent.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
    std::shared_ptr<WAL::Scene> Runner::loadGameScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("control")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>();
		std::map<SoundComponent::SoundIndex, std::string> soundPath ={
		    {SoundComponent::JUMP, "assets/sounds/jump.wav"},
		    {SoundComponent::MOVE, "assets/sounds/move.ogg"},
		    {SoundComponent::BOMB, "assets/sounds/bomb_drop.ogg"},
		    //{SoundComponent::DEATH, "assets/sounds/death.ogg"}
		};
		scene->addEntity("Timer")
			.addComponent<TimerComponent>(std::chrono::seconds(60), [](WAL::Entity &, WAL::Wal &) {
				Runner::gameState.nextScene = GameState::ScoreScene;
			});
		scene->addEntity("player")
			.addComponent<PositionComponent>(0, 1.01, 0)
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", true, std::make_pair(MAP_DIFFUSE, "assets/player/blue.png"))
			.addComponent<ControllableComponent>()
			.addComponent<ScoreComponent>()
			.addComponent<AnimatorComponent>()
		    .addComponent<GravityComponent>()
	        .addComponent<BumperTimerComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<ShaderComponentModel>("assets/shaders/glsl330/predator.fs")
			.addComponent<TagComponent<Blowable>>()
			//.addComponent<GamepadComponent>(0)
			.addComponent<AnimationsComponent>(RAY::ModelAnimations("assets/player/player.iqm"), 3)
			.addComponent<CollisionComponent>(BBM::Vector3f{0.25, 0, 0.25}, BBM::Vector3f{.75, 2, .75})
			.addComponent<MovableComponent>()
			.addComponent<SoundComponent>(soundPath)
			.addComponent<MusicComponent>("assets/musics/music_battle.ogg")
			.addComponent<BombHolderComponent>()
			.addComponent<PlayerBonusComponent>()
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity, WAL::Wal &wal) {
				auto &animation = entity.getComponent<AnimationsComponent>();
				animation.setAnimIndex(5);
			});
		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 20, 7)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		MapGenerator::loadMap(16, 16, MapGenerator::createMap(16, 16), scene);

		return scene;
	}
}