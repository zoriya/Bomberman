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

		//! @brief All bombs on the map
		std::vector<std::pair<Vector3f, int>> _bombs;

		//! @brief update the raw info of the map
		void UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity);

		//! @brief push danger info position
		void pushInfoDangerPos(LuaG::State &state, int &index, float xpos, float ypos);

		//! @brief push player info
		void pushInfoPlayer(LuaG::State &state, MapInfo &player);

		//! @brief push raw map info
		void pushInfoRaw(LuaG::State &state);

		//! @brief push danger map info
		void pushInfoDanger(LuaG::State &state);

		//! @brief push all the infos to the ai stack
		void pushInfo(LuaG::State &state, MapInfo &player);
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
	};
}
