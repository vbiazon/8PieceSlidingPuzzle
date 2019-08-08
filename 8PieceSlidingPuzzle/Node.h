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
	bool GerarFilhos(Lista<Node>* Frontier, Lista<Node>* Explored, int &Qtde_Verif); // gera nós derivados do puzzle, verifica se ja existem na fronteira ou no explorado, se sao o objetivo e inserem na fronteira. (BFS e DFS)
	void GerarFilhos_Informado(Lista<Node>* Frontier, Lista<Node>* Explored, int& Qtde_Verif); // gera nós, verifica se ja existemou se sao o objetivo, calcula heuristica e inserem na fronteira. (A* e Hill Climb)
	bool BuscarNodeLista(Lista<Node>* list, Node* Alvo); //encontra um nó numa lista
	Node* MoveRi(); //move espaco para direita
	Node* MoveLe(); //move espaco para esquerda
	Node* MoveUp(); //move espaco para cima
	Node* MoveDn(); //move espaco para baixo

	
};

