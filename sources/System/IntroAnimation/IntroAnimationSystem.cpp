
#include <algorithm>
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/IntroAnimation/IntroAnimationSystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include <Drawables/2D/Rectangle.hpp>

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	IntroAnimationSystem::IntroAnimationSystem(WAL::Wal &wal)
		: System(wal), wal(wal)
	{}

	void IntroAnimationSystem::onFixedUpdate(WAL::ViewEntity<IntroAnimationComponent> &entity)
	{
        auto &component = entity.get<IntroAnimationComponent>();
        auto &scene = wal.getScene();

        switch (component.currentStep)
        {
        case IntroAnimationComponent::animationSteps::init:
            scene->addEntity("white background")
               .addComponent<Drawable2DComponent, RAY2D::Rectangle>(BBM::Vector2f(), BBM::Vector2f(1920, 1080), WHITE);
            
            scene->addEntity("blinking square").addComponent<Drawable2DComponent, RAY2D::Rectangle>(BBM::Vector2f(), BBM::Vector2f(16, 16), WHITE);
            component.currentStep = IntroAnimationComponent::animationSteps::boxBlinking;
            break;
        case IntroAnimationComponent::animationSteps::boxBlinking:

            if ((component.frame / 15) % 2)
                scene->getEntities()
            break;
        
        }
        component.frame++;
	}

	void IntroAnimationSystem::onSelfUpdate(void)
	{
	}
}