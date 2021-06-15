/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef RECTANGLE2D_HPP_
#define RECTANGLE2D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D
{
	//! @brief Rectangle in a two-dimensional space
	class Rectangle : public ADrawable2D
	{
	public:
		//! @brief Rectangle constructor
		//! @param position position of top-left point
		//! @param dimensions dimensions of the rectangle
		//! @param Color Color of the rectangle
		Rectangle(const Vector2 &position,
		          const Vector2 &dimensions,
		          const Color &color = WHITE,
		          float scale = 1,
		          float rotation = 0);

		//! @brief Rectangle constructor
		//! @param x x-position of top-left point
		//! @param y y-position of top-left point
		//! @param width width of the rectangle
		//! @param length length of the rectangle
		//! @param Color Color of the rectangle
		Rectangle(int x, int y, int width, int height, const Color &color = WHITE);

		//! @brief A default copy constructor
		Rectangle(const Rectangle &) = default;

		//! @brief A rectangle is assignable
		Rectangle &operator=(const Rectangle &) = default;

		//! @brief A default destructor
		virtual ~Rectangle() override = default;

		//! @return the dimensions of the rectangle
		const Vector2 &getDimensions(void);

		//! @return the width of the rectangle
		float getWidth(void) const;

		//! @return the height of the rectangle
		float getHeight(void) const;

		//! @brief set dimensions
		Rectangle &setDimensions(const Vector2 &dimensions);

		//! @brief increment width of the rectangle
		//! @param width incrementer
		Rectangle &incrementWidth(float width);

		//! @brief increment height of the rectangle
		//! @param height incrementer
		Rectangle &incrementHeight(float height);

		//! @brief set rectangle's height
		//! @param height height of the rectangle
		Rectangle &setHeight(float height);

		//! @brief set rectangle's width
		//! @param width width of the rectangle
		Rectangle &setWidth(float width);

		//! @brief set dimensions
		Rectangle &setDimensions(float x, float y);

		//! @brief Draw point on window
		virtual void drawOn(RAY::Window &) override;

		//! @brief Draw point on image
		virtual void drawOn(RAY::Image &image) override;

	protected:
		//! @brief Diemnsions of the rectangle
		Vector2 _dimensions;

	INTERNAL:

		operator ::Rectangle() const;
	};
};

#endif /* !PIXEL_HPP_ */
