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
    class Text: public ADrawable2D
	{
        public:
            //! @brief Text constructor
            //! @param content text
            //! @param fontSize size of the text
            //! @param position position of top-left point 
            //! @param Color Color of the text  
            Text(const std::string &content, int fontSize, Vector2 position, Color);
            
            //! @brief Text constructor
            //! @param content text
            //! @param fontSize size of the text
            //! @param x x-position of top-left point  
            //! @param y y-position of top-left point 
            //! @param Color Color of the text  
            Text(const std::string &content, int fontSize, int x, int y, Color);
            
            //! @brief A default copy constructor
            Text(const Text &) = default;

            //! @brief A text is assignable
            Text &operator=(const Text &) = default;

            //! @brief A default destructor
            ~Text() = default;

            //! @return the text's content
            const std::string &getString(void);

            //! @return the font size
            int getFontSize(void);

            //! @return set font
            Text &setFont(const Font &font);

            //! @brief set text content
            Text &setText(const std::string &text);

            //! @brief set font size
            Text &setFontSize(int size);

            //! @brief Draw text on window
            void drawOn(Canvas &);

        private:
            //! @brief Text, just text
            std::string _text;

            //! @brief Font
            Font _font;

            //! @brief font size of the text
            int _size;
    };
};


#endif /* !TEXT_HPP_ */
