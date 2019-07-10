#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indeces[0] = 0;
	_indeces[1] = 1;
	_indeces[2] = 2;
	_zDepth = 0.00;
	_cullPolygon = false;
	_normal = Vector(0, 0, 0);
	_colour = RGB(0, 0, 0);
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indeces[0] = index0;
	_indeces[1] = index1;
	_indeces[2] = index2;
	_zDepth = 0.00;
	_cullPolygon = false;
	_normal = Vector(0, 0, 0);
	_colour = RGB(0, 0, 0);
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indeces[0] = p.GetIndex(0);
	_indeces[1] = p.GetIndex(1);
	_indeces[2] = p.GetIndex(2);
	_zDepth = p.GetZDepth();
	_cullPolygon = p.GetCull();
	_normal = p.GetNormal();
	_colour = p.GetColour();
}

int Polygon3D::GetIndex(int i) const
{
	return _indeces[i];
}

float Polygon3D::GetZDepth() const
{
	return _zDepth;
}

void Polygon3D::SetZDepth(const float zDepth)
{
	_zDepth = zDepth;
}

bool Polygon3D::GetCull() const
{
	return _cullPolygon;
}

void Polygon3D::SetCull(const bool &cull)
{
	_cullPolygon = cull;
}

Vector Polygon3D::GetNormal() const
{
	return _normal;
}

void Polygon3D::SetNormal(const Vector &normal)
{
	_normal = normal;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;
}

void Polygon3D::SetColour(const COLORREF colour)
{
	_colour = colour;
}

Polygon3D& Polygon3D::operator= (const Polygon3D &rhs)
{
	if (this != &rhs)
	{
		_indeces[0] = rhs.GetIndex(0);
		_indeces[1] = rhs.GetIndex(1);
		_indeces[2] = rhs.GetIndex(2);
		_zDepth = rhs.GetZDepth();
		_cullPolygon = rhs.GetCull();
		_normal = rhs.GetNormal();
		_colour = rhs.GetColour();
	}
	return *this;
}