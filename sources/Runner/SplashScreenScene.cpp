
#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include "Component/Music/MusicComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Button/ButtonComponent.hpp"
#include "Drawables/2D/Text.hpp"
#include "Component/IntroAnimation/IntroAnimationComponent.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadSplashScreenScene()
	{
		auto scene = std::make_shared<WAL::Scene>();

		addMenuControl(*scene);
		scene->addEntity("animation component")
			.addComponent<IntroAnimationComponent>();
		scene->addEntity("background")
			.addComponent<PositionComponent>(0, 0, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(), RAY::Vector2(1920, 1080));
		scene->addEntity("Press space to skip")
			.addComponent<PositionComponent>(1920 - 250, 1080 - 30, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Press space to skip", 20, RAY::Vector2(), BLACK)
			.addComponent<OnIdleComponent>()
			.addComponent<OnHoverComponent>()
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::TitleScreenScene;
			});
		return scene;
	}
}