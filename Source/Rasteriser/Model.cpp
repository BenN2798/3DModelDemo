#include "Model.h"
#include <algorithm>

bool SortByZDepth(Polygon3D elem1, Polygon3D elem2)
{
	return elem1.GetZDepth() > elem2.GetZDepth();
}

Model::Model()
{
	kaRed = 1.0f;
	kaGreen = 1.0f;
	kaBlue = 1.0f;
	kdRed = 1.0f;
	kdGreen = 1.0f;
	kdBlue = 1.0f;
	ksRed = 1.0f;
	ksGreen = 1.0f;
	ksBlue = 1.0f;
}

Model::~Model()
{
}

std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

std::vector<Vertex>& Model::GetVertices()
{
	return _verticesTransform;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex _vertex(x, y, z, 1);
	_vertices.push_back(_vertex);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D _polygon(i0, i1, i2);
	_polygons.push_back(_polygon);
}

void Model::ApplyTransformToLocalVertices(const Matrix &transform)
{
	_verticesTransform.clear();
	int size = int(_vertices.size());
	for (int i = 0; i < size; i++)
	{
		_verticesTransform.push_back(transform * _vertices[i]);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix &transform)
{
	int size = int(_verticesTransform.size());
	for (int i = 0; i < size; i++)
	{
		_verticesTransform[i] = transform * _verticesTransform[i];
	}
}

void Model::DehomoginizeVertices()
{
	int size = int(_verticesTransform.size());
	for (int i = 0; i < size; i++)
	{
		_verticesTransform[i] = _verticesTransform[i].dehomoginize(_verticesTransform[i]);
	}
}

void Model::CalculateBackFaces(const Vertex &cameraPosition)
{
	int size = int(_polygons.size());
	Vector a(0, 0, 0);
	Vector b(0, 0, 0);
	Vector crossProduct(0, 0, 0);
	Vector normal(0, 0, 0);
	Vector eye(0, 0, 0);
	float dotProduct = 0;
	float length = 0;
	int indeces[3] = { 0, 0, 0 };
	for (int i = 0; i < size; i++)
	{
		indeces[0] = _polygons[i].GetIndex(0);
		indeces[1] = _polygons[i].GetIndex(1);
		indeces[2] = _polygons[i].GetIndex(2);
		a = _verticesTransform[indeces[1]] - _verticesTransform[indeces[0]];
		b = _verticesTransform[indeces[2]] - _verticesTransform[indeces[0]];
		crossProduct = b.GetCrossProduct(b, a);
		length = crossProduct.GetLength(crossProduct);
		normal = crossProduct.Normalise(crossProduct, length);
		_polygons[i].SetNormal(normal);
		eye = _vertices[indeces[0]] - cameraPosition;
		dotProduct = normal.GetDotProduct(normal, eye);
		if (dotProduct < 0)
		{
			_polygons[i].SetCull(true);
		}
		else
		{
			_polygons[i].SetCull(false);
		}
	}
}

void Model::Sort()
{
	int size = int(_polygons.size());
	float zDepth = 0.00;
	std::vector<Vertex> polygonVertices;
	polygonVertices.clear();
	Vertex polygonVertex(0, 0, 0, 1);
	for (int i = 0; i < size; i++)
	{
		polygonVertices.clear();
		for (int j = 0; j < 3; j++)
		{
			polygonVertex = _verticesTransform[_polygons[i].GetIndex(j)];
			polygonVertices.push_back(polygonVertex);
		}
		zDepth = (polygonVertices[0].GetZ() + polygonVertices[1].GetZ() + polygonVertices[2].GetZ()) / 3;
		_polygons[i].SetZDepth(zDepth);
	}
	std::sort(_polygons.begin(), _polygons.end(), SortByZDepth);
}

void Model::CalculateLightingAmbient(const AmbientLight &light)
{
	int polygonSize = (int)_polygons.size();
	float totalRed = 0;
	float totalGreen = 0;
	float totalBlue = 0;
	float tempRed = 0;
	float tempGreen = 0;
	float tempBlue = 0;
	for (int i = 0; i < polygonSize; i++)
	{
		totalRed = 0;
		totalGreen = 0;
		totalBlue = 0;
		tempRed = float(light.GetRed());
		tempGreen = float(light.GetGreen());
		tempBlue = float(light.GetBlue());
		tempRed = tempRed * kaRed;
		tempGreen = tempGreen * kaGreen;
		tempBlue = tempBlue * kaBlue;
		totalRed = totalRed + tempRed;
		totalGreen = totalGreen + tempGreen;
	    totalBlue = totalBlue + tempBlue;
		if (totalRed > 255)
		{
			totalRed = 255;
		}
		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		if (totalBlue > 255)
		{
			totalBlue = 255;
		}
		COLORREF totalColour = RGB(totalRed, totalGreen, totalBlue);
		_polygons[i].SetColour(totalColour);
	}
}

void Model::CalculateLightingDirectional(const std::vector<DirectionalLight> &lights)
{
	int polygonSize = (int)_polygons.size();
	int lightSize = (int)lights.size();
	float totalRed = 0;
	float totalGreen = 0;
	float totalBlue = 0;
	float tempRed = 0;
	float tempGreen = 0;
	float tempBlue = 0;
	float dotProduct = 0.0f;
	float lightLength = 0.0f;
	Vector direction = Vector();
	Vector lightNormal = Vector();
	for (int i = 0; i < polygonSize; i++)
	{
		totalRed = GetRValue(_polygons[i].GetColour());
		totalGreen = GetGValue(_polygons[i].GetColour());
		totalBlue = GetBValue(_polygons[i].GetColour());
		for (int j = 0; j < lightSize; j++)
		{
			tempRed = float(lights[j].GetRed());
			tempGreen = float(lights[j].GetGreen());
			tempBlue = float(lights[j].GetBlue());
			tempRed = tempRed * kdRed;
			tempGreen = tempGreen * kdGreen;
			tempBlue = tempBlue * kdBlue;
			direction = lights[j].GetDirection();
			lightLength = direction.GetLength(direction);
			lightNormal = direction.Normalise(direction, lightLength);
			dotProduct = lightNormal.GetDotProduct(lightNormal, _polygons[i].GetNormal());
			tempRed = tempRed * dotProduct;
			tempGreen = tempGreen * dotProduct;
			tempBlue = tempBlue * dotProduct;
			totalRed = totalRed + tempRed;
			totalGreen = totalGreen + tempGreen;
			totalBlue = totalBlue + tempBlue;
		}
		if (totalRed > 255)
		{
			totalRed = 255;
		}
		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		if (totalBlue > 255)
		{
			totalBlue = 255;
		}
		COLORREF totalColour = RGB(totalRed, totalGreen, totalBlue);
		_polygons[i].SetColour(totalColour);
	}
}

void Model::CalculateLightingPoint(const std::vector<PointLight> &lights)
{
	int polygonSize = (int)_polygons.size();
	int lightSize = (int)lights.size();
	float totalRed = 0;
	float totalGreen = 0;
	float totalBlue = 0;
	float tempRed = 0;
	float tempGreen = 0;
	float tempBlue = 0;
	float dotProduct = 0.0f;
	float lightLength = 0.0f;
	float attenuation = 0.0f;
	Vector direction = Vector();
	Vector lightNormal = Vector();
	for (int i = 0; i < polygonSize; i++)
	{
		totalRed = GetRValue(_polygons[i].GetColour());
		totalGreen = GetGValue(_polygons[i].GetColour());
		totalBlue = GetBValue(_polygons[i].GetColour());
		for (int j = 0; j < lightSize; j++)
		{
			tempRed = float(lights[j].GetRed());
			tempGreen = float(lights[j].GetGreen());
			tempBlue = float(lights[j].GetBlue());
			tempRed = tempRed * kdRed;
			tempGreen = tempGreen * kdGreen;
			tempBlue = tempBlue * kdBlue;
			direction = _verticesTransform[_polygons[i].GetIndex(0)] - lights[j].GetPosition();
			lightLength = direction.GetLength(direction);
			attenuation = lights[j].GetAttenuation(lightLength);
			lightNormal = direction.Normalise(direction, lightLength);
			dotProduct = lightNormal.GetDotProduct(lightNormal, _polygons[i].GetNormal());
			tempRed = tempRed * dotProduct;
			tempGreen = tempGreen * dotProduct;
			tempBlue = tempBlue * dotProduct;
			tempRed = tempRed * attenuation;
			tempGreen = tempGreen * attenuation;
			tempBlue = tempBlue * attenuation;
			totalRed = totalRed + tempRed;
			totalGreen = totalGreen + tempGreen;
			totalBlue = totalBlue + tempBlue;
		}
		if (totalRed > 255)
		{
			totalRed = 255;
		}
		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		if (totalBlue > 255)
		{
			totalBlue = 255;
		}
		COLORREF totalColour = RGB(totalRed, totalGreen, totalBlue);
		_polygons[i].SetColour(totalColour);
	}
}
