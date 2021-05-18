/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Window
*/

#include "Window.hpp"
#include "Mouse.hpp"

RAY::Window::Window(int width, int height, const std::string title, bool openNow):
    _isOpen(openNow), _dimensions({width, height}), _title(title)
{
    if (this->_isOpen)
        this->open();
}

bool RAY::Window::open(void)
{
    InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
    this->_isOpen = true;
    return true;
}

bool RAY::Window::shouldClose(void) const
{
    return WindowShouldClose();
}

void RAY::Window::close(void)
{
    CloseWindow();
}

bool RAY::Window::isFocused(void) const
{
    return IsWindowFocused();
}

const RAY::Vector2 &RAY::Window::getDimensions(void) const
{
    return this->_dimensions;
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

Vector2 RAY::Window::getCursorPosition(void) const
{
    return RAY::Mouse::getCursorPosition();
}

void RAY::Window::setFPS(unsigned int fps)
{
    SetTargetFPS(fps);
}

void RAY::Window::clear(const RAY::Color &color)
{
    ClearBackground(color.getColor());
}

void RAY::Window::beginDrawing(void)
{
    ::BeginDrawing();
}

void RAY::Window::endDrawing(void)
{
    ::EndDrawing();
}

void RAY::Window::beginMode2D(Camera::Camera2D &camera)
{
    BeginMode2D(camera.getCamera());
}

void RAY::Window::beginMode3D(Camera::Camera3D &camera)
{
    BeginMode3D(camera.getCamera());
}

void RAY::Window::endMode2D(void)
{
    EndMode2D();
}

void RAY::Window::endMode3D(void)
{
    EndMode3D();
}

void RAY::Window::setTitle(const std::string &title)
{
    this->_title = title;
}

void RAY::Window::draw(Drawables::IDrawable &drawable)
{
    drawable.drawOn(*this);
}

void RAY::Window::draw(const RAY::Texture &texture, Vector2 position, const Color &tint)
{
    DrawTexture(texture.getTexture(), position.x, position.y, tint.getColor());
}

void RAY::Window::draw(const Mesh &mesh, const Material &material, const Matrix &transform)
{
    DrawMesh(mesh, material, transform);
}