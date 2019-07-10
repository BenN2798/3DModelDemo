#pragma once
#include "math.h"

class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& rhs);
	~Vector();

	void SetX(const float x);
	float GetX() const;
	void SetY(const float y);
	float GetY() const;
	void SetZ(const float z);
	float GetZ() const;
	static float GetDotProduct(const Vector& vector1, const Vector& vector2);
	static Vector GetCrossProduct(const Vector& vector1, const Vector& vector2);
	static float GetLength(const Vector& vector);
	static Vector Normalise(const Vector& vector, const float &length);

	Vector& operator=(const Vector& rhs);

private:
	float _x;
	float _y;
	float _z;
};