/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Window
*/

#include "Window.hpp"
#include <utility>
#include <stdexcept>
#include "Controllers/Mouse.hpp"
#include "Drawables/ADrawable2D.hpp"
#include "Drawables/ADrawable3D.hpp"
#include "Drawables/Image.hpp"

std::optional<RAY::Window> RAY::Window::_instance = std::nullopt;

RAY::Window &RAY::Window::getInstance()
{
	if (!RAY::Window::_instance.has_value())
		throw std::runtime_error("No window has been constructed.");
	return RAY::Window::_instance.value();
}

RAY::Window &RAY::Window::getInstance(int width, int height, const std::string &title, unsigned flags, bool openNow) noexcept
{
	if (!RAY::Window::_instance.has_value()){
		RAY::Window window(width, height, title, flags, openNow);
		RAY::Window::_instance.emplace(std::move(window));
	}
	return RAY::Window::_instance.value();
}

RAY::Window::Window(int width, int height, std::string title, unsigned flags, bool openNow):
	_dimensions(width, height),
	_title(std::move(title)),
	_isOpen(openNow),
	_flags(flags),
	_displayState(NONE)
{
	if (openNow)
		this->open();
}

bool RAY::Window::open(void)
{
	if (this->_flags) {
		SetConfigFlags(this->_flags);
	}
	InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
	this->_isOpen = true;
	this->setExitKey(Controller::Keyboard::Key::KEY_DELETE);
	InitAudioDevice();
	return true;
}

bool RAY::Window::shouldClose(void) const
{
	return WindowShouldClose();
}

void RAY::Window::close(void)
{
	CloseWindow();
	CloseAudioDevice();
}

bool RAY::Window::isFocused(void) const
{
	return IsWindowFocused();
}

const RAY::Vector2 &RAY::Window::getDimensions(void)
{
	this->_dimensions.x = GetScreenWidth();
	this->_dimensions.y = GetScreenHeight();
	return this->_dimensions;
}

RAY::Window &RAY::Window::setDimensions(const Vector2 &dims)
{
	this->_dimensions = dims;
	SetWindowSize(dims.x, dims.y);
	return *this;
}

void RAY::Window::setVisibleCursor(bool visible)
{
	if (visible)
		ShowCursor();
	else
		HideCursor();
}

void RAY::Window::enableCursor(bool enable)
{
	if (enable)
		EnableCursor();
	else
		DisableCursor();
}

bool RAY::Window::cursorIsVisible(void) const
{
	return !IsCursorHidden();
}

RAY::Vector2 RAY::Window::getCursorPosition(void) const
{
	return RAY::Controller::Mouse::getCursorPosition();
}

void RAY::Window::setFPS(unsigned int fps)
{
	SetTargetFPS(fps);
}

void RAY::Window::clear(RAY::Color color)
{
	ClearBackground(color);
}

void RAY::Window::beginDrawing()
{
	BeginDrawing();
}

void RAY::Window::endDrawing()
{
	EndDrawing();
}

void RAY::Window::useCamera(RAY::Camera::Camera2D &camera)
{
	this->unuseCamera();
	this->_displayState = RAY::Window::TWO_DIMENSIONNAL;
	BeginMode2D(camera);
}

void RAY::Window::useCamera(RAY::Camera::Camera3D &camera)
{
	this->unuseCamera();
	this->_displayState = RAY::Window::THREE_DIMENSIONNAL;
	BeginMode3D(camera);
}

void RAY::Window::unuseCamera(void)
{
	switch (this->_displayState)
	{
	case THREE_DIMENSIONNAL:
		EndMode3D();
		break;
	case TWO_DIMENSIONNAL:
		EndMode2D();
		break;
	default:
		break;
	}
	this->_displayState = NONE;
}

void RAY::Window::setTitle(const std::string &title)
{
	this->_title = title;
}

void RAY::Window::draw(RAY::Drawables::IDrawable &drawable)
{
	drawable.drawOn(*this);
}

void RAY::Window::draw(const Mesh &mesh, const Material &material, const Matrix &transform)
{
	DrawMesh(mesh, material, transform);
}

void RAY::Window::setIcon(RAY::Image &img)
{
	SetWindowIcon(img);
}

void RAY::Window::drawFPS(const RAY::Vector2 &position)
{
	DrawFPS(position.x, position.y);
}

bool RAY::Window::isReady() const
{
	return IsWindowReady();
}

void RAY::Window::setExitKey(RAY::Controller::Keyboard::Key key)
{
	SetExitKey(key);
}