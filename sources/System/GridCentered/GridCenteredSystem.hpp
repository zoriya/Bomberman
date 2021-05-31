//
// Created by Zoe Roux on 5/24/21.
//

#pragma once

#include <System/System.hpp>

namespace BBM
{
	//! @brief The system handling GridCenteredComponent
	class GridCenteredSystem : public WAL::System
	{
	public:
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		GridCenteredSystem();
		//! @brief A GridCenteredSystem is copyable.
		GridCenteredSystem(const GridCenteredSystem &) = default;
		//! @brief A default destructor
		~GridCenteredSystem() override = default;
		//! @brief A GridCenteredSystem is assignable
		GridCenteredSystem &operator=(const GridCenteredSystem &) = default;
	};
}
