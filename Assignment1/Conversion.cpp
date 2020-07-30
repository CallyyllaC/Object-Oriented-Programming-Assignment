/**
Author: Callum Dyson-Gainsborough
Date Created: 9/12/18
Date Last Changed: 9/12/18
Last Change: Created
**/

#include "Conversion.h"
#include <algorithm>

//Constructor
Conversion::Conversion()
{
}

//Destructor
Conversion::~Conversion()
{
}

//works out the quartiles of an array
void Stats(File a, Conversion b, double *arr, int len, double *output)
{
	//create a copy off the array and sort
	auto tmp = new double[len];
	std::copy(arr, arr + len, tmp);
	std::sort(tmp, tmp + len);

	//Get and Set the quartiles

	//median
	int loc = len / 2;
	output[0] = tmp[loc];
	//upper
	loc = (len / 4) + (len / 2);
	output[1] = tmp[loc];
	//lower
	loc = len / 4;
	output[2] = tmp[loc];

	//Delete the copy
	delete[] tmp;
}

//converts grayscale pixel to heatmap colour pixels
void Convert(File a, Conversion b, double* &arr, double pixel, double* stats)
{
	//Get the stats
	double median = stats[0];
	double upper = stats[1];
	double lower = stats[2];

	//Set the multiplier
	const int multiplier = 15;

	//Calculate the red
	if (pixel < lower)
	{
		arr[0] = 1;
	}
	else if (pixel > median)
	{
		arr[0] = 1 - ((pixel - lower) * multiplier);
	}
	else
	{
		arr[0] = 0;
	}

	//Calculate the green
	if (pixel < lower)
	{
		arr[1] = pixel * multiplier;
	}
	else if (pixel > upper)
	{
		arr[1] = 1 - ((pixel - upper) * multiplier);
	}
	else
	{
		arr[1] = 1;
	}

	//Calculate the blue
	if (pixel > median)
	{
		if (pixel < upper)
		{
			arr[2] = (pixel - median) * multiplier;
		}
		else
		{
			arr[2] = 1;
		}

	}

	//set the values to be used and convert them into 255 pixels
	arr[0] = arr[0] * 255;
	arr[1] = arr[1] * 255;
	arr[2] = arr[2] * 255;

}
