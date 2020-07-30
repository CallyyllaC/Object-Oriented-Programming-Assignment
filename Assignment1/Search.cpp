/**
Author: Callum Dyson-Gainsborough
Date Created: 10/11/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#include "Search.h"
#include "SearchContainer.h"
#include "Map.h"
#include <cmath>
#include <algorithm>
#include "Globals.h"

//Constructor
Search::Search()
{
}

//Destructor
Search::~Search()
{
	if (global_debug)
		std::cout << "Search destroyed" << std::endl;
}

//Calculate the percentage
int Search::percent(int score, int maxScore)
{
	return int(double(score) / double(maxScore) * 100);
}

//Print percentage to screen
void Search::PercentComplete(int percentage)
{
	std::cout << "\r" << percentage << "% completed.   " << std::flush;
}

//Search
void Search::SADSearch(Image *lImage, Image *rImage, const int returns, const int accuracy)
{
	std::cout << "Finding Wally..." << std::endl;

	//create a vector of the stored results
	std::vector<SearchContainer> results;

	//itterator
	std::vector<SearchContainer>::iterator it = results.begin();

	//holds the current results for found wallys
	int resultsSize = 0;

	//used to hold the current score and percentage of the search
	double dif = 0;
	int x = 0;

	//holds variables about the images and search accuracy to reduce amount of calls
	const int lwidth = lImage->Width();
	const int lheight = lImage->Height();
	const int rwidth = rImage->Width();
	const int rheight = rImage->Height();
	int hacc = 1;
	int wacc = 1;

	if (accuracy != 0)
	{
		hacc = rheight / accuracy;
		wacc = rwidth / accuracy;
	}

	//create a map holder and define the 
	int mapxc = 0;
	int mapyc = 0;
	const int mapx = lwidth / wacc;
	const int mapy = lheight / hacc;
	Map *map = new Map(mapx, mapy);


	//loop through the main image
	for (int i = 0; i < lwidth; i = i + wacc)
	{
		mapyc = 0;
		for (int j = 0; j < lheight; j = j + hacc)
		{
			//Print current percentage if higher than the last percentage
			int y = percent((i*j), (lwidth*lheight));
			if (x < y)
			{
				x = y;
				PercentComplete(x);
			}

			//reset the score
			dif = 0;

			//loop through the wally from this position
			for (int k = 0; k < rwidth; k++)
			{
				for (int l = 0; l < rheight; l++)
				{
					//get relative location
					int currentX = i + k;
					int currentY = j + l;

					//check if in the bounds of the image and ignore if ref image is 255
					if (currentX < lwidth && currentY < lheight && rImage->image.GetValue(k, l) != 255)
					{
						//get the absoloute value of the difference between the two pixels
						dif += std::abs((rImage->image.GetValue(k, l) - lImage->image.GetValue(currentX, currentY)));
					}
					else
					{
						//give max difference
						dif += 255;
					}
				}
			}
			//add score to map
			map->image.SetValue(mapxc, mapyc, percent(dif, 255*(rwidth*rheight)));

			//add result to the vector and increment
			results.push_back(SearchContainer(dif, i, j));
			++resultsSize;

			//once the results vector hits over x results go through and remove the highest score
			if (resultsSize > returns)
			{
				//max score container and its location within the vector
				SearchContainer Max = results[0];
				//std::vector<SearchContainer>::iterator bookmark;
				int bookmark = 0;
				int counter = 0;

				//go through and find the max score
				for (std::vector<SearchContainer>::iterator it = results.begin(); it != results.end(); ++it)
				{
					if (results[counter].Score() > Max.Score())
					{
						Max = results[counter];
						bookmark = counter;
					}
					++counter;
				}

				//remove max value from results and update the counter
				results.erase(results.begin() + bookmark);
				--resultsSize;

			}
			//increment map co-ordinates
			mapyc++;
		}
		//increment map co-ordinates
		mapxc++;
	}

	//Mark as completed
	std::cout << "\r" << "100% completed.   " << std::flush;
	std::cout << std::endl;

	//Find Min and Max of the scores
	auto min = FindMin(map->image.Get(), map->Width()*map->Height());
	auto max = FindMax(map->image.Get(), map->Width()*map->Height());

	//convert the map scores into a percentage value between 0 and 1
	for (int i = 0; i < map->Width(); i++)
	{
		for (int j = 0; j < map->Height(); j++)
		{
			double pixel = ((map->image.GetValue(i, j) - min) / (max - min));
			map->image.SetValue(i, j, pixel);
		}
	}

	//Draw the top results onto the image
	DrawFoundLocationGrids(*lImage, *rImage, results);

	//Save the Image and Map
	char output[] = "Output.pgm";
	lImage->write_pgm(output, lImage->image.Get(), lImage->Height(), lImage->Width());
	char outputmap[] = "Map.ppm";
	lImage->write_ppm(outputmap, map->image.Get(), map->Height(), map->Width());

	//Cleanup and finish
	delete map;
	std::cout << std::endl << "Wally Found!" << std::endl;
}

//finds the minimum value of an array
double Search::FindMin(double *arr, int size)
{
	double min = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

//finds the maximum value of an array
double Search::FindMax(double *arr, int size)
{
	double max = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

void Search::DrawFoundLocationGrids(Image &lImage, Image &rImage, std::vector<SearchContainer> &results)
{
	std::sort(results.begin(), results.end());
	//get the reference image size and thickness of line to draw
	int counter = 1;
	auto width = rImage.Width();
	auto height = rImage.Height();
	int thickness = 3;

	//Write Results
	std::cout << "Results Found:" << std::endl << std::endl;

	//for each value in the vector
	for (std::vector<SearchContainer>::iterator it = results.begin(); it != results.end(); ++it)
	{
		//get the x and y
		auto x = it->Xpos();
		auto y = it->Ypos();
		auto s = it->Score();

		//draw the box
		for (int i = x; i < x + width; i++)
		{
			for (int j = y; j < y + height; j++)
			{
				if (i < x + thickness || i > x + width - 1 - thickness)
				{
					if (i >= 0 && j >= 0)
					{
						lImage.image.SetValue(i, j, 0);
					}
				}
				if (j < y + thickness || j > y + height - 1 - thickness)
				{
					if (i >= 0 && j >= 0)
					{
						lImage.image.SetValue(i, j, 0);
					}
				}
			}
		}

		//Write Results
		std::cout << counter << ". x: " << x << " , y: " << y << " , Score : " << s << std::endl;
		counter++;
	}
	std::cout << std::endl;
}

