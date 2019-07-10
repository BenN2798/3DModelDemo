#include "Rasteriser.h"
#include <algorithm>

Rasteriser app;

bool SortByYValue(Vertex elem1, Vertex elem2)
{
	return elem1.GetY() < elem2.GetY();
}

bool Rasteriser::Initialise()
{
    _angle = 0.0f;
	count = 0;
	scale = 0.0f;
	translateX = 0.0f;
	translateY = 0.0f;
	translateZ = 0.0f;
	_ambientLight = AmbientLight(0, 127, 127);
	DirectionalLight dLight(0, 127, 127, Vector(0, -50, 0));
	_directionalLights.push_back(dLight);
	PointLight pLight(50, 0, 0, 0.0f, 1.0f, 0.0f, Vertex(2, 1, 0, 1));
	_pointLights.push_back(pLight);
	if (!MD2Loader::LoadModel("teapot.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Rasteriser::Update(Bitmap &bitmap)
{
	count += 1;
	_angle += 0.025f;
	if (count > 3000)
	{
		count = 0;
		scale = 0.0f;
		translateX = 0.0f;
		translateY = 0.0f;
		translateZ = 0.0f;
	}
	if (count <= 1800)
	{
		_worldMatrix = Matrix(cos(_angle), 0, -sin(_angle), 0, 0, 1, 0, 0, sin(_angle), 0, cos(_angle), 0, 0, 0, 0, 1);
	}
	else if (count > 1800 && count <= 2100)
	{
		_worldMatrix = Matrix(1, 0, 0, 0, 0, cos(_angle), sin(_angle), 0, 0, -sin(_angle), cos(_angle), 0, 0, 0, 0, 1);
	}
	else if (count > 2100 && count <= 2400)
	{
		_worldMatrix = Matrix(cos(_angle), sin(_angle), 0, 0, -sin(_angle), cos(_angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}
	else if (count > 2400 && count <= 2700)
	{
		scale += 0.01f;
		_worldMatrix = Matrix(scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, 1);
	}
	else
	{
		if (count <= 2800)
		{
			translateX += 0.1f;
			_worldMatrix = Matrix(1, 0, 0, translateX, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		}
		else if (count > 2800 && count <= 2900)
		{
			translateY += 0.1f;
			_worldMatrix = Matrix(1, 0, 0, 0, 0, 1, 0, translateY, 0, 0, 1, 0, 0, 0, 0, 1);
		}
		else
		{
			translateZ += 0.1f;
			_worldMatrix = Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, translateZ, 0, 0, 0, 1);
		}
	}
	float d = 5.0f;
	float aspectRatio = float(bitmap.GetWidth()) / float(bitmap.GetHeight());
	GeneratePerspectiveMatrix(d, aspectRatio);
	GenerateViewMatrix(d, bitmap.GetWidth(), bitmap.GetHeight());
}

void Rasteriser::Render(Bitmap &bitmap)
{
	_model.ApplyTransformToLocalVertices(_worldMatrix);
	Vertex cameraPosition(0, 0, -50, 1);
	_camera.SetPosition(cameraPosition);
	_model.CalculateBackFaces(cameraPosition);
	if (count > 600)
	{
		_model.CalculateLightingAmbient(_ambientLight);
	}
	if (count > 900)
	{
		_model.CalculateLightingDirectional(_directionalLights);
	}
	if (count > 1200)
	{
		_model.CalculateLightingPoint(_pointLights);
	}
	_cameraMatrix = _camera.GetCameraMatrix();
	_model.ApplyTransformToTransformedVertices(_cameraMatrix);
	_model.Sort();
    _model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
	_model.DehomoginizeVertices();
	_model.ApplyTransformToTransformedVertices(_viewMatrix);
	bitmap.Clear(RGB(0, 0, 0));
	if (count <= 600)
	{
		DrawWireFrame(bitmap);
	}
	else if (count > 600 && count <= 1500)
	{
		DrawSolidFlat(bitmap);
	}
	else
	{
		MyDrawSolidFlat(bitmap);
	}
	LPCTSTR displayString = GetDisplayString();
	LPCTSTR transformString = GetTransformString();
	DrawString(bitmap, displayString, transformString);
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	Matrix _perspective(d / aspectRatio, 0, 0, 0, 0, d, 0, 0, 0, 0, d, 0, 0, 0, 1, 0);
	_perspectiveMatrix = _perspective;
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	Matrix _screen(float(width) / 2, 0, 0, float(width) / 2, 0, float(-height) / 2, 0, float(height) / 2, 0, 0, d / 2, d / 2, 0, 0, 0, 1);
	_viewMatrix = _screen;
}

void Rasteriser::DrawWireFrame(Bitmap &bitmap)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);
	std::vector<Polygon3D> _polygons = _model.GetPolygons();
	std::vector<Vertex> _vertices = _model.GetVertices();
	if (count <= 300)
	{
		for (int i = 0; i < _polygons.size(); i++)
		{
			MoveToEx(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(0)].GetX()), int(_vertices[_polygons[i].GetIndex(0)].GetY()), NULL);
			LineTo(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(1)].GetX()), int(_vertices[_polygons[i].GetIndex(1)].GetY()));
			LineTo(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(2)].GetX()), int(_vertices[_polygons[i].GetIndex(2)].GetY()));
			LineTo(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(0)].GetX()), int(_vertices[_polygons[i].GetIndex(0)].GetY()));
		}
	}
	else
	{
		for (int i = 0; i < _polygons.size(); i++)
		{
			if (_polygons[i].GetCull() != true)
			{
				MoveToEx(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(0)].GetX()), int(_vertices[_polygons[i].GetIndex(0)].GetY()), NULL);
				LineTo(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(1)].GetX()), int(_vertices[_polygons[i].GetIndex(1)].GetY()));
				LineTo(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(2)].GetX()), int(_vertices[_polygons[i].GetIndex(2)].GetY()));
				LineTo(bitmap.GetDC(), int(_vertices[_polygons[i].GetIndex(0)].GetX()), int(_vertices[_polygons[i].GetIndex(0)].GetY()));
			}
		}
	}
	SelectObject(bitmap.GetDC(), oldPen);
	DeleteObject(hPen);
}

