#include "PointLight.h"

PointLight::PointLight()
{
	_red = 255;
	_green = 255;
	_blue = 255;
	_position = Vertex();
	_a = 0.0f;
	_b = 1.0f;
	_c = 0.0f;
}

PointLight::PointLight(int red, int green, int blue, float a, float b, float c, Vertex position)
{
	_red = red;
	_green = green;
	_blue = blue;
	_position = position;
	_a = a;
	_b = b;
	_c = c;
}

PointLight::PointLight(const PointLight &rhs)
{
	_red = rhs.GetRed();
	_green = rhs.GetGreen();
	_blue = rhs.GetBlue();
	_position = rhs.GetPosition();
	_a = rhs.GetACoefficient();
	_b = rhs.GetBCoefficient();
	_c = rhs.GetCCoefficient();
}

PointLight::~PointLight()
{
}

int PointLight::GetRed() const
{
	return _red;
}

void PointLight::SetRed(const int red)
{
	_red = red;
}

int PointLight::GetGreen() const
{
	return _green;
}

void PointLight::SetGreen(const int green)
{
	_green = green;
}

int PointLight::GetBlue() const
{
	return _blue;
}

void PointLight::SetBlue(const int blue)
{
	_blue = blue;
}

Vertex PointLight::GetPosition() const
{
	return _position;
}

void PointLight::SetPosition(const Vertex &position)
{
	_position = position;
}

float PointLight::GetACoefficient() const
{
	return _a;
}

float PointLight::GetBCoefficient() const
{
	return _b;
}

float PointLight::GetCCoefficient() const
{
	return _c;
}

void PointLight::SetAttenuationCoefficients(const float a, const float b, const float c)
{
	_a = a;
	_b = b;
	_c = c;
}

float PointLight::GetAttenuation(const float length) const
{
	return 1/((_a + _b) * (length + _c) * (length*length));
}

PointLight& PointLight::operator=(const PointLight &rhs)
{
	if (this != &rhs)
	{
		_red = rhs.GetRed();
		_green = rhs.GetGreen();
		_blue = rhs.GetBlue();
		_position = rhs.GetPosition();
		_a = rhs.GetACoefficient();
		_b = rhs.GetBCoefficient();
		_c = rhs.GetCCoefficient();
	}
	return *this;
}