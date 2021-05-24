/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable
*/

#ifndef ADRAWABLE3D_HPP_
#define ADRAWABLE3D_HPP_

#include <raylib.h>
#include "Drawables/IDrawable.hpp"
#include "Color.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Abstraction of any three-dimensionnal drawable
	class ADrawable3D: public IDrawable
	{
		public:
			//! @param Color Color of the drawable 
			//! @param Position Position of the drawable (wether its center or start position for lines)
			ADrawable3D(const RAY::Vector3 &position, const RAY::Color &color);

			//! @brief A default copy constructor
			ADrawable3D(const ADrawable3D &) = default;

			//! @brief A default destructor
			virtual ~ADrawable3D() = default;

			//! @brief Draw drawble on window
			virtual void drawOn(RAY::Window &) = 0;

			//! @return the color of the ADrawable
			const RAY::Color &getColor(void) const;
			
			//! @brief set color
			ADrawable3D &setColor(const RAY::Color &color);

			//! @return the position of the ADrawable
			virtual const Vector3 &getPosition(void) const;
			
			//! @brief set position
			virtual ADrawable3D &setPosition(const Vector3 &position);

		protected:
			//! @brief Position of the ADrawable
			Vector3 _position;

			//! @brief Color of the ADrawable
			Color _color;

	};
};

#endif /* !ADrawable_HPP_ */
