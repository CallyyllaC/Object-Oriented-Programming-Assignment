/**
Author: Callum Dyson-Gainsborough
Date Created: 9/12/18
Date Last Changed: 9/12/18
Last Change: Created
**/

#pragma once
#include "File.h"

class File;

class Conversion
{
public:
	//Friend functions
	//convert to heatmap
	friend void Convert(File a, Conversion b, double* &arr, double pixel, double* stats);
	//GetStats
	friend void Stats(File a, Conversion b, double *arr, int len, double *output);

	//structors
	Conversion();
	~Conversion();
};

