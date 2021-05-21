/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Canvas
*/

#ifndef CANVAS_HPP_
#define CANVAS_HPP_

namespace RAY {
    namespace Drawables {
        class IDrawable;
    }
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
