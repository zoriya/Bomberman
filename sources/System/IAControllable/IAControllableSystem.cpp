//
// Created by Louis Auzuret on 06/07/21
//

#include "Component/Score/ScoreComponent.hpp"
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
	: System(wal), _wal(wal), _cached(false), _luamap()
	{ }

	void IAControllableSystem::UpdateMapInfos(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity)
	{
		_luamap._enemies.clear();
		if (!_wal.getScene())
			return;
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, ScoreComponent>()) {
			if (other == entity)
				continue;
			_luamap._enemies.push_back(Vector2f(pos.position.x, pos.position.z));
		}
		if (_cached)
			return;
		for (int i = 0; i < 17; i++)
			for (int j = 0; j < 17; j++)
				_luamap._map[i][j] = 0;
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Breakable>>())
			_luamap._map[pos.position.z][pos.position.x] = MapGenerator::BREAKABLE;
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Unbreakable>>())
			_luamap._map[pos.position.z][pos.position.x] = MapGenerator::UNBREAKABLE;
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Bumper>>())
			_luamap._map[pos.position.z][pos.position.x] = MapGenerator::BUMPER;
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Hole>>())
			_luamap._map[pos.position.z][pos.position.x] = MapGenerator::HOLE;
		for (auto &[other, pos, bomb, timer] : _wal.getScene()->view<PositionComponent, BasicBombComponent, TimerComponent>())
			updateDangerBomb(pos.position, bomb.explosionRadius, timer.ringIn);
		_cached = true;
	}

	void IAControllableSystem::updateDangerBomb(Vector3f bombPos, int radius, std::chrono::nanoseconds ringIn)
	{
		Vector3f pos;
		int dangerLevel = std::chrono::duration_cast<std::chrono::seconds>(ringIn).count();
		if (dangerLevel == 0)
			dangerLevel = 1;
		radius++;
		_luamap._map[bombPos.z][bombPos.x] = 10;
		_luamap._danger[bombPos.z][bombPos.x] = dangerLevel;
		for (auto i = 1; i < radius; i++) {
			pos = bombPos - Vector3f(i, 0, 0);
			if (!_luamap.setDanger(pos.x, pos.z, dangerLevel))
				break;
		}
		for (auto i = 1; i < radius; i++) {
			pos = bombPos - Vector3f(-i, 0, 0);
			if (!_luamap.setDanger(pos.x, pos.z, dangerLevel))
				break;
		}
		for (auto i = 1; i < radius; i++) {
			pos = bombPos - Vector3f(0, 0, i);
			if (!_luamap.setDanger(pos.x, pos.z, dangerLevel))
				break;
		}
		for (auto i = 1; i < radius; i++) {
			pos = bombPos - Vector3f(0, 0, -i);
			if (!_luamap.setDanger(pos.x, pos.z, dangerLevel))
				break;
		}
	}

	void IAControllableSystem::registerFunc(LuaG::State &state)
	{
		state.registerClosure(&_luamap, "getMap", LuaMap::getMap);
		state.registerClosure(&_luamap, "getDanger", LuaMap::getDanger);
		state.registerClosure(&_luamap, "getPath", LuaMap::getPath);
		state.registerClosure(&_luamap, "getPlayer", LuaMap::getPlayer);
		state.registerClosure(&_luamap, "getPlayerRound", LuaMap::getPlayerRound);
		state.registerClosure(&_luamap, "getDangerLevelPlayer", LuaMap::getDangerLevelPlayer);
		state.registerClosure(&_luamap, "getDangerLevel", LuaMap::getDangerLevel);
		state.registerClosure(&_luamap, "getBlockType", LuaMap::getBlockType);
		state.registerClosure(&_luamap, "getClosestSafeSpace", LuaMap::getClosestSafeSpace);
		state.registerClosure(&_luamap, "canPutBombSafe", LuaMap::canPutBomb);
		state.registerClosure(&_luamap, "getRadius", LuaMap::getRadius);
		state.registerClosure(&_luamap, "getEnemies", LuaMap::getEnemies);
		state.registerClosure(&_luamap, "getEnemiesRound", LuaMap::getEnemiesRound);
	}

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent, BombHolderComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		auto &pos = entity.get<PositionComponent>();
		auto &bombHolder = entity.get<BombHolderComponent>();

		_luamap.setPlayer(pos.position);
		_luamap.currRadius = bombHolder.explosionRadius;
		if (!ia.registered) {
			this->registerFunc(ia._state);
			ia.registered = true;
		}
		if (controllable.disabled)
			return;
		UpdateMapInfos(entity);
		ia._state.getGlobal("Update");
		if (!lua_isfunction(ia._state.getState(), -1))
			return;
		ia._state.callFunction(0, 4);
		controllable.bomb = ia._state.getReturnBool();
		controllable.secondary = ia._state.getReturnBool();
		controllable.move.y = ia._state.getReturnNumber();
		controllable.move.x = ia._state.getReturnNumber();
		ia._state.popLast();
	}

	void IAControllableSystem::onSelfUpdate(std::chrono::nanoseconds dtime)
	{
		_cached = false;
		_luamap.clearDanger();
	}
}