//
// Created by Louis Auzuret on 06/07/21
//

#include "Component/Tag/TagComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"
#include <string>

namespace BBM
{
	IAControllableSystem::IAControllableSystem(WAL::Wal &wal)
	: System(wal), _wal(wal), _map(), _players(), _cached(false)
	{ }
/*
	float IAControllableSystem::getReturnNumber(lua_State *state)
	{
		float res = 0;

		if (lua_isnil(state, -1))
			return res;
		if (!lua_isnumber(state, -1))
			return res;
		res = lua_tonumber(state, -1);
		lua_pop(state, 1);

		return res;
	}

	bool IAControllableSystem::getReturnBool(lua_State *state)
	{
		bool res = false;

		if (lua_isnil(state, -1))
			return res;
		if (!lua_isboolean(state, -1))
			return res;
		res = lua_toboolean(state, -1);
		lua_pop(state, 1);
		return res;
	}*/

	void IAControllableSystem::UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity)
	{
		if (_cached)
			return;
		if (!_wal.scene.get())
			return;
		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Breakable>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::BREAKABLE));
		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Unbreakable>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::UNBREAKABLE));
		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Bumper>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::BUMPER));
		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Hole>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::HOLE));
		for (auto &[other, pos, _] : _wal.scene->view<PositionComponent, TagComponent<Player>>()) {
			if (static_cast<WAL::Entity>(entity).getUid() == other.getUid())
				continue;
			_players.push_back(MapInfo(pos.position, MapGenerator::NOTHING));
		}
		//for (auto &[other, pos, bomb] : _wal.getScene()->view<PositionComponent, BasicBombComponent>())
		//	_bombs.push_back(std::make_pair(pos.position, bomb.explosionRadius));
		_cached = true;

	}

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		auto &pos = entity.get<PositionComponent>();
		MapInfo player(pos.position, MapGenerator::NOTHING);

		UpdateMapInfos(entity);
		luabridge::LuaRef updateFunc = luabridge::getGlobal(ia.state, "Update");
		if (!updateFunc.isFunction())
			return;
		luabridge::LuaResult res = updateFunc(player, _map, _players);

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

	void IAControllableSystem::onSelfUpdate()
	{
		_cached = false;
		_map.clear();
		_bombs.clear();
		_players.clear();
	}

	bool IAControllableSystem::isInExplosionRange(float x, float y, float z)
	{
		return false;
		//for (auto &bomb : bombs) {
		//	 
		//}
	}
}