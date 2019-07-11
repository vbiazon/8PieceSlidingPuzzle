#pragma once
#include "Lista.h"
#include "Grid.h"
#define NULL 0
class Node
{
public:
	Node* parent;
	Grid* puzzle;
	Node();
	Node(Grid* x);
	~Node();
	int path_cost = 0; //custo do caminho
	int h; //heuristica
	bool IsGoal();
	bool ComparePuzzles(Grid* x, Grid* y);
	void PrintPuzzle();
	void Heuristica_M(); // calcula a heuristica pela distancia de manhattan
	void Heuristica_E(); // calcula heuristica pela quantidade de quadradinhos na posicao correta
	void GerarFilhos(Lista<Node>* Frontier, Lista<Node>* Explored, bool isGoal);
	bool BuscarNodeLista(Lista<Node>* list, Node* Alvo);
	Node* MoveRi();
	Node* MoveLe();
	Node* MoveUp();
	Node* MoveDn();

	
};

