/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable
*/

#ifndef ADRAWABLE2D_HPP_
#define ADRAWABLE2D_HPP_

#include <raylib.h>
#include <Vector.hpp>
#include "Drawables/IDrawable.hpp"
#include "Color.hpp"

namespace RAY::Drawables::Drawables2D {
	class ADrawable2D: public IDrawable
	{
		public:
			//! @brief ADrawable constructor
			//! @param poition position of top-left point 
			//! @param Color Color of the color  
			ADrawable2D(const Vector2 &position, const RAY::Color &color);
			//! @brief ADrawable constructor
			//! @param x x-position of top-left point  
			//! @param y y-position of top-left point 
			//! @param Color Color of the color  
			ADrawable2D(int x, int y, const RAY::Color &color);

			//! @brief A default copy constructor
			ADrawable2D(const ADrawable2D &) = default;

			//! @brief A default destructor
			virtual ~ADrawable2D() = default;

			//! @return the top-left position of the ADrawable
			const Vector2 &getPosition(void) const;

			//! @return the color of the ADrawable
			const RAY::Color &getColor(void) const;

			//! @brief set Top-left position
			ADrawable2D &setPosition(const Vector2 &position);
			
			//! @brief set Top-left position
			ADrawable2D &setPosition(int x, int y);
			
			//! @brief set color
			ADrawable2D &setColor(const Color &color);

			//! @brief Draw drawble on window
			virtual void drawOn(RAY::Window &) = 0;

			//! @brief Draw drawble on image
			virtual void drawOn(RAY::Image &image) = 0;

		protected:
			//! @brief Top-left position 
			Vector2 _position;
			//! @brief Color of the ADrawable
			Color _color;

	};
};

#endif /* !ADrawable_HPP_ */
