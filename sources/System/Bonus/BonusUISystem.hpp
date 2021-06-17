//
//
//

#pragma once

#include "System/System.hpp"
#include "Wal.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Stat/StatComponent.hpp"

namespace BBM
{
	//! @brief The system that allow the text of the ui to display current values
	class BonusUISystem : public WAL::System<StatComponent, Drawable2DComponent>
	{
	private:
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<StatComponent, Drawable2DComponent> &entity) override;

		//! @brief A default constructor
		explicit BonusUISystem(WAL::Wal &wal);
		//! @brief A bomb holder system is copy constructable
		BonusUISystem(const BonusUISystem &) = default;
		//! @brief A default destructor
		~BonusUISystem() override = default;
		//! @brief A bomb holder system is not assignable.
		BonusUISystem &operator=(const BonusUISystem &) = delete;
	};
}