void Rasteriser::DrawSolidFlat(Bitmap &bitmap)
{
	COLORREF polygonColour = RGB (0, 0, 0);
	std::vector<Polygon3D> _polygons = _model.GetPolygons();
	std::vector<Vertex> _vertices = _model.GetVertices();
	POINT vertices[3];
	for (int i = 0; i < _polygons.size(); i++)
	{
		if (_polygons[i].GetCull() != true)
		{
			for (int j = 0; j < 3; j++)
			{
				vertices[j].x = (LONG)_vertices[_polygons[i].GetIndex(j)].GetX();
				vertices[j].y = (LONG)_vertices[_polygons[i].GetIndex(j)].GetY();
			}
			polygonColour = _polygons[i].GetColour();
			HPEN hPen = CreatePen(PS_SOLID, 1, polygonColour);
			HBRUSH hBrush = CreateSolidBrush(polygonColour);
			HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);
			HGDIOBJ oldBrush = SelectObject(bitmap.GetDC(), hBrush);
			Polygon(bitmap.GetDC(), vertices, 3);
			SelectObject(bitmap.GetDC(), oldPen);
			SelectObject(bitmap.GetDC(), oldBrush);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
	}
}

void Rasteriser::MyDrawSolidFlat(Bitmap &bitmap)
{
	COLORREF polygonColour = RGB(0, 0, 0);
	std::vector<Polygon3D> _polygons = _model.GetPolygons();
	std::vector<Vertex> _vertices = _model.GetVertices();
	Vertex vertices[3];
	for (int i = 0; i < _polygons.size(); i++)
	{
		if (_polygons[i].GetCull() != true)
		{
			for (int j = 0; j < 3; j++)
			{
				vertices[j] = _vertices[_polygons[i].GetIndex(j)];
			}
			polygonColour = _polygons[i].GetColour();
			FillPolygonFlat(bitmap, vertices, polygonColour);
		}
	}
}

void Rasteriser::FillPolygonFlat(Bitmap &bitmap, Vertex vertices[3], COLORREF colour)
{
	std::vector<Vertex>verticesSort;
	verticesSort.push_back(vertices[0]);
	verticesSort.push_back(vertices[1]);
	verticesSort.push_back(vertices[2]);

	sort(verticesSort.begin(), verticesSort.end(), SortByYValue);

	Vertex v1 = verticesSort[0];
	Vertex v2 = verticesSort[1];
	Vertex v3 = verticesSort[2];

	if (v2.GetY() == v3.GetY())
	{
		FillBottomFlat(bitmap, v1, v2, v3, colour);
	}
	else if (v1.GetY() == v2.GetY())
	{
		FillBottomFlat(bitmap, v1, v2, v3, colour);
	}
	else
	{
		Vertex v4 = Vertex(v1.GetX() + (v2.GetY() - v1.GetY()) / (v3.GetY() - v1.GetY()) * (v3.GetX() - v1.GetX()), v2.GetY(), 0, 1);
		FillBottomFlat(bitmap, v1, v2, v4, colour);
		FillTopFlat(bitmap, v2, v4, v3, colour);
	}
}

