#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	_red = 255;
	_green = 255;
	_blue = 255;
	_direction = Vector();
}

DirectionalLight::DirectionalLight(int red, int green, int blue, Vector direction)
{
	_red = red;
	_green = green;
	_blue = blue;
	_direction = direction;
}

DirectionalLight::DirectionalLight(const DirectionalLight &rhs)
{
	_red = rhs.GetRed();
	_green = rhs.GetGreen();
	_blue = rhs.GetBlue();
	_direction = rhs.GetDirection();
}

DirectionalLight::~DirectionalLight()
{
}

int DirectionalLight::GetRed() const
{
	return _red;
}

void DirectionalLight::SetRed(const int red)
{
	_red = red;
}

int DirectionalLight::GetGreen() const
{
	return _green;
}

void DirectionalLight::SetGreen(const int green)
{
	_green = green;
}

int DirectionalLight::GetBlue() const
{
	return _blue;
}

void DirectionalLight::SetBlue(const int blue)
{
	_blue = blue;
}

Vector DirectionalLight::GetDirection() const
{
	return _direction;
}

void DirectionalLight::SetDirection(const Vector &direction)
{
	_direction = direction;
}

DirectionalLight& DirectionalLight::operator=(const DirectionalLight &rhs)
{
	if (this != &rhs)
	{
		_red = rhs.GetRed();
		_green = rhs.GetGreen();
		_blue = rhs.GetBlue();
		_direction = rhs.GetDirection();
	}
	return *this;
}