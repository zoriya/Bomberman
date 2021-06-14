
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/IntroAnimation/IntroAnimationSystem.hpp"
#include "Entity/Entity.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include <Drawables/2D/Rectangle.hpp>
#include <Drawables/2D/Text.hpp>
#include "Runner/Runner.hpp"
#include "Component/Music/MusicComponent.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	IntroAnimationSystem::IntroAnimationSystem(WAL::Wal &wal)
		: System(wal), wal(wal)
	{}

	void IntroAnimationSystem::onFixedUpdate(WAL::ViewEntity<IntroAnimationComponent> &entity)
	{
        static const RAY::Vector2 logoPos(1920 / 2 - 128, 1080 / 2 - 128);
        auto &component = entity.get<IntroAnimationComponent>();
        auto scene = wal.getScene();
        RAY2D::Rectangle *rectangle = nullptr;
        RAY2D::Text *text = nullptr;
        static auto &rayText = scene->addEntity("raylibtext Rectangle")
            .addComponent<PositionComponent>(1920 / 2 - 44, 1080 / 2 + 48, 0)
            .addComponent<Drawable2DComponent, RAY2D::Text>("", 50, RAY::Vector2(), BLACK);
        static auto &bottomRectangle = scene->addEntity("bottom Rectangle")
            .addComponent<PositionComponent>(1920 / 2 - 128, 1080 / 2 - 128, 0)
            .addComponent<Drawable2DComponent, RAY2D::Rectangle>(logoPos, RAY::Vector2(16, 16), BLACK);
        static auto &leftRectangle = scene->addEntity("left Rectangle")
            .addComponent<PositionComponent>(1920 / 2 - 128, 1080 / 2 - 128, 0)
            .addComponent<Drawable2DComponent, RAY2D::Rectangle>(logoPos, RAY::Vector2(16, 16), BLACK);
        static auto &rightRectangle = scene->addEntity("right Rectangle")
            .addComponent<PositionComponent>(1920 / 2 - 128, 1080 / 2 - 128, 0)
            .addComponent<Drawable2DComponent, RAY2D::Rectangle>(logoPos, RAY::Vector2(16, 16), BLACK);
        static auto &topRectangle = scene->addEntity("top Rectangle")
            .addComponent<PositionComponent>(1920 / 2 - 128, 1080 / 2 - 128, 0)
            .addComponent<Drawable2DComponent, RAY2D::Rectangle>(logoPos, RAY::Vector2(16, 16), BLACK);
        static short letterCounter = 0;

        switch (component.currentStep)
        {
        case IntroAnimationComponent::animationSteps::boxBlinking:
            if ((component.frameCounter / 15) % 2)
                topRectangle.getComponent<Drawable2DComponent>().drawable->setColor(BLACK);
            else
                topRectangle.getComponent<Drawable2DComponent>().drawable->setColor(WHITE);
            if (component.frameCounter >= 60) {
                component.currentStep = IntroAnimationComponent::animationSteps::topLeftgrowing;
                component.frameCounter = -1;
                topRectangle.getComponent<Drawable2DComponent>().drawable->setColor(BLACK);
                leftRectangle.getComponent<Drawable2DComponent>().drawable->setColor(BLACK);
            }
            break;
        case IntroAnimationComponent::animationSteps::topLeftgrowing:
            rectangle = dynamic_cast<RAY2D::Rectangle *>(leftRectangle.getComponent<Drawable2DComponent>().drawable.get());
            rectangle->incrementHeight(8);
            rectangle = dynamic_cast<RAY2D::Rectangle *>(topRectangle.getComponent<Drawable2DComponent>().drawable.get());
			rectangle->incrementWidth(8);
            if (rectangle->getWidth() >= 256) {
                component.currentStep = IntroAnimationComponent::animationSteps::bottomRightGrowing;
                bottomRectangle.getComponent<PositionComponent>().position = Vector3f(1920 / 2 - 128, 1080 / 2 - 128 + 240, 0);
                rightRectangle.getComponent<PositionComponent>().position = Vector3f(1920 / 2 - 128 + 240, 1080 / 2 - 128, 0);
            }
            break;
        case IntroAnimationComponent::animationSteps::bottomRightGrowing:
            rectangle = dynamic_cast<RAY2D::Rectangle *>(bottomRectangle.getComponent<Drawable2DComponent>().drawable.get());
            rectangle->incrementWidth(8);
            rectangle = dynamic_cast<RAY2D::Rectangle *>(rightRectangle.getComponent<Drawable2DComponent>().drawable.get());
			rectangle->incrementHeight(8);
            if (rectangle->getHeight() >= 256) {
                component.currentStep = IntroAnimationComponent::animationSteps::lettersTyping;
                component.frameCounter = 0;
            }
            break;
        case IntroAnimationComponent::animationSteps::lettersTyping:
            if ((component.frameCounter / 10) % 2) {
                letterCounter++;
                text = dynamic_cast<RAY2D::Text *>(rayText.getComponent<Drawable2DComponent>().drawable.get());
                if (letterCounter == 2) {
                    scene->addEntity("startup sound")
                        .addComponent<MusicComponent>("assets/sounds/splash_sound.ogg")
                        .getComponent<MusicComponent>().playMusic();
                }
                text->setText(std::string("raylib").substr(0, letterCounter));
            }
            if (component.frameCounter == 60)
                Runner::gameState.nextScene = Runner::gameState.TitleScreenScene;
            break;
        default:
            break;
        }
        component.frameCounter++;
	}

	void IntroAnimationSystem::onSelfUpdate(void)
	{
	}
}