//
// Created by Zoe Roux on 5/27/21.
//

#pragma once

#include <Component/Component.hpp>
#include <Models/Vector3.hpp>

namespace BBM
{
	//! @brief A class allowing one to place the camera in the scene.
	//! @warning Only one CameraComponent is allowed on the scene. Using more than one result in undefined behaviors.
	class CameraComponent : public WAL::Component
	{
	public:
		//! @brief The camera's target, the cam will look at this position.
		Vector3f target;

		//! @inherit
		Component *clone(WAL::Entity &entity) const override;

		//! @brief Ctor
		explicit CameraComponent(WAL::Entity &, Vector3f cameraTarget = Vector3f());
		//! @brief A camera component is copy constructable.
		CameraComponent(const CameraComponent &) = default;
		//! @brief Default destructor.
		~CameraComponent() override = default;
		//! @brief A camera component can't be assigned.
		CameraComponent &operator=(const CameraComponent &) = delete;
	};
}