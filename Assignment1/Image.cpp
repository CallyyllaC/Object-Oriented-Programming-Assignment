/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 30/11/18
Last Change: Created
**/

#include "Image.h"
#include "Globals.h"

//Constructor
Image::Image(char *fileName, int x, int y, double* data) :Base(fileName, x, y, data)
{
}

//Destructor
Image::~Image()
{
	if (global_debug)
		std::cout << "Image destroyed" << std::endl;
}
