//
// Created by Louis Auzuret on 06/07/21
//

#include "Component/Bomb/BasicBombComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"
#include <string>

namespace BBM
{
	IAControllableSystem::IAControllableSystem(WAL::Wal &wal)
	: System(wal), _wal(wal), _cached(false)
	{ }

	void IAControllableSystem::UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity)
	{
		_players.clear();
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Player>>()) {
			if (static_cast<WAL::Entity>(entity).getUid() == other.getUid())
				continue;
			_players.push_back(MapInfo(pos.position, MapGenerator::NOTHING));
		}
		if (_cached)
			return;
		if (!_wal.getScene())
			return;
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Breakable>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::BREAKABLE));
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Unbreakable>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::UNBREAKABLE));
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Bumper>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::BUMPER));
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Hole>>())
			_map.push_back(MapInfo(pos.position, MapGenerator::HOLE));
		for (auto &[other, pos, bomb] : _wal.getScene()->view<PositionComponent, BasicBombComponent>())
			_bombs.push_back(std::make_pair(pos.position, bomb.explosionRadius));
		_cached = true;

	}

	void IAControllableSystem::pushInfoPlayer(LuaG::State &state, MapInfo &player)
	{
		state.push("player");
		state.newTable();
		state.push("x");
		state.push(player.x);
		state.setTable();
		state.push("y");
		state.push(player.z);
		state.setTable();
		state.setTable();
	}

	void IAControllableSystem::pushInfoRaw(LuaG::State &state)
	{
		int index = 0;
		state.push("raw");
		state.newTable();
		for (auto &info : _map) {
			state.push(index++);
			state.newTable();
			state.push("x");
			state.push(info.x);
			state.setTable();
			state.push("y");
			state.push(info.z);
			state.setTable();
			state.push("type");
			state.push(info.type);
			state.setTable();
			state.setTable();
		}
		state.setTable();
	}

	void IAControllableSystem::pushInfoDangerPos(LuaG::State &state, int &index, float xpos, float ypos)
	{
		state.push(index++);
		state.newTable();
		state.push("x");
		state.push(xpos);
		state.setTable();
		state.push("y");
		state.push(ypos);
		state.setTable();
		state.setTable();
	}

	void IAControllableSystem::pushInfoDanger(LuaG::State &state)
	{
		int index = 0;
		state.push("danger");
		state.newTable();
		for (auto &bomb : _bombs) {
			Vector3f bombPos = std::get<0>(bomb);
			int bombRadius = std::get<1>(bomb);
			pushInfoDangerPos(state, index, bombPos.x, bombPos.z);
			for (int i = 1; i < bombRadius; i++) {
				Vector3f pos = bombPos - Vector3f(i, 0, 0);
				pushInfoDangerPos(state, index, pos.x, pos.z);
				pos = bombPos - Vector3f(-i, 0, 0);
				pushInfoDangerPos(state, index, pos.x, pos.z);
				pos = bombPos - Vector3f(0, 0, i);
				pushInfoDangerPos(state, index, pos.x, pos.z);
				pos = bombPos - Vector3f(0, 0, -i);
				pushInfoDangerPos(state, index, pos.x, pos.z);
			}
		}
		state.setTable();
	}

	void IAControllableSystem::pushInfo(LuaG::State &state, MapInfo &player)
	{
		state.newTable();
		pushInfoPlayer(state, player);
		pushInfoRaw(state);
		pushInfoDanger(state);
	}

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		auto &pos = entity.get<PositionComponent>();
		MapInfo player(pos.position, MapGenerator::NOTHING);

		UpdateMapInfos(entity);

		ia._state.getGlobal("Update");
		if (!lua_isfunction(ia._state.getState(), -1))
			return;
		pushInfo(ia._state, player);
		ia._state.callFunction(1, 4);
		controllable.bomb = ia._state.getReturnBool();
		controllable.jump = ia._state.getReturnBool();
		controllable.move.y = ia._state.getReturnNumber();
		controllable.move.x = ia._state.getReturnNumber();
		ia._state.popLast();
	}

	void IAControllableSystem::onSelfUpdate()
	{
		_cached = false;
		_map.clear();
		_bombs.clear();
	}
}