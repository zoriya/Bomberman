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
		for (auto &[other, pos, _] : _wal.getScene()->view<PositionComponent, TagComponent<Player>>()) {
			if (static_cast<WAL::Entity>(entity).getUid() == other.getUid())
				continue;
			_players.push_back(MapInfo(pos.position, MapGenerator::NOTHING));
		}
		for (auto &[other, pos, bomb] : _wal.getScene()->view<PositionComponent, BasicBombComponent>())
			_bombs.push_back(std::make_pair(pos.position, bomb.explosionRadius));
		_cached = true;

	}

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, ControllableComponent, IAControllableComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		auto &pos = entity.get<PositionComponent>();
		MapInfo player(pos.position, MapGenerator::NOTHING);

		UpdateMapInfos(entity);

        luabridge::getGlobalNamespace(ia.state)
            .beginNamespace ("luaBBM")
				.addFunction("isInExplosionRange", IAControllableSystem::isInExplosionRange)
			.endNamespace();
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
		Vector3f pos(x, y, z);
		//pos = pos.round();
		//for (auto &bomb : _bombs) {
		//	Vector3f bombPos = std::get<0>(bomb);
		//	int bombRadius = std::get<1>(bomb);
		//	for (int i = 1; i < bombRadius; i++) {
		//		if (pos == bombPos - Vector3f(i, 0, 0))
		//			return true;
		//		if (pos == bombPos - Vector3f(-i, 0, 0))
		//			return true;
		//		if (pos == bombPos - Vector3f(0, 0, i))
		//			return true;
		//		if (pos == bombPos - Vector3f(0, 0, -i))
		//			return true;	
		//	}
		//}
		return true;
	}
}