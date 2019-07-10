#pragma once

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(int red, int green, int blue);
	AmbientLight(const AmbientLight &rhs);
	~AmbientLight();

	int GetRed() const;
	void SetRed(const int red);
	int GetGreen() const;
	void SetGreen(const int green);
	int GetBlue() const;
	void SetBlue(const int blue);

	AmbientLight& operator=(const AmbientLight &rhs);

private:
	int _red;
	int _green;
	int _blue;
};