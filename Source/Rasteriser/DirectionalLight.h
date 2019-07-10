#pragma once
#include "Vector.h"

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(int red, int green, int blue, Vector direction);
	DirectionalLight(const DirectionalLight &rhs);
	~DirectionalLight();

	int GetRed() const;
	void SetRed(const int red);
	int GetGreen() const;
	void SetGreen(const int green);
	int GetBlue() const;
	void SetBlue(const int blue);
	Vector GetDirection() const;
	void SetDirection(const Vector &direction);

	DirectionalLight& operator=(const DirectionalLight &rhs);

private:
	int _red;
	int _green;
	int _blue;
	Vector _direction;
};