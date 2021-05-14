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

namespace Ray {
class Window {
    public:
        // Creates window, and opens it if openNow is set to true
        Window(int width, int height, const std::string title, bool openNow = false);
        
        //Closes window if still open
        ~Window() = default;

        // Initialize window and OpenGL context
        bool open(void);

        // Check if KEY_ESCAPE pressed or Close icon pressed
        bool shouldClose(void) const;

        // Close window and unload OpenGL context
        bool close(void);

        // Check if window is currently focused
        bool isFocused(void);

        // Set window dimensions
        const Ray::Vector2 &getDimensions(void) const;

        // Shows cursor
        void showCursor(void);

        // Hides cursor
        void hideCursor(void);

        // Check if cursor is not visible
        bool cursorIsHidden(void) const;

        // Check if cursor is on the current screen.
        bool cursorIsOnScreen(void) const;

    private:
        Ray::Vector2 _dimensions;
        std::string _title;
        bool _isOpen;
};
}

#endif /* !WINDOW_HPP_ */
