#pragma once
#include <vector>
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Vector.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"

bool SortByZDepth(Polygon3D elem1, Polygon3D elem2);

class Model
{
public:
	Model();
	~Model();

	std::vector<Polygon3D>& GetPolygons();
	std::vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);
	void DehomoginizeVertices();
	void CalculateBackFaces(const Vertex &cameraPosition);
	void Sort();
	void CalculateLightingAmbient(const AmbientLight &light);
	void CalculateLightingDirectional(const std::vector<DirectionalLight> &lights);
	void CalculateLightingPoint(const std::vector<PointLight> &lights);

private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _verticesTransform;
	float kaRed;
	float kaGreen;
	float kaBlue;
	float kdRed;
	float kdGreen;
	float kdBlue;
	float ksRed;
	float ksGreen;
	float ksBlue;
};