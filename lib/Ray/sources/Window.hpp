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
#include <optional>
#include "Drawables/Image.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector3.hpp"
#include "Controllers/Keyboard.hpp"
#include "Camera/Camera2D.hpp"
#include "Camera/Camera3D.hpp"
#include "Color.hpp"

namespace RAY {
	//! @brief Window manager
	namespace Drawables {
		class IDrawable;
		class ADrawable3D;
		namespace Drawables3D
		{
			class Model;
		}
	}
	class Window {
		private:
			//! @brief The window's instance as an optional.
			static std::optional<Window> _instance;
		public:
			//! @brief Get The window's instance, if the window has not been already constructed a runtime exception is thrown.
			static Window &getInstance();

			//! @return A widow insta,ce. Only one window can be open at a time
			static Window &getInstance(int width, int height, const std::string &title, unsigned flags = 0, bool openNow = true) noexcept;
			
			//! @brief A window is movable.
			Window(Window &&) = default;

			//! @brief A default copy constructor
			Window(const Window &window) = delete;

			//! @brief A window is assignable
			Window &operator=(const Window &window) = delete;
			
			//! @brief Closes window if still open
			~Window() = default;

			//! @brief Initialize window and OpenGL context
			bool open(void);

			//! @brief Check if KEY_ESCAPE pressed or Close icon pressed
			bool shouldClose(void) const;

			//! @brief Close window and unload OpenGL context
			void close(void);

			//! @brief Check if window is currently focused
			bool isFocused(void) const;

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

			//! @brief set the window icon
			void setIcon(RAY::Image &img);

			//! @brief Get the cursor position
			Vector2 getCursorPosition() const;

			//! @brief Set target FPS (maximum)
			void setFPS(unsigned int fps);

			//! @brief Set background color (framebuffer clear color)
			//! @param color The color to clear the screen (default: black)
			void clear(const Color &color = BLACK);

			//! @brief Different states of the view of the window
			enum displayState {
				//! @brief When a custom 2D camera is used
				TWO_DIMENSIONNAL,
				//! @brief When a custom 3D camera is used
				THREE_DIMENSIONNAL,
				//! @brief When no camera is used
				NONE,
			};

			//! @brief Draw the content of the buffer on the screen.
			void draw();

			//! @brief Initialize 2D mode with custom camera (2D)
			void useCamera(Camera::Camera2D &camera);

			//! @brief Initialize 3D mode with custom camera (2D)
			void useCamera(Camera::Camera3D &camera);

			//! @brief Ends current view mode and returns to default mode
			void unuseCamera(void);

			//! @brief Set the window title
			void setTitle(const std::string &title);


			//! @brief draw drawable
			//! @param drawable The drawable to render on screen
			void draw(RAY::Drawables::IDrawable &drawable);

			//! @brief Draw a 3d mesh with material and transform
			void draw(const Mesh &mesh, const Material &material, const Matrix &transform);


		private:
			//! @brief Creates window, and opens it if openNow is set to true
			Window(int width, int height, std::string title, unsigned flags = 0, bool openNow = true);

			//! @brief Dimension of window
			RAY::Vector2 _dimensions;

			//! @brief Title of window
			std::string _title;

			//! @brief has the window been open?
			bool _isOpen;

			//! @brief flags for the window (ex: FLAG_WINDOW_RESIZABLE)
			unsigned int _flags;

			//! @brief Current window draw-state
			enum displayState _displayState;
	};
}

#endif /* !WINDOW_HPP_ */
