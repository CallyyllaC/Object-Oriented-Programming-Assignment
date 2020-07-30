/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#pragma once
#include "Matrix.h"
#include "File.h"

class Base : public File
{

public:
	//structors
	Base();
	Base(char *fileName, int x, int y, double *data);
	Base(int x, int y);
	~Base();

	//define access functions
	int Width();
	int Height();

	//Define Image stored as matrix
	Matrix image;

protected:
	//Define variables to hold image size
	int x;
	int y;

};

