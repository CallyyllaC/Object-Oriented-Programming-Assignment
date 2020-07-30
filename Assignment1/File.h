/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#pragma once
#include "Conversion.h"
#include <fstream>
#include <iostream>

class Conversion;

class File
{

public:
	//convert to heatmap
	friend void Convert(File a, Conversion b, double* &arr, double pixel, double* stats);
	//GetStats
	friend void Stats(File a, Conversion b, double *arr, int len, double *output);

	//load the image
	virtual void read_text(char * fileName, int size, double* data);

	//save the image 
	virtual void write_pgm(char * filename, double * data, int sizeR, int sizeC, int Q = 255);

	//save the image 
	virtual void write_ppm(char * filename, double * data, int sizeR, int sizeC, int Q = 255);


};

