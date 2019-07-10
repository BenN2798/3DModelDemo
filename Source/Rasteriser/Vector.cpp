#include "Vector.h"

Vector::Vector()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector::Vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector::Vector(const Vector& rhs)
{
	_x = rhs.GetX();
	_y = rhs.GetY();
	_z = rhs.GetZ();
}

Vector::~Vector()
{
}

void Vector::SetX(const float x)
{
	_x = x;
}

float Vector::GetX() const
{
	return _x;
}

void Vector::SetY(const float y)
{
	_y = y; 
}

float Vector::GetY() const
{
	return _y;
}

void Vector::SetZ(const float z)
{
	_z = z;
}

float Vector::GetZ() const
{
	return _z;
}

float Vector::GetDotProduct(const Vector& vector1, const Vector& vector2)
{
	float dotProduct = (vector1.GetX() * vector2.GetX()) + (vector1.GetY() * vector2.GetY()) + (vector1.GetZ() * vector2.GetZ());
	return dotProduct;
}

Vector Vector::GetCrossProduct(const Vector& vector1, const Vector& vector2)
{
	float x = (vector1.GetY() * vector2.GetZ()) - (vector1.GetZ() * vector2.GetY());
	float y = (vector1.GetZ() * vector2.GetX()) - (vector1.GetX() * vector2.GetZ());
	float z = (vector1.GetX() * vector2.GetY()) - (vector1.GetY() * vector2.GetX());
	return Vector(x, y, z);
}

float Vector::GetLength(const Vector& vector)
{
	return float(sqrt((vector.GetX() * vector.GetX()) + (vector.GetY() * vector.GetY()) + (vector.GetZ() * vector.GetZ())));
}

Vector Vector::Normalise(const Vector& vector, const float& length)
{
	float x = vector.GetX() / length;
	float y = vector.GetY() / length;
	float z = vector.GetZ() / length;
	return Vector(x, y, z);
}

Vector& Vector::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
	}
	return *this;
}