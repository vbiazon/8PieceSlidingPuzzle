#pragma once

#include "Tile.h"
#include <iostream>

using namespace std;

class Grid
{
public:
	Grid();
	~Grid();
	Tile* s1 = NULL;
	Tile* s2 = NULL;
	Tile* s3 = NULL;
	Tile* s4 = NULL;
	Tile* s5 = NULL;
	Tile* s6 = NULL;
	Tile* s7 = NULL;
	Tile* s8 = NULL;
	Tile* s9 = NULL;
	Tile* Empty; // aposnta para qual quadradinho esta com o valor vazio e/ou 0
	void WhereEmpty();
};




	