void Rasteriser::FillBottomFlat(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	float invSlope1 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());
	float invSlope2 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());

	float curX1 = v1.GetX();
	float curX2 = v1.GetX();
	
	HPEN hPen = CreatePen(PS_SOLID, 1, colour);
	HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);

	for (float scanLineY = v1.GetY(); scanLineY <= v2.GetY(); scanLineY++)
	{
		MoveToEx(bitmap.GetDC(), int(curX1), int(scanLineY), NULL);
		LineTo(bitmap.GetDC(), int(curX2), int(scanLineY));
		curX1 += invSlope1;
		curX2 += invSlope2;
	}
	SelectObject(bitmap.GetDC(), oldPen);
	DeleteObject(hPen);
	hPen = CreatePen(PS_SOLID, 2, colour);
	oldPen = SelectObject(bitmap.GetDC(), hPen);

	MoveToEx(bitmap.GetDC(), int(v1.GetX()), int(v1.GetY()), NULL);
	LineTo(bitmap.GetDC(), int(v2.GetX()), int(v2.GetY()));
	LineTo(bitmap.GetDC(), int(v3.GetX()), int(v3.GetY()));
	LineTo(bitmap.GetDC(), int(v1.GetX()), int(v1.GetY()));

	SelectObject(bitmap.GetDC(), oldPen);
	DeleteObject(hPen);
}

void Rasteriser::FillTopFlat(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	float invSlope1 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());
	float invSlope2 = (v3.GetX() - v2.GetX()) / (v3.GetY() - v2.GetY());

	float curX1 = v3.GetX();
	float curX2 = v3.GetX();

	HPEN hPen = CreatePen(PS_SOLID, 1, colour);
	HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);

	for (float scanLineY = v3.GetY(); scanLineY > v1.GetY(); scanLineY--)
	{
		MoveToEx(bitmap.GetDC(), int(curX1), int(scanLineY), NULL);
		LineTo(bitmap.GetDC(), int(curX2), int(scanLineY));
		curX1 -= invSlope1;
		curX2 -= invSlope2;
	}
	SelectObject(bitmap.GetDC(), oldPen);
	DeleteObject(hPen);
	hPen = CreatePen(PS_SOLID, 2, colour);
	oldPen = SelectObject(bitmap.GetDC(), hPen);

	MoveToEx(bitmap.GetDC(), int(v1.GetX()), int(v1.GetY()), NULL);
	LineTo(bitmap.GetDC(), int(v2.GetX()), int(v2.GetY()));
	LineTo(bitmap.GetDC(), int(v3.GetX()), int(v3.GetY()));
	LineTo(bitmap.GetDC(), int(v1.GetX()), int(v1.GetY()));

	SelectObject(bitmap.GetDC(), oldPen);
	DeleteObject(hPen);
}

void Rasteriser::DrawString(Bitmap &bitmap, LPCTSTR displayText, LPCTSTR transformText)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("display"));

	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		TextOut(hdc, 10, 10, displayText, lstrlen(displayText));
		TextOut(hdc, 10, 500, transformText, lstrlen(transformText));

		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}

LPCTSTR Rasteriser::GetDisplayString() const
{
	if (count <= 300)
	{
		return L"Wireframe";
	}
	else if (count > 300 && count <= 600)
	{
		return L"Wireframe with Backface Culling";
	}
	else if (count > 600 && count <= 900)
	{
		return L"Solid Shading with Ambient Light";
	}
	else if (count > 900 && count <= 1200)
	{
		return L"Directional Light Added";
	}
	else if (count > 1200 && count <= 1500)
	{
		return L"Point Light Added";
	}
	else
	{
		return L"Standard Algorithm Custom Polygon Fill";
	}
}

LPCTSTR Rasteriser::GetTransformString() const
{
	if (count <= 1800)
	{
		return L"Rotation on Y Axis";
	}
	else if (count > 1800 && count <= 2100)
	{
		return L"Rotation on X Axis";
	}
	else if (count > 2100 && count <= 2400)
	{
		return L"Rotation on Z Axis";
	}
	else if (count > 2400 && count <= 2700)
	{
		return L"Scaling";
	}
	else if (count > 2700 && count <= 2800)
	{
		return L"Translation on X Axis";
	}
	else if (count > 2800 && count <= 2900)
	{
		return L"Translation on Y Axis";
	}
	else
	{
		return L"Translation on Z Axis";
	}
}