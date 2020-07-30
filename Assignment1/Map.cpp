/**
Author: Callum Dyson-Gainsborough
Date Created: 2/11/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#include "Map.h"
#include "Globals.h"

//Constructor
Map::Map(int x, int y) :Base(x, y)
{

}

//Destructor
Map::~Map()
{
	if (global_debug)
		std::cout << "Map destroyed" << std::endl;
}
