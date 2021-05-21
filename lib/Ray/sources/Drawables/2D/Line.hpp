/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef LINE_HPP_
#define LINE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
	class Line: public ADrawable2D
	{
		public:

			//! @brief Line constructor
			//! @param startPosition position of the start point 
			//! @param endPosition position of the end point
			//! @param Color Color of the circle  
			Line(const Vector2 &startPosition, const Vector2 &endPosition, const Color &);

			//! @brief Line constructor
			//! @param xStart x-position of start point  
			//! @param yStart y-position of start point 
			//! @param xEnd x-position of end point  
			//! @param yEnd y-position of end point 
			//! @param length length of the line
			//! @param Color Color of the circle  
			Line(int xStart, int yStart, int xEnd, int yEnd, const Color &);

			//! @brief A default copy constructor
			Line(const Line &) = default;

			//! @brief A line is assignable
			Line &operator=(const Line &) = default;

			//! @brief A default destructor
			~Line() = default;

			//! @return the end position of the line
			const Vector2 &getEndPosition(void) const;

			//! @brief set the end position of the line
			Line &setEndPosition(const Vector2 &);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;
			//! @brief Draw point on image
			void drawOn(RAY::Image &image) override;

		private:
			//! @brief Positon of the end of the line 
			Vector2 _end;
	};
};

#endif /* !PIXEL_HPP_ */
