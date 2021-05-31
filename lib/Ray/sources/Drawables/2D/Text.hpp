/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "Drawables/ADrawable2D.hpp"
#include <string>

namespace RAY::Drawables::Drawables2D {
	//! @brief Text in a two-dimensionnal space
	class Text: public ADrawable2D
	{
		public:
			//! @brief The Letter spacing used when creating a Text instance
			static constexpr int DefaultLetterSpacing = 1;
			//! @brief Text constructor
			//! @param content text
			//! @param fontSize size of the text
			//! @param position position of top-left point 
			//! @param Color Color of the text  
			Text(std::string content, int fontSize, const Vector2 &position, const Color &color);
			
			//! @brief Text constructor
			//! @param content text
			//! @param fontSize size of the text
			//! @param x x-position of top-left point  
			//! @param y y-position of top-left point 
			//! @param Color Color of the text  
			Text(std::string content, int fontSize, int x, int y, const Color &color);
			
			//! @brief A default copy constructor
			Text(const Text &) = default;

			//! @brief A text is assignable
			Text &operator=(const Text &) = default;

			//! @brief A default destructor
			~Text() override = default;

			//! @return the text's content
			const std::string &getString(void);

			//! @return the font size
			int getFontSize(void) const;

			//! @return the letter spacing
			int getLetterSpacing(void) const;

			//! @return set font
			Text &setFont(const Font &font);

			//! @brief set text content
			Text &setText(const std::string &text);

			//! @brief set text spacing
			Text &setLetterSpacing(int spacing);

			//! @brief set font size
			Text &setFontSize(int size);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;
			//! @brief Draw point on image
			void drawOn(RAY::Image &image) override;

		private:
			//! @brief Text, just text
			std::string _text;

			//! @brief Font
			Font _font;

			//! @brief font size of the text
			int _size;

			//! @brief spacing of chars
			int _spacing;
	};
};

#endif /* !TEXT_HPP_ */
