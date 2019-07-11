#include "Grid.h"
#include <limits>

using namespace std;


Grid::Grid()
{
	s1 = new Tile;
	s2 = new Tile;
	s3 = new Tile;
	s4 = new Tile;
	s5 = new Tile;
	s6 = new Tile;
	s7 = new Tile;
	s8 = new Tile;
	s9 = new Tile;
	s1->Ri = s2; s1->Dn = s4;
	s2->Le = s1; s2->Ri = s3; s2->Dn = s5;
	s3->Le = s2; s3->Dn = s6;
	s4->Up = s1; s4->Ri = s5; s4->Dn = s7;
	s5->Up = s2; s5->Le = s4; s5->Ri = s6; s5->Dn = s8;
	s6->Up = s3; s6->Le = s5; s6->Dn = s9;
	s7->Up = s4; s7->Ri = s8;
	s8->Le = s7; s8->Up = s5; s8->Ri = s9;
	s9->Up = s6; s9->Le = s8;
	Empty = NULL;

}

Grid::~Grid()
{
	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
	delete s6;
	delete s7;
	delete s8;
	delete s9;

}

void Grid::WhereEmpty()
{
	if (s1->valor == 0) {
		Empty = s1;
		return;
	}
	if (s2->valor == 0) {
		Empty = s2;
		return;
	}
	if (s3->valor == 0) {
		Empty = s3;
		return;
	}
	if (s4->valor == 0) {
		Empty = s4;
		return;
	}
	if (s5->valor == 0) {
		Empty = s5;
		return;
	}
	if (s6->valor == 0) {
		Empty = s6;
		return;
	}
	if (s7->valor == 0) {
		Empty = s7;
		return;
	}
	if (s8->valor == 0) {
		Empty = s8;
		return;
	}
	if (s9->valor == 0) {
		Empty = s9;
		return;
	}
	return;
}

