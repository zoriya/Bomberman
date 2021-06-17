
#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Button/ButtonComponent.hpp"
#include "Drawables/2D/Text.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
    std::shared_ptr<WAL::Scene> Runner::loadTitleScreenScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();
		addMenuControl(*scene, sounds);
		scene->addEntity("control")
			.addComponent<SoundComponent>(sounds)
			.addComponent<MusicComponent>("assets/musics/music_title.ogg");
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(320, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_big.png");
		scene->addEntity("text_prompt")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 130, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Press space", 70, RAY::Vector2(), BLACK)
			.addComponent<OnIdleComponent>()
			.addComponent<OnHoverComponent>()
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			});
		return scene;
	}
}