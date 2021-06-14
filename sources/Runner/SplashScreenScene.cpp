
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

		auto &splashComponent = scene->addEntity("animation component")
			.addComponent<IntroAnimationComponent>()
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>();
		auto &background = scene->addEntity("background")
			.addComponent<PositionComponent>(0, 0, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(), RAY::Vector2(1920, 1080));
		auto &text = scene->addEntity("powered by text")
			.addComponent<PositionComponent>(1920 / 2 - 200, 1080 / 2 - 180, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("powered by", 30, RAY::Vector2(), BLACK);
		auto &skipText = scene->addEntity("Press space to skip")
			.addComponent<PositionComponent>(1920 - 250, 1080 - 30, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Press space to skip", 20, RAY::Vector2(), BLACK);
		return scene;
	}
}