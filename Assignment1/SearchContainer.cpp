/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 30/10/18
Last Change: Created
**/

#include "SearchContainer.h"
#include <iostream>
#include "Globals.h"

//assign the variables
SearchContainer::SearchContainer(double score, int x, int y)
{
	this->x = x;
	this->y = y;
	this->score = score;
}

//return the x position
int SearchContainer::Xpos()
{
	return this->x;
}

//return the y position
int SearchContainer::Ypos()
{
	return this->y;
}

//return the score of this position
double SearchContainer::Score()
{
	return this->score;
}


SearchContainer::~SearchContainer()
{
	//if (global_debug)
	//	std::cout << "SearchContainer destroyed" << std::endl;
}
