//
// Created by Tom Augier on 05/06/2021
//

#include "CameraSystem.hpp"
#include "Entity/Entity.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Runner/Runner.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Drawables/2D/Text.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	CameraSystem::CameraSystem(WAL::Wal &wal)
		: System(wal)
	{}

	bool CameraSystem::introAnimation(WAL::ViewEntity<CameraComponent, PositionComponent> &entity)
	{	
		auto &pos = entity.get<PositionComponent>();
		static Vector3f posTarget(8, 25, 7);

		if (hasEnded)
			return true;
		if (pos.position.distance(posTarget) < 4) {
			hasEnded = true;
			this->_wal.getScene()->scheduleNewEntity("white background")
				.addComponent<PositionComponent>(1920 / 2 - 2 * 30 - 20, 28, 0)
				.addComponent<Drawable2DComponent, RAY2D::Rectangle>(Vector2f(), Vector2f(150, 60), RAY::Color(BLACK).setA(150));
			this->_wal.getScene()->scheduleNewEntity("Timer")
				.addComponent<TimerComponent>(Runner::timerDelay, [](WAL::Entity &, WAL::Wal &engine) {
					engine.getSystem<CameraSystem>().hasEnded = false;
					Runner::gameState.nextScene = GameState::ScoreScene;
				})
				.addComponent<PositionComponent>(1920 / 2 - 2 * 30, 30, 0)
				.addComponent<TagComponent<Timer>>()
				.addComponent<Drawable2DComponent, RAY2D::Text>("", 60, RAY::Vector2(), ORANGE);
			for (WAL::Entity &player : this->_wal.getScene()->view<TagComponent<Player>>())
				player.getComponent<ControllableComponent>().disabled = false;
			return true;
		}

		pos.position += (posTarget - pos.position) / 100;
		return false;
	}

	void CameraSystem::onUpdate(WAL::ViewEntity<CameraComponent, PositionComponent> &entity,
	                            std::chrono::nanoseconds dtime) {
		if (Runner::gameState.currentScene != GameState::GameScene || !introAnimation(entity))
			return;
		auto &pos = entity.get<PositionComponent>();
		auto &cam = entity.get<CameraComponent>();
		Vector3f newCameraPos = Vector3f(-1, -1, -1);
		std::vector<Vector3f> playerPos;
		float maxDist = 0;
		float lowerXDist = 0;
		float lowerZDist = 0;
		for (auto &[player, position, _] : this->_wal.getScene()->view<PositionComponent, TagComponent<Player>>()) {
			playerPos.emplace_back(position.position);
		}
		if (pos.position.x > Runner::mapWidth || pos.position.z > Runner::mapHeight) {
			pos.position.x = Runner::mapWidth / 2;
			pos.position.y = (Runner::mapHeight / 2) - 1;
		}
		if (playerPos.size() == 1)
			newCameraPos = playerPos[0];
		for (size_t i = 0; i < playerPos.size(); i++)
			for (size_t j = 0; j < playerPos.size(); j++) {
				if (i == j)
					continue;
				if (maxDist < playerPos[i].distance(playerPos[j])) {
					maxDist = playerPos[i].distance(playerPos[j]);
					newCameraPos = (playerPos[i] + playerPos[j]) / 2;
				}
				if (lowerXDist < std::abs((playerPos[i].x - playerPos[j].x)))
					lowerXDist = std::abs((playerPos[i].x - playerPos[j].x));
				if (lowerZDist < std::abs((playerPos[i].z - playerPos[j].z)))
					lowerZDist = std::abs((playerPos[i].z - playerPos[j].z));
			}
		maxDist += (lowerXDist  + lowerZDist) / 2;
		if (maxDist < 1)
			return;
		if (maxDist < 14)
			maxDist = 14;
		if (maxDist > 23)
			maxDist = 23;
		for (auto &[other, backPos, _] : this->_wal.getScene()->view<PositionComponent, TagComponent<Background>>()) {
			backPos.position = cam.target;
		}
		newCameraPos.y = 0;
		if (lowerXDist < 0.5)
			newCameraPos.x = pos.position.x;
		if (lowerZDist < 0.5)
			newCameraPos.z = pos.position.z;
		cam.target += (newCameraPos.abs() - cam.target.abs()) / 10;
		cam.target = cam.target.abs();
		newCameraPos.y = maxDist;
		if (lowerZDist > 0.5 || cam.target.z >= pos.position.z)
			newCameraPos.z = cam.target.z > 1 ? newCameraPos.z - 1 : 0;
		pos.position += (newCameraPos.abs() - pos.position.abs()) / 10;
	}
}