/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <raylib.h>
#include <string>
#include "Vector.hpp"
#include "Keyboard.hpp"
#include "Surface.hpp"

namespace Ray {
    class Window: public Surface {
        public:
            //! @brief Creates window, and opens it if openNow is set to true
            Window(int width, int height, const std::string title, bool openNow = false);

            //! @brief A default copy constructor
            Window(const Window &) = default;

            //! @brief A window is assignable
            Window &operator=(const Window &) = default;
            
            //! @brief Closes window if still open
            ~Window() = default;

            //! @brief Initialize window and OpenGL context
            bool open(void);

            //! @brief Check if KEY_ESCAPE pressed or Close icon pressed
            bool shouldClose(void) const;

            //! @briefSet key used to close window (default: ESC)
            void setExitKey(Keyboard::Key key);

            //! @brief Close window and unload OpenGL context
            bool close(void);

            //! @brief Check if window is currently focused
            bool isFocused(void);

            //! @brief Set window dimensions
            const Ray::Vector2 &getDimensions(void) const;

            //! @brief Shows cursor
            void showCursor(void);

            //! @brief Hides cursor
            void hideCursor(void);

            //! @brief Check if cursor is not visible
            bool cursorIsHidden(void) const;

            //! @brief Check if cursor is on the current screen.
            bool cursorIsOnScreen(void) const;

            //! @brief Set target FPS (maximum)
            void setFPS(int fps); 

            //! @brief Set background color (framebuffer clear color)
            void clear(const Color &color);

            //! @brief Setup canvas (framebuffer) to start drawing
            //! @brief Must be called before first draw of iteration
            void beginDrawing(void);

            //! @brief End canvas drawing and swap buffers (double buffering)
            //! @info Must be called after last draw of iteration
            void endDrawing(void);

            //! @brief draw rectangle
            void draw(const Rectangle &);

            //! @brief draw line
            void draw(const Line &);

            //! @brief draw point
            void draw(const Point &);

            //! @brief draw circle
            void draw(const Circle &);

        private:
            //! @brief Dimension of window
            Ray::Vector2 _dimensions;

            //! @brief Title of window
            std::string _title;

            //! @brief has the window been open?
            bool _isOpen;
    };
}

#endif /* !WINDOW_HPP_ */
