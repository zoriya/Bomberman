//
// Created by Zoe Roux on 5/31/21.
//

#include "TimerUISystem.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Drawables/2D/Text.hpp"

using namespace std::chrono_literals;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	TimerUISystem::TimerUISystem(WAL::Wal &wal)
		: System(wal)
	{}

	void TimerUISystem::onUpdate(WAL::ViewEntity<TimerComponent, Drawable2DComponent, TagComponent<Timer>> &entity, std::chrono::nanoseconds dtime)
	{
		auto &timer = entity.get<TimerComponent>();
		RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.get<Drawable2DComponent>().drawable.get());

		if (text) {
			unsigned long second = std::chrono::duration_cast<std::chrono::seconds>(timer.ringIn).count();
			unsigned long minutes = second / 60;
			second = second % 60;
			std::string stringed = std::to_string(minutes) + ":";
			if (second < 10)
				stringed += "0";
			stringed += std::to_string(second);
			text->setText(stringed);
		}
	}
}