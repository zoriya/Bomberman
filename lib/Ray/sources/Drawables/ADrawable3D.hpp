/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable
*/

#ifndef ADRAWABLE3D_HPP_
#define ADRAWABLE3D_HPP_

#include <raylib.h>
#include "Vector/Vector3.hpp"
#include "Drawables/IDrawable.hpp"
#include "Color.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Abstraction of any three-dimensionnal drawable
	class ADrawable3D: public IDrawable
	{
		public:
			//! @param Color Color of the drawable  
			ADrawable3D(const RAY::Color &color);

			//! @brief A default copy constructor
			ADrawable3D(const ADrawable3D &) = default;

			//! @brief A default destructor
			virtual ~ADrawable3D() = default;

			//! @brief Draw drawble on window
			virtual void drawOn(RAY::Window &) = 0;

			//! @return the color of the ADrawable
			const Color &getColor(void) const;
			
			//! @brief set color
			ADrawable3D &setColor(const RAY::Color &color);

		protected:
			//! @brief Color of the ADrawable
			Color _color;

	};
};

#endif /* !ADrawable_HPP_ */
