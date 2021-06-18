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

		//! @brief All players in the map
		std::vector<MapInfo> _players;

		//! @brief update danger map with a bomb
		void updateDangerBomb(Vector3f pos, int radius, std::chrono::nanoseconds ringIn);

		//! @brief Register the functions to the lua
		void registerFunc(LuaG::State &state);
	
		//! @brief update the raw info of the map
		void UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity);

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
