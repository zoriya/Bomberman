/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Camera3D
*/

#include "Camera/Camera3D.hpp"

RAY::Camera::Camera3D::Camera3D(const Vector3 &position, const Vector3 &target, const Vector3 &up, float fovy, Projection projection):
	_camera({position, target, up, fovy, projection})
{
}

void RAY::Camera::Camera3D::setPosition(const Vector3 &Position)
{
	this->_camera.position = Position;
}

void RAY::Camera::Camera3D::setTarget(const Vector3 &target)
{
	this->_camera.target = target;
}

void RAY::Camera::Camera3D::setUp(const Vector3 &up)
{
	this->_camera.up = up;
}

void RAY::Camera::Camera3D::setFovy(float fovy)
{
	this->_camera.fovy = fovy;
}

void RAY::Camera::Camera3D::setProjection(Projection projection)
{
	this->_camera.projection = projection;
}

const Vector3 &RAY::Camera::Camera3D::getPosition(void) const
{
	return this->_camera.position;
}

const Vector3 &RAY::Camera::Camera3D::getTarget(void) const
{
	return this->_camera.target;
}

const Vector3 &RAY::Camera::Camera3D::getUp(void) const
{
	return this->_camera.up;
}

float RAY::Camera::Camera3D::getFovy(void) const
{
	return this->_camera.fovy;
}

RAY::Camera::Projection RAY::Camera::Camera3D::getProjection(void) const
{
	return (RAY::Camera::Projection)this->_camera.projection;
}

Matrix RAY::Camera::Camera3D::getMatrix(void) const
{
	return GetCameraMatrix(this->_camera);
}

void RAY::Camera::Camera3D::setMode(Mode mode)
{
	this->_mode = mode;
}

RAY::Camera::Camera3D::operator ::Camera3D() const
{
	return this->_camera;
}
