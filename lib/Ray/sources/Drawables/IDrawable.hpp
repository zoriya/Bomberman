/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include "Window.hpp"

namespace RAY
{
	class Window;
	namespace Drawables {
		//! @brief Interface for any drawable
		class IDrawable {
			public:
				virtual ~IDrawable() = default;

				virtual void drawOn(Window &) = 0;
			protected:
			private:
		};
	}
}


#endif /* !IDRAWABLE_HPP_ */
