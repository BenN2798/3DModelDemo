#pragma once
#include "Vector.h"
#include "framework.h"

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	int GetIndex(int i) const;
	float GetZDepth() const;
	void SetZDepth(const float zDepth);
	bool GetCull() const;
	void SetCull(const bool &cull);
	Vector GetNormal() const;
	void SetNormal(const Vector &normal);
	COLORREF GetColour() const;
	void SetColour(const COLORREF colour);

	Polygon3D& operator= (const Polygon3D &rhs);

private:
	int _indeces[3];
	float _zDepth;
	bool _cullPolygon;
	Vector _normal;
	COLORREF _colour;
};