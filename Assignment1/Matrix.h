/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#pragma once

class Matrix
{
	
public:
	//structors
	Matrix();
	Matrix(int x, int y, double *data);
	Matrix(int x, int y);
	~Matrix();
	Matrix operator+(const Matrix& m);

	Matrix operator-(const Matrix & m);

	Matrix operator=(const Matrix & m);


	//define access functions
	double* Get();
	double GetValue(int x, int y);
	void SetValue(int x, int y, double value);

private:
	//define array
	double *matrix = nullptr;
	//can be deleted?
	bool deleteable = false;

	//store x and y
	int width;
	int height;
};