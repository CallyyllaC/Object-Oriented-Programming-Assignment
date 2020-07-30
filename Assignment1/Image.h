/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 9/12/18
Last Change: Updated comments
**/

#pragma once
#include "Base.h"

class Image : public Base
{

public:
	//structors
	Image(char *fileName, int x, int y, double* data);
	~Image();
};

