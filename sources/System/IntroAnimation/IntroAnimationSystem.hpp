#pragma once

#include "Component/IntroAnimation/IntroAnimationComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Controllable entities in a menu.
	class IntroAnimationSystem : public WAL::System<IntroAnimationComponent>
	{
	private:
		//! @brief reference to wal
		WAL::Wal &wal;

	public:
		//! @inherit
		void onSelfUpdate(std::chrono::nanoseconds dtime) override;

		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<IntroAnimationComponent> &entities) override;

		//! @brief A default constructor
		IntroAnimationSystem(WAL::Wal &wal);
		//! @brief A IntroAnimation system is not copy constructable
		IntroAnimationSystem(const IntroAnimationSystem &) = delete;
		//! @brief A default destructor
		~IntroAnimationSystem() override = default;
		//! @brief A IntroAnimation system is assignable.
		IntroAnimationSystem &operator=(const IntroAnimationSystem &) = default;
	};
}