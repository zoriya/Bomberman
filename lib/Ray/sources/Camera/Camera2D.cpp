/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Camera2D
*/

#include "Camera/Camera2D.hpp"

RAY::Camera::Camera2D::Camera2D(const RAY::Vector2 &offset, const RAY::Vector2 &target, float rotation, float zoom):
	_camera({offset, target, rotation, zoom})
{
}


void RAY::Camera::Camera2D::setOffset(const Vector2 &offset)
{
	this->_camera.offset = offset;
}

void RAY::Camera::Camera2D::setTarget(const Vector2 &target)
{
	this->_camera.target = target;
}

void RAY::Camera::Camera2D::setRotation(float rotation)
{
	this->_camera.rotation = rotation;
}

void RAY::Camera::Camera2D::setZoom(float zoom)
{
	this->_camera.zoom = zoom;
}

RAY::Vector2 RAY::Camera::Camera2D::getOffset(void) const
{
	return this->_camera.offset;
}

RAY::Vector2 RAY::Camera::Camera2D::getTarget(void) const
{
	return this->_camera.target;
}

float RAY::Camera::Camera2D::getRotation(void) const
{
	return this->_camera.rotation;
}

float RAY::Camera::Camera2D::getZoom(void) const
{
	return this->_camera.zoom;
}

Matrix RAY::Camera::Camera2D::getMatrix(void) const
{
	return GetCameraMatrix2D(this->_camera);
}

RAY::Camera::Camera2D::operator ::Camera2D() const
{
	return this->_camera;
}
