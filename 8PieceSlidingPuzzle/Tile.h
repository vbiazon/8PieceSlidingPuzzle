#pragma once

#define NULL 0
struct Tile {

	int valor = 0;
	Tile* Up = NULL;
	Tile* Dn = NULL;
	Tile* Le = NULL;
	Tile* Ri = NULL;

};