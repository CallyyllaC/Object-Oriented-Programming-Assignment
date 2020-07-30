/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#include "Globals.h"
#include "Search.h"
#include "Matrix.h"
#include "Image.h"
#include "Image.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <ShellAPI.h>


//define variables
bool mainMenu = true;
int input;
char ImageLocationLarge[] = "Cluttered_scene.txt";
char ImageLocationSmall[] = "Wally_grey.txt";

//define object pointers
Search *searcher;
Image *imageLarge;
Image *imageSmall;

//define functions
void FindWally();
void Open();

int main(int argc, char* argv[])
{
	//while at the menu
	while (true)
	{
		std::cout << "Please wait a moment whilst the images load..." << std::endl << std::endl;
		if (global_debug)
			std::cout << "Loading large image" << std::endl;

		//Load the larger image
		double* largeImageContainer = new double[1024 * 768];
		imageLarge = new Image(ImageLocationLarge, 1024, 768, largeImageContainer);
		if (global_debug)
			std::cout << "Large image loaded, loading small image" << std::endl;

		//Load the smaller Image
		double* smallImageContainer = new double[36 * 49];
		imageSmall = new Image(ImageLocationSmall, 36, 49, smallImageContainer);
		if (global_debug)
			std::cout << "Small image loaded" << std::endl;

		//create search object
		searcher = new Search();

		//Write the main menu
		std::cout << "Main Menu" << std::endl << std::endl << "1. Find Wally" << std::endl << "2. Exit" << std::endl << std::endl;

		//wait for user input and catch errors
		try
		{
			std::cin >> input;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			//run the find wally function
			FindWally();
			//open the outputs
			Open();

			if (global_debug)
				std::cout << "Deleting Images and arrays" << std::endl;
			//Delete the Objects and arrays
			delete imageLarge;
			delete[] largeImageContainer;
			delete imageSmall;
			delete[] smallImageContainer;
			delete searcher;
			break;
		case 2:
			return 0;
		default:
			std::cout << std::endl << "Please select a valid option" << std::endl << std::endl;
			break;
		}

	}

	return 0;
};

//Goto the FindWally submenu
void FindWally()
{
	//Ask how many results to find
	int num = -1;
	bool working = true;
	bool valid = false;
	do
	{
		std::cout << "How many results do you want to look for? (it may detect simmilar locacations dependsing on the search accuracy)" << std::endl << std::endl;
		std::cin >> num;
		std::cout << std::endl << std::endl;
		if (std::cin.good())
		{
			valid = true;
		}
	} while (!valid);


	//Select the accuracy of the search (for loop increment)
	//Recommend option 3 due to high speed and good enough accuracy
	std::cout << "Please select search accuracy" << std::endl << std::endl << "1. Best (Slowest) - recommended only for higher detailed heatmap but takes a long time" << std::endl << "2. Good (Faster)" << std::endl << "3. Okay (Fastest) - recommended for speed and very good results" << std::endl << "4. Back" << std::endl << std::endl;
	while (working)
	{
		//wait for user input
		std::cin >> input;
		std::cout << std::endl;

		//Run the selected find function or go back to the main menu
		switch (input)
		{
		case 1:
			try
			{
				searcher->SADSearch(imageLarge, imageSmall, num);
				working = false;
				std::cout << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case 2:
			try
			{
				searcher->SADSearch(imageLarge, imageSmall, num, 16);
				working = false;
				std::cout << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case 3:
			try
			{
				searcher->SADSearch(imageLarge, imageSmall, num, 4);
				working = false;
				std::cout << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case 4:
			working = false;
			break;
		default:
			std::cout << std::endl << "Please select a valid search accuracy" << std::endl << std::endl;
			break;
		}
	}
	std::cout << std::endl;
};

//Open the outputfiles
void Open()
{
	ShellExecuteA(NULL, "open", "Output.pgm", NULL, NULL, SW_SHOWNORMAL);
	ShellExecuteA(NULL, "open", "Map.ppm", NULL, NULL, SW_SHOWNORMAL);
};