//
// Created by hbenjamin on 07/06/2021.
//

#pragma once
namespace BBM {
	class BombAnimatorComponent {
	public:
		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief ctor
		explicit BombAnimatorComponent(WAL::Entity &entity);
		//! @brief copy ctor
		BombAnimatorComponent(const BombAnimatorComponent &) = default;
		//! @brief dtor
		~BombAnimatorComponent() override = default;
		//! @brief assignment operator
		BombAnimatorComponent &operator=(const BombAnimatorComponent &) = delete;
	};
}