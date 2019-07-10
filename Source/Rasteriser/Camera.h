#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include "Math.h"

class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	~Camera();
	void SetXRotation(float i);
	void SetYRotation(float i);
	void SetZRotation(float i);
	void SetPosition(const Vertex& rhs);
	Matrix GetCameraMatrix();

private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;
	Matrix _cameraMatrix;
};