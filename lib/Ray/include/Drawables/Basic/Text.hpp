/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "Drawables/Drawable.hpp"
#include <string>

namespace Ray {
    class Text: public Drawable
	{
        public:
            //! @brief Text constructor
            //! @param content text
            //! @param fontSize size of the text
            //! @param position position of top-left point (in percentage)
            //! @param Color Color of the text  
            Text(const std::string &content, int fontSize, Vector2 position, Color);
            
            //! @brief Text constructor
            //! @param content text
            //! @param fontSize size of the text
            //! @param x x-position of top-left point (in percentage) 
            //! @param y y-position of top-left point (in percentage)
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

            //! @brief set text content
            Text &setText(const std::string &text);

            //! @brief set font size
            Text &setFontSize(int size);

        private:
            //! @brief Text, just text
            std::string _text;

            //! @brief font size of the text
            int _size;
    };
};


#endif /* !TEXT_HPP_ */
