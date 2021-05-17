/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <raylib.h>

namespace RAY {
    class Color {
        public:
            //! @brief A Color constructor
            //! @param r R-component of color
            //! @param g B-component of color
            //! @param g G-component of color
            //! @param a A-component of color
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

            //! @brief A constructor using ray's own color struct
            //! @info Useful when want to use pre-defined color
            Color(const ::Color &);

            //! @brief A default copy constructor
            Color(const Color &) = default;

            //! @brief Create a color from an hexadecimal value
            Color(int hexValue);

            //! @brief A default destructor
            ~Color() = default;

            //! @brief An color is assignable
            Color &operator=(const Color &) = default;
            

            //! @brief set R-component of color
            Color &setR(unsigned char r);

            //! @brief set G-component of color
            Color &setG(unsigned char g);

            //! @brief set B-component of color
            Color &setB(unsigned char b);

            //! @brief set A-component of color
            Color &setA(unsigned char a);

            //! @return R-component of color
            unsigned char getR(void) const;

            //! @return G-component of color
            unsigned char getG(void) const;

            //! @return B-component of color
            unsigned char getB(void) const;

            //! @return A-component of color
            unsigned char getA(void) const;

            //! @return color struct
            const ::Color &getColor(void) const; 

            //! @return hexadecimal value of color
            int toHex(void) const;

        private:
            //! @brief Color, really, that's just it...
            ::Color _color;
    };
};

#endif /* !COLOR_HPP_ */
