//
// Created by Louis Auzuret on 06/07/21
//

#include "Map/MapInfo.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"
#include <vector>
#include <string>

namespace BBM
{
	IAControllableSystem::IAControllableSystem(WAL::Wal &wal)
	: System(wal), _wal(wal)
	{ }

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		auto &pos = entity.get<PositionComponent>();
		MapInfo player(pos.position, MapGenerator::NOTHING);
		std::vector<MapInfo> infos;
		std::vector<MapInfo> players;

		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Breakable>>())
			infos.push_back(MapInfo(pos.position, MapGenerator::BREAKABLE));

		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Unbreakable>>())
			infos.push_back(MapInfo(pos.position, MapGenerator::UNBREAKABLE));

		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Bumper>>())
			infos.push_back(MapInfo(pos.position, MapGenerator::BUMPER));

		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Hole>>())
			infos.push_back(MapInfo(pos.position, MapGenerator::HOLE));
		
		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Player>>()) {
			if (static_cast<WAL::Entity>(entity).getUid() == other.getUid())
				continue;
			players.push_back(MapInfo(pos.position, MapGenerator::NOTHING));
		}

		luabridge::LuaRef updateFunc = luabridge::getGlobal(ia.state, "Update");
		if (!updateFunc.isFunction())
			return;
		luabridge::LuaResult res = updateFunc(player, infos, players);

		if (res.hasFailed() || res.size() != 4)
			return;
		if (res[0].isNumber())
			controllable.move.x = res[0];
		if (res[1].isNumber())
			controllable.move.y = res[1];
		if (res[2].isBool())
			controllable.jump = res[2];
		if (res[3].isBool())
			controllable.bomb = res[3];
	}
}