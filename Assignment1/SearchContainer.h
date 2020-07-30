/**
Author: Callum Dyson-Gainsborough
Date Created: 2/11/18
Date Last Changed: 2/11/18
Last Change: Updated comments
**/

#pragma once

class SearchContainer
{

public:
	//stuctors
	SearchContainer(double score, int x, int y);
	~SearchContainer();

	bool operator<(const SearchContainer &rhs) const { return score < rhs.score; }

	//define access functions
	int Xpos();
	int Ypos();
	double Score();

private:
	//define position and score
	int x;
	int y;
	double score;
};

