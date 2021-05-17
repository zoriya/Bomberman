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

            //! @brief Close window and unload OpenGL context
            bool close(void);

            //! @brief Check if window is currently focused
            bool isFocused(void);

            //! @brief Set window dimensions
            const RAY::Vector2 &getDimensions(void) const;

            //! @brief Set the cursor visibility
            //! @param visible True if the cursor is visible
            void setVisibleCursor(bool visible);

            //! @brief Enable/Disable the cursor
            //! @param enable True for the cursor to be enabled
            void enableCursor(bool enable);

            //! @brief Check if cursor is not visible
            bool cursorIsVisible(void) const;

            //! @brief Set target FPS (maximum)
            void setFPS(unsigned int fps);

            //! @brief Set background color (framebuffer clear color)
            //! @param color The color to clear the screen (default: black)
            void clear(const Color &color = Color(0, 0, 0, 0));

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

            //! @brief Set the window title
            void setTitle(const std::string &title);


            //! @brief draw rectangle
            //! @param drawable The drawable to render on screen
            void draw(const Drawables::IDrawable &drawable);

            //! @brief draw texture at position
            //! @param texture The object to render
            //! @param position The position of the texture relative to the top left window corner
            //! @param tint
            void draw(const Texture &texture, Vector2 position, const Color &tint);

            //! @brief Draw a 3d mesh with material and transform
            void draw(const Mesh &mesh, const Material &material, const Matrix &transform);

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
