/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Canvas
*/

#ifndef Canvas_HPP_
#define Canvas_HPP_

#include "Drawables/IDrawable.hpp"

namespace RAY {
    class Canvas {
        public:
            //! @brief A default destructor
            virtual ~Canvas() = default;

            //! @brief draw drawable
            virtual void draw(const Drawables::IDrawable &) = 0;

        protected:
        private:
    };
}

#endif /* !Canvas_HPP_ */
