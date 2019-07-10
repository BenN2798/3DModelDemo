#pragma once
#include "Vertex.h"

class PointLight
{
public:
	PointLight();
	PointLight(int red, int green, int blue, float a, float b, float c, Vertex position);
	PointLight(const PointLight &rhs);
	~PointLight();

	int GetRed() const;
	void SetRed(const int red);
	int GetGreen() const;
	void SetGreen(const int green);
	int GetBlue() const;
	void SetBlue(const int blue);
	Vertex GetPosition() const;
	void SetPosition(const Vertex &position);
	float GetACoefficient() const;
	float GetBCoefficient() const;
	float GetCCoefficient() const;
	void SetAttenuationCoefficients(const float a, const float b, const float c);
	float GetAttenuation(const float length) const;

	PointLight& operator=(const PointLight &rhs);

private:
	int _red;
	int _green;
	int _blue;
	float _a;
	float _b;
	float _c;
	Vertex _position;
};