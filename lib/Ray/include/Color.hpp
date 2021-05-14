/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <raylib.h>

namespace Ray {
    class Color {
        public:
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

            Color(const Color &) = default;

            Color(int hexValue);

            ~Color() = default;

            Color &operator=(const Color &) = default;
            
            Color &setR(unsigned char r);
            Color &setG(unsigned char g);
            Color &setG(unsigned char b);
            Color &setA(unsigned char a);

            unsigned char getR(void) const;
            unsigned char getG(void) const;
            unsigned char getG(void) const;
            unsigned char getA(void) const;

            const ::Color &getColor(void) const; 

            int toHex(void) const;

        private:
            ::Color _color;
    };
};

#endif /* !COLOR_HPP_ */
