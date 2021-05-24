/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef LINE3D_HPP_
#define LINE3D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Line in a three-dimensionnal space
	class Line: public ADrawable3D
	{
		public:
			//! @brief Line constructor
			//! @param startPosition position of top-left point  
			//! @param startPosition position of bottom-rigth point  
			//! @param Color Color of the line  
			Line(const Vector3 &startPosition, const Vector3 &endPosition, const Color &color);

			//! @brief A default copy constructor
			Line(const Line &) = default;

			//! @brief A line is assignable
			Line &operator=(const Line &) = default;

			//! @brief A default destructor
			~Line() = default;


			//! @return the start position of the line
			const Vector3 &getStartPosition(void) const;

			//! @return the end position of the line
			const Vector3 &getEndPosition(void) const;

			//! @brief Set start position
			Line &setStartPosition(const Vector3 &startPosition);

			//! @brief Set end position
			Line &setEndPosition(const Vector3 &endPosition);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;

		private:
			//! @brief end position
			Vector3 _endPosition;
	};
};

#endif /* !PIXEL_HPP_ */
