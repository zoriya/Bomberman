//
// Created by Zoe Roux on 5/31/21.
//

#include "TimerSystem.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Drawables/2D/Text.hpp"

using namespace std::chrono_literals;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	TimerSystem::TimerSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void TimerSystem::onUpdate(WAL::ViewEntity<TimerComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &timer = entity.get<TimerComponent>();
		timer.ringIn -= dtime;
		if (timer.ringIn <= 0ns) {
			timer.setDisable(true);
			timer.callback(entity, this->_wal);
		}

		RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.get<Drawable2DComponent>().drawable.get());

		if (text) {
			unsigned long second = std::chrono::duration_cast<std::chrono::seconds>(timer.ringIn).count();
			unsigned long minutes = second / 60;
			second = second % 60;
			text->setText(std::to_string(minutes) + ":" + std::to_string(second));
		}
	}
}