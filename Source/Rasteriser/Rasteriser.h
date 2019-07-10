#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "MD2Loader.h"
#include "Model.h"
#include "Camera.h"
#include "Polygon3D.h"
#include "Vector.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"

bool SortByYValue(Vertex elem1, Vertex elem2);

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(Bitmap &bitmap);
	void DrawSolidFlat(Bitmap &bitmap);
	void MyDrawSolidFlat(Bitmap &bitmap);
	void FillPolygonFlat(Bitmap &bitmap, Vertex vertices[3], COLORREF colour);
	void FillBottomFlat(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour);
	void FillTopFlat(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour);
	void DrawString(Bitmap &bitmap, LPCTSTR displayText, LPCTSTR transformText);
	LPCTSTR GetDisplayString() const;
	LPCTSTR GetTransformString() const;

private:
	Model _model;
	Camera _camera;
	Matrix _worldMatrix;
	Matrix _cameraMatrix;
	Matrix _perspectiveMatrix;
	Matrix _viewMatrix;
	float _angle;
	int count;
	float scale;
	float translateX;
	float translateY;
	float translateZ;
	AmbientLight _ambientLight;
	std::vector<DirectionalLight> _directionalLights;
	std::vector<PointLight> _pointLights;
};

