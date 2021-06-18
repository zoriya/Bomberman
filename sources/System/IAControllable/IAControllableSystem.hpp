//
// Created by Louis Auzuret on 06/07/21
//

#pragma once

#include <vector>
#include "Component/BombHolder/BombHolderComponent.hpp"
#include "Map/MapInfo.hpp"
#include "Map/LuaMap.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle keyboard entities.
	class IAControllableSystem : public WAL::System<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent>
	{
	private:
		//! @brief Reference to wal to get Views
		WAL::Wal &_wal;

		//! @brief Are the infos cached for current update
		bool _cached;

		//! @brief Map to handle the informations
		LuaMap _luamap;

		//! @brief All blocks in the map
		std::vector<MapInfo> _map;

		//! @brief All players in the map
		std::vector<MapInfo> _players;

		//! @brief All bombs on the map
		std::vector<std::tuple<Vector3f, int, std::chrono::nanoseconds>> _bombs;

		//! @brief Register the functions to the lua
		void registerFunc(LuaG::State &state);
	
		//! @brief update the raw info of the map
		void UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity);

		//! @brief push danger info position
		void pushInfoDangerPos(LuaG::State &state, int &index, float xpos, float ypos, int dangerLevel);

		//! @brief push player info
		void pushInfoPlayer(LuaG::State &state, MapInfo &player, BombHolderComponent &bombHolder);

		//! @brief push raw map info
		void pushInfoRaw(LuaG::State &state);

		//! @brief push danger map info
		void pushInfoDanger(LuaG::State &state);

		//! @brief push info ennemies
		void pushInfoEnemies(LuaG::State &state);

		//! @brief push all the infos to the lua stack
		void pushInfo(LuaG::State &state, MapInfo &player, BombHolderComponent &bombHolder);
	public:

		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity) override;

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
