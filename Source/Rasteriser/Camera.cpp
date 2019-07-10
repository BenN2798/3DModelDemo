#include "Camera.h"

Camera::Camera()
{
	_xRotation = 0;
	_yRotation = 0;
	_zRotation = 0;
	_position = Vertex(0, 0, 0, 1);
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;
}

Camera::~Camera()
{
}

void Camera::SetXRotation(float i)
{
	_xRotation = i;
}

void Camera::SetYRotation(float i)
{
	_yRotation = i;
}

void Camera::SetZRotation(float i)
{
	_zRotation = i;
}

void Camera::SetPosition(const Vertex& rhs)
{
	_position = rhs;
}

Matrix Camera::GetCameraMatrix()
{
	Matrix cameraX(1, 0, 0, 0, 0, cos(_xRotation), sin(_xRotation), 0, 0, -sin(_xRotation), cos(_xRotation), 0, 0, 0, 0, 1);
	Matrix cameraY(cos(_yRotation), 0, -sin(_yRotation), 0, 0, 1, 0, 0, sin(_yRotation), 0, cos(_yRotation), 0, 0, 0, 0, 1);
	Matrix cameraZ(cos(_zRotation), sin(_zRotation), 0, 0, -sin(_zRotation), cos(_zRotation), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	Matrix cameraPosition(1, 0, 0, -_position.GetX(), 0, 1, 0, -_position.GetY(), 0, 0, 1, -_position.GetZ(), 0, 0, 0, 1);
	_cameraMatrix = cameraX * cameraY * cameraZ * cameraPosition;
	return _cameraMatrix;
}