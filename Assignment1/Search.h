/**
Author: Callum Dyson-Gainsborough
Date Created: 10/11/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#pragma once
#include "Image.h"
#include "Image.h"
#include "SearchContainer.h"
#include <vector>

class Search
{

public:
	//structors
	Search();
	~Search();

	//prints percentage complete to the console
	void PercentComplete(int percentage);

	//calculates the percentage
	int percent(int score, int maxScore);

	//Sum of Absoloute Difference based search, finds top 10 closest matches
	void SADSearch(Image *lImage, Image *rImage, int returns, int accuracy = 0);

	//Find minimum value in an array
	double FindMin(double *arr, int size);

	//Find maximum value in an array
	double FindMax(double *arr, int size);

	//Draw Wally results to the image 
	void DrawFoundLocationGrids(Image &lImage, Image &rImage, std::vector<SearchContainer> &results);

};

