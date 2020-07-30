/**
Author: Callum Dyson-Gainsborough
Date Created: 2/11/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#include "Base.h"
#include "Globals.h"

//Constructor that takes in an image
Base::Base(char *fileName, int x, int y, double *data):image(x, y, data), File()
{
	this->x = x;
	this->y = y;
	read_text(fileName, x*y, data);
}

//Constructor that doesnt take in an image
Base::Base(int x, int y):image(x, y), File()
{
	this->x = x;
	this->y = y;
}

//Empty constructor, never used
Base::Base()
{

}

//Destructor
Base::~Base()
{
	if (global_debug)
		std::cout << "Base destroyed" << std::endl;
}

//Return Width
int Base::Width()
{
	return this->x;
}

//Return Height
int Base::Height()
{
	return this->y;
}
