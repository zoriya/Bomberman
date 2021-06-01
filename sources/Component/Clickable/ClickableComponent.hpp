//
// Created by Louis Auzuret on 2021-05-24
//

#pragma once

#include "Models/Callback.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <unordered_map>

namespace BBM
{
	class ClickableComponent : public WAL::Component
	{
		private:
		public:
			//! @brief Callback holder
			WAL::Callback<WAL::Entity &> _onClick;
			//! @brief Instanciate the component with no callback
			ClickableComponent(WAL::Entity &entity);

			//! @brief Default destructor
			~ClickableComponent() override = default;

			//! @brief A ClickableComponent can't be assigned
			ClickableComponent &operator=(const ClickableComponent &) = delete;

			//! @brief A component can't be instantiated, it should be derived.
			ClickableComponent(const ClickableComponent &) = default;

			//! @brief Clone a component for another or the same entity.
			//! @param entity The entity that owns the ne component.
			ClickableComponent *clone(WAL::Entity &entity) const override;

			//! @brief add a callback to the component
			//! @param type the type of event the callback will be assigned to
			int addCallback(std::function<void (WAL::Entity &)> callback);
	};
} //namespace BBM