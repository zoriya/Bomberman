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
#include "Controllers/Keyboard.hpp"
#include "Canvas.hpp"
#include "Camera/Camera2D.hpp"

namespace RAY {
    class Window: public Canvas {
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
            const RAY::Vector2 &getDimensions(void) const;

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


            //! @brief Initialize 2D mode with custom camera (2D)
            void beginMode2D(Camera2D &camera);

            //! @brief Initialize 3D mode with custom camera (2D)
            void beginMode3D(Camera3D &camera);

            //! @brief Ends 2D mode with custom camera
            void endMode2D(void);

            //! @brief Ends 3D mode and returns to default 2D orthographic mode
            void endMode3D(void);


            //! @brief draw rectangle
            virtual void draw(const Drawable2D::Rectangle &) = 0;

            //! @brief draw Line
            virtual void draw(const Drawable2D::Line &) = 0;

            //! @brief draw Point
            virtual void draw(const Drawable2D::Point &) = 0;

            //! @brief draw Circle
            virtual void draw(const Drawable2D::Circle &) = 0;

            //! @brief draw Text
            virtual void draw(const Drawable2D::Text &) = 0;
    
            //! @brief draw Triangle
            virtual void draw(const Drawable2D::Triangle &) = 0;

            //! @brief draw Line
            virtual void draw(const Drawable3D::Line &) = 0;

            //! @brief draw Point
            virtual void draw(const Drawable3D::Point &) = 0;

            //! @brief draw Circle
            virtual void draw(const Drawable3D::Circle &) = 0;

            //! @brief draw Cylinder
            virtual void draw(const Drawable3D::Cylinder &) = 0;

            //! @brief draw Plane
            virtual void draw(const Drawable3D::Plane &) = 0;

            //! @brief draw Ray
            virtual void draw(const Drawable3D::Ray &) = 0;
    
            //! @brief draw Sphere
            virtual void draw(const Drawable3D::Sphere &) = 0;

            //! @brief draw Triangle
            virtual void draw(const Drawable3D::Triangle &) = 0;

            //! @brief draw texture at position
            void draw(const Texture &, Vector2 position, Color tint);

        private:
            //! @brief Dimension of window
            RAY::Vector2 _dimensions;

            //! @brief Title of window
            std::string _title;

            //! @brief has the window been open?
            bool _isOpen;
    };
}

#endif /* !WINDOW_HPP_ */
