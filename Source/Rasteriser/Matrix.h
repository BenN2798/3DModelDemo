#pragma once
#include "Vertex.h"

class Matrix
{
public:
	// Default constructor
	Matrix();

	// Constructor that initialises all elements. Note that an initialiser
	// list is used to pass in the values. This is a new C++ feature.
	Matrix(float one, float two, float three, float four, float five, float six, float seven, float eight, float nine,
		float ten, float eleven, float twelve, float thirteen, float fourteen, float fifteen, float sixteen);

	// Copy constructor
	Matrix(const Matrix& other);

	// Destructor
	~Matrix();

	// Retrieve value in matrix at specified row and column
	float GetM(const int row, const int column) const;

	// Set value in matrix at specified row and column
	void SetM(const int row, const int column, const float value);

	// Copy assignment operator
	Matrix& operator= (const Matrix &rhs);

	// Multiply two matrices together
	const Matrix operator*(const Matrix &other) const;

	// Multiply a matrix by a vertex, returning a vertex
	const Vertex operator*(const Vertex &other) const;
private:
	float _matrix[4][4];
};