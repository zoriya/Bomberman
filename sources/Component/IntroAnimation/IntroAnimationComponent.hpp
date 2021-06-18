#pragma once

#include <Component/Component.hpp>

namespace BBM
{
	//! @brief A component to slowly center entities to the middle of their current block.
	//!        This allow flexibility in their movement will preventing them from getting stuck at every corner.
	class IntroAnimationComponent : public WAL::Component
	{
	public:
        unsigned int frameCounter = 0;

		enum animationSteps {
			epitechLogo,
            boxBlinking,
            topLeftgrowing,
            bottomRightGrowing,
            lettersTyping,
            fading,
			prompt,
        };

        enum animationSteps currentStep = epitechLogo;

		//! @inherit
		Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new, default IntroAnimationComponent.
		//! @param entity The entity attached to this component.
		explicit IntroAnimationComponent(WAL::Entity &entity);
		//! @brief A IntroAnimationComponent is copy constructable
		//! @param other The other IntroAnimationComponent to copy.
		IntroAnimationComponent(const IntroAnimationComponent &other) = default;
		//! @brief A default destructor
		~IntroAnimationComponent() override = default;
		//! @brief A IntroAnimationComponent is not assignable
		IntroAnimationComponent &operator=(const IntroAnimationComponent &) = delete;
	};
}
