/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 30/11/18
Last Change: Created
**/

#include "Image.h"


//Assign the size of the image and create a matrix with the image data
Image::Image(char *fileName, int x, int y) :image(x, y, read_text(fileName, x, y))
{
}

Image::~Image()
{
}
