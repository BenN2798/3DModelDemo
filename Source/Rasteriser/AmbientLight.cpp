#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
	_red = 255;
	_green = 255;
	_blue = 255;
}

AmbientLight::AmbientLight(int red, int green, int blue)
{
	_red = red;
	_green = green;
	_blue = blue;
}

AmbientLight::AmbientLight(const AmbientLight &rhs)
{
	_red = rhs.GetRed();
	_green = rhs.GetGreen();
	_blue = rhs.GetBlue();
}

AmbientLight::~AmbientLight()
{
}

int AmbientLight::GetRed() const
{
	return _red;
}

void AmbientLight::SetRed(const int red)
{
	_red = red;
}

int AmbientLight::GetGreen() const
{
	return _green;
}

void AmbientLight::SetGreen(const int green)
{
	_green = green;
}

int AmbientLight::GetBlue() const
{
	return _blue;
}

void AmbientLight::SetBlue(const int blue)
{
	_blue = blue;
}

AmbientLight& AmbientLight::operator=(const AmbientLight &rhs)
{
	if (this != &rhs)
	{
		_red = rhs.GetRed();
		_green = rhs.GetGreen();
		_blue = rhs.GetBlue();
	}
	return *this;
}