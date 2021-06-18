//
// Created by Louis Auzuret on 06/07/21
//

#include "Component/Bomb/BasicBombComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"
#include <string>

namespace BBM
{
	IAControllableSystem::IAControllableSystem(WAL::Wal &wal)
	: System(wal), _wal(wal), _cached(false)
	{ }

	void IAControllableSystem::UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity)
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
		for (auto &[other, pos, bomb, timer] : _wal.getScene()->view<PositionComponent, BasicBombComponent, TimerComponent>())
			_bombs.push_back(std::make_tuple(pos.position, bomb.explosionRadius, timer.ringIn));
		_cached = true;

	}

	void IAControllableSystem::pushInfoPlayer(LuaG::State &state, MapInfo &player, BombHolderComponent &bombHolder)
	{
		state.push("player");
		state.newTable();
		state.push("x");
		state.push(player.x);
		state.setTable();
		state.push("y");
		state.push(player.z);
		state.setTable();
		state.push("bombCount");
		state.push(bombHolder.bombCount);
		state.setTable();
		state.push("radius");
		state.push(bombHolder.explosionRadius);
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
		for (auto &bomb : _bombs) {
			Vector3f bombPos = std::get<0>(bomb);
			state.push(index++);
			state.newTable();
			state.push("x");
			state.push(bombPos.x);
			state.setTable();
			state.push("y");
			state.push(bombPos.z);
			state.setTable();
			state.push("type");
			state.push(10);
			state.setTable();
			state.setTable();
		}
		state.setTable();
	}

	void IAControllableSystem::pushInfoDangerPos(LuaG::State &state, int &index, float xpos, float ypos, int dangerLevel)
	{
		state.push(index++);
		state.newTable();
		state.push("x");
		state.push(xpos);
		state.setTable();
		state.push("y");
		state.push(ypos);
		state.setTable();
		state.push("level");
		state.push(dangerLevel);
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
			std::chrono::nanoseconds timeleft = std::get<2>(bomb);
			int dangerLevel = std::chrono::duration_cast<std::chrono::seconds>(timeleft).count();
			if (dangerLevel == 0)
				dangerLevel = 1;
			pushInfoDangerPos(state, index, bombPos.x, bombPos.z, dangerLevel);
			pushInfoDangerPos(state, index, bombPos.x, bombPos.z, dangerLevel);
			for (int i = 1; i < bombRadius; i++) {
				Vector3f pos = bombPos - Vector3f(i, 0, 0);
				pushInfoDangerPos(state, index, pos.x, pos.z, dangerLevel);
				pos = bombPos - Vector3f(-i, 0, 0);
				pushInfoDangerPos(state, index, pos.x, pos.z, dangerLevel);
				pos = bombPos - Vector3f(0, 0, i);
				pushInfoDangerPos(state, index, pos.x, pos.z, dangerLevel);
				pos = bombPos - Vector3f(0, 0, -i);
				pushInfoDangerPos(state, index, pos.x, pos.z, dangerLevel);
			}
		}
		state.setTable();
	}

	void IAControllableSystem::pushInfo(LuaG::State &state, MapInfo &player, BombHolderComponent &bombHolder)
	{
		state.newTable();
		pushInfoPlayer(state, player, bombHolder);
		pushInfoRaw(state);
		pushInfoDanger(state);
	}

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		auto &pos = entity.get<PositionComponent>();
		auto &bombHolder = entity.get<BombHolderComponent>();
		MapInfo player(pos.position, MapGenerator::NOTHING);

		if (controllable.disabled)
			return;

		UpdateMapInfos(entity);

		ia._state.getGlobal("Update");
		if (!lua_isfunction(ia._state.getState(), -1))
			return;
		pushInfo(ia._state, player, bombHolder);
		ia._state.callFunction(1, 4);
		controllable.bomb = ia._state.getReturnBool();
		controllable.select = ia._state.getReturnBool();
		controllable.move.y = ia._state.getReturnNumber();
		controllable.move.x = ia._state.getReturnNumber();
		ia._state.popLast();
	}

	void IAControllableSystem::onSelfUpdate(std::chrono::nanoseconds dtime)
	{
		_cached = false;
		_map.clear();
		_bombs.clear();
	}
}