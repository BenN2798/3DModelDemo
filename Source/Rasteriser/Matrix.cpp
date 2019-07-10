#include "Matrix.h"

Matrix::Matrix()
{
	_matrix[0][0] = 1.0f;
	_matrix[0][1] = 0.0f;
	_matrix[0][2] = 0.0f;
	_matrix[0][3] = 0.0f;
	_matrix[1][0] = 0.0f;
	_matrix[1][1] = 1.0f;
	_matrix[1][2] = 0.0f;
	_matrix[1][3] = 0.0f;
	_matrix[2][0] = 0.0f;
	_matrix[2][1] = 0.0f;
	_matrix[2][2] = 1.0f;
	_matrix[2][3] = 0.0f;
	_matrix[3][0] = 0.0f;
	_matrix[3][1] = 0.0f;
	_matrix[3][2] = 0.0f;
	_matrix[3][3] = 1.0f;
}

Matrix::Matrix(float one, float two, float three, float four, float five, float six, float seven, float eight, float nine,
	float ten, float eleven, float twelve, float thirteen, float fourteen, float fifteen, float sixteen)
{
	_matrix[0][0] = one;
	_matrix[0][1] = two;
	_matrix[0][2] = three;
	_matrix[0][3] = four;
	_matrix[1][0] = five;
	_matrix[1][1] = six;
	_matrix[1][2] = seven;
	_matrix[1][3] = eight;
	_matrix[2][0] = nine;
	_matrix[2][1] = ten;
	_matrix[2][2] = eleven;
	_matrix[2][3] = twelve;
	_matrix[3][0] = thirteen;
	_matrix[3][1] = fourteen;
	_matrix[3][2] = fifteen;
	_matrix[3][3] = sixteen;
}

Matrix::Matrix(const Matrix& other)
{
	_matrix[0][0] = other.GetM(0, 0);
	_matrix[0][1] = other.GetM(0, 1);
	_matrix[0][2] = other.GetM(0, 2);
	_matrix[0][3] = other.GetM(0, 3);
	_matrix[1][0] = other.GetM(1, 0);
	_matrix[1][1] = other.GetM(1, 1);
	_matrix[1][2] = other.GetM(1, 2);
	_matrix[1][3] = other.GetM(1, 3);
	_matrix[2][0] = other.GetM(2, 0);
	_matrix[2][1] = other.GetM(2, 1);
	_matrix[2][2] = other.GetM(2, 2);
	_matrix[2][3] = other.GetM(2, 3);
	_matrix[3][0] = other.GetM(3, 0);
	_matrix[3][1] = other.GetM(3, 1);
	_matrix[3][2] = other.GetM(3, 2);
	_matrix[3][3] = other.GetM(3, 3);
}

Matrix::~Matrix()
{
}

float Matrix::GetM(const int row, const int column) const
{
	return _matrix[row][column];
}

void Matrix::SetM(const int row, const int column, const float value)
{
	_matrix[row][column] = value;
}

Matrix& Matrix::operator= (const Matrix &rhs)
{
	if (this != &rhs)
	{
		_matrix[0][0] = rhs.GetM(0, 0);
		_matrix[0][1] = rhs.GetM(0, 1);
		_matrix[0][2] = rhs.GetM(0, 2);
		_matrix[0][3] = rhs.GetM(0, 3);
		_matrix[1][0] = rhs.GetM(1, 0);
		_matrix[1][1] = rhs.GetM(1, 1);
		_matrix[1][2] = rhs.GetM(1, 2);
		_matrix[1][3] = rhs.GetM(1, 3);
		_matrix[2][0] = rhs.GetM(2, 0);
		_matrix[2][1] = rhs.GetM(2, 1);
		_matrix[2][2] = rhs.GetM(2, 2);
		_matrix[2][3] = rhs.GetM(2, 3);
		_matrix[3][0] = rhs.GetM(3, 0);
		_matrix[3][1] = rhs.GetM(3, 1);
		_matrix[3][2] = rhs.GetM(3, 2);
		_matrix[3][3] = rhs.GetM(3, 3);
	}

	return *this;
}

const Matrix Matrix::operator*(const Matrix &other) const
{
	float _one = (_matrix[0][0] * other.GetM(0,0)) + (_matrix[0][1] * other.GetM(1, 0)) + (_matrix[0][2] * other.GetM(2, 0)) + (_matrix[0][3] * other.GetM(3, 0));
	float _two = (_matrix[0][0] * other.GetM(0, 1)) + (_matrix[0][1] * other.GetM(1, 1)) + (_matrix[0][2] * other.GetM(2, 1)) + (_matrix[0][3] * other.GetM(3, 1));
	float _three = (_matrix[0][0] * other.GetM(0, 2)) + (_matrix[0][1] * other.GetM(1, 2)) + (_matrix[0][2] * other.GetM(2, 2)) + (_matrix[0][3] * other.GetM(3, 2));
	float _four = (_matrix[0][0] * other.GetM(0, 3)) + (_matrix[0][1] * other.GetM(1, 3)) + (_matrix[0][2] * other.GetM(2, 3)) + (_matrix[0][3] * other.GetM(3, 3));
	float _five = (_matrix[1][0] * other.GetM(0, 0)) + (_matrix[1][1] * other.GetM(1, 0)) + (_matrix[1][2] * other.GetM(2, 0)) + (_matrix[1][3] * other.GetM(3, 0));
	float _six = (_matrix[1][0] * other.GetM(0, 1)) + (_matrix[1][1] * other.GetM(1, 1)) + (_matrix[1][2] * other.GetM(2, 1)) + (_matrix[1][3] * other.GetM(3, 1));
	float _seven = (_matrix[1][0] * other.GetM(0, 2)) + (_matrix[1][1] * other.GetM(1, 2)) + (_matrix[1][2] * other.GetM(2, 2)) + (_matrix[1][3] * other.GetM(3, 2));
	float _eight = (_matrix[1][0] * other.GetM(0, 3)) + (_matrix[1][1] * other.GetM(1, 3)) + (_matrix[1][2] * other.GetM(2, 3)) + (_matrix[1][3] * other.GetM(3, 3));
	float _nine = (_matrix[2][0] * other.GetM(0, 0)) + (_matrix[2][1] * other.GetM(1, 0)) + (_matrix[2][2] * other.GetM(2, 0)) + (_matrix[2][3] * other.GetM(3, 0));
	float _ten = (_matrix[2][0] * other.GetM(0, 1)) + (_matrix[2][1] * other.GetM(1, 1)) + (_matrix[2][2] * other.GetM(2, 1)) + (_matrix[2][3] * other.GetM(3, 1));
	float _eleven = (_matrix[2][0] * other.GetM(0, 2)) + (_matrix[2][1] * other.GetM(1, 2)) + (_matrix[2][2] * other.GetM(2, 2)) + (_matrix[2][3] * other.GetM(3, 2));
	float _twelve = (_matrix[2][0] * other.GetM(0, 3)) + (_matrix[2][1] * other.GetM(1, 3)) + (_matrix[2][2] * other.GetM(2, 3)) + (_matrix[2][3] * other.GetM(3, 3));
	float _thirteen = (_matrix[3][0] * other.GetM(0, 0)) + (_matrix[3][1] * other.GetM(1, 0)) + (_matrix[3][2] * other.GetM(2, 0)) + (_matrix[3][3] * other.GetM(3, 0));
	float _fourteen = (_matrix[3][0] * other.GetM(0, 1)) + (_matrix[3][1] * other.GetM(1, 1)) + (_matrix[3][2] * other.GetM(2, 1)) + (_matrix[3][3] * other.GetM(3, 1));
	float _fifteen = (_matrix[3][0] * other.GetM(0, 2)) + (_matrix[3][1] * other.GetM(1, 2)) + (_matrix[3][2] * other.GetM(2, 2)) + (_matrix[3][3] * other.GetM(3, 2));
	float _sixteen = (_matrix[3][0] * other.GetM(0, 3)) + (_matrix[3][1] * other.GetM(1, 3)) + (_matrix[3][2] * other.GetM(2, 3)) + (_matrix[3][3] * other.GetM(3, 3));
	Matrix result(_one, _two, _three, _four, _five, _six, _seven, _eight, _nine, _ten, _eleven, _twelve, _thirteen, _fourteen, _fifteen, _sixteen);

	return result;
}

const Vertex Matrix::operator*(const Vertex &other) const
{
	float _x = (_matrix[0][0] * other.GetX()) + (_matrix[0][1] * other.GetY()) + (_matrix[0][2] * other.GetZ()) + (_matrix[0][3] * other.GetW());
	float _y = (_matrix[1][0] * other.GetX()) + (_matrix[1][1] * other.GetY()) + (_matrix[1][2] * other.GetZ()) + (_matrix[1][3] * other.GetW());
	float _z = (_matrix[2][0] * other.GetX()) + (_matrix[2][1] * other.GetY()) + (_matrix[2][2] * other.GetZ()) + (_matrix[2][3] * other.GetW());
	float _w = (_matrix[3][0] * other.GetX()) + (_matrix[3][1] * other.GetY()) + (_matrix[3][2] * other.GetZ()) + (_matrix[3][3] * other.GetW());
	Vertex result(_x, _y, _z, _w);

	return result;
};