/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Canvas
*/

#ifndef CANVAS_HPP_
#define CANVAS_HPP_

namespace RAY {
	namespace Drawables {
		class ADrawable2D;
	}
	//! @brief Interface for any drawable surface
	class Canvas {
		public:
			//! @brief A default destructor
			virtual ~Canvas() = default;

			//! @brief draw drawable
			virtual void draw(Drawables::ADrawable2D &) = 0;

		protected:
		private:
	};
}

#endif /* !Canvas_HPP_ */
