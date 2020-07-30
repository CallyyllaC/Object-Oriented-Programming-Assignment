/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#include "Globals.h"
#include "Matrix.h"
#include <array>
#include <iostream>

//Constructor
Matrix::Matrix()
{
}

//Constructor that takes in size and data
Matrix::Matrix(int x, int y, double *data)
{
	//store the width, height and image data, and mark as non destructable
	width = x;
	height = y;
	matrix = data;
	deleteable = false;
}

//Constructor that only takes in size
Matrix::Matrix(int x, int y)
{
	//store the width, height, create an empty image array, and mark as destructable
	width = x;
	height = y;
	matrix = new double[x*y];
	deleteable = false;

	//fill image array with 0's
	for (int i = 0; i < x*y; i++)
	{
		matrix[i] = 0;
	}
}

//Destructor
Matrix::~Matrix()
{
	if (global_debug)
		std::cout << "Matrix destroyed" << std::endl;

	if (deleteable)
	{
		delete[] matrix;

		if (global_debug)
			std::cout << "Delete Called" << std::endl;
	}
}

Matrix Matrix::operator+(const Matrix & m)
{
	Matrix newM = Matrix(this->width, this->height);
	newM.deleteable = this->deleteable;
	newM.matrix = new double[width*height];
	for (int i = 0; i < (this->width*this->height); i++)
	{
		newM.matrix[i] = this->matrix[i] + m.matrix[i];
	}
	return newM;
}

Matrix Matrix::operator-(const Matrix & m)
{
	Matrix newM = Matrix(this->width, this->height);
	newM.deleteable = this->deleteable;
	newM.matrix = new double[width*height];
	for (int i = 0; i < (this->width*this->height); i++)
	{
		newM.matrix[i] = this->matrix[i] - m.matrix[i];
	}
	return newM;
}

Matrix Matrix::operator=(const Matrix & m)
{
	Matrix newM = Matrix(m.width, m.height);
	newM.deleteable = m.deleteable;
	newM.matrix = new double[width*height];

	for (int i = 0; i < (m.width*m.height); i++)
	{
		newM.matrix[i] = m.matrix[i];
	}

	return newM;
}

//return the matrix
double* Matrix::Get()
{
	return matrix;
}

//return the value at a given position in the matrix
double Matrix::GetValue(int x, int y)
{
	return matrix[(width * y) + x];
}

//Change the value at a given position in the matrix
void Matrix::SetValue(int x, int y, double value)
{
	matrix[(width * y) + x] = value;
}


