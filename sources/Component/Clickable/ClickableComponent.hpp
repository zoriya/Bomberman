//
// Created by Louis Auzuret on 2021-05-24
//

#pragma once

#include "lib/wal/sources/Models/Callback.hpp"
#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM
{
	template<typename T>
	class ClickableComponent : public WAL::Component
	{
		private:
			WAL::Callback<WAL::Entity &, T &> _callback;
		protected:
		public:
			//! @brief Instanciate the component with no callback
			ClickableComponent(void)
			{ }

			//! @brief Instanciate the component with given callback
			ClickableComponent(std::function<void (WAL::Entity &, T &)> callback)
			{
				_callback.addCallback(callback);
			}
			//! @brief add a callback to the component
			int addCallback(std::function<void (WAL::Entity &, T &)> callback)
			{
				return _callback.addCallback(callback);
			}

			//! @brief remove a callback from the component
			void removeCallback(int id)
			{
				_callback.removeCallback(id);
			}
	};
} //namespace BBM