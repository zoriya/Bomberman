//
// Created by Louis Auzuret on 06/07/21
//

#pragma once

#include <vector>
#include "Map/MapInfo.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle keyboard entities.
	class IAControllableSystem : public WAL::System<PositionComponent, ControllableComponent, IAControllableComponent>
	{
	private:
		//! @brief Reference to wal to get Views
		WAL::Wal &_wal;

		//! @brief Are the infos cached for current update
		bool _cached;

		//! @brief All blocks in the map
		std::vector<MapInfo> _map;

		//! @brief All players in the map
		std::vector<MapInfo> _players;

		std::vector<std::pair<Vector3f, int>> _bombs;

		//! @brief
		void UpdateMapInfos(WAL::Entity entity);
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity) override;

		//! @inherit
		void onSelfUpdate() override;

		//! @brief A default constructor
		IAControllableSystem(WAL::Wal &wal);
		//! @brief A keyboard system is copy constructable
		IAControllableSystem(const IAControllableSystem &) = default;
		//! @brief A default destructor
		~IAControllableSystem() override = default;
		//! @brief A keyboard system is assignable.
		IAControllableSystem &operator=(const IAControllableSystem &) = default;

		static bool isInExplosionRange(float x, float y, float z);
	};
}
