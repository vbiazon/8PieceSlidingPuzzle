#include "Node.h"


Node::Node()
{
	parent = NULL;
	puzzle = NULL;
	h = 0;
	path_cost = 0;
}

Node::Node(Grid* x)
{
	parent = NULL;
	puzzle = new Grid;
	puzzle->s1->valor = x->s1->valor;
	puzzle->s2->valor = x->s2->valor;
	puzzle->s3->valor = x->s3->valor;
	puzzle->s4->valor = x->s4->valor;
	puzzle->s5->valor = x->s5->valor;
	puzzle->s6->valor = x->s6->valor;
	puzzle->s7->valor = x->s7->valor;
	puzzle->s8->valor = x->s8->valor;
	puzzle->s9->valor = x->s9->valor;
	h = 0;
}

Node::~Node()
{
	delete parent;
	delete puzzle;
}

bool Node::IsGoal()
{
	if (puzzle->s1->valor == 1 && \
		puzzle->s2->valor == 2 && \
		puzzle->s3->valor == 3 && \
		puzzle->s4->valor == 4 && \
		puzzle->s5->valor == 5 && \
		puzzle->s6->valor == 6 && \
		puzzle->s7->valor == 7 && \
		puzzle->s8->valor == 8 && \
		puzzle->s9->valor == 0) {
		return true;
	}
	return false;
}

bool Node::ComparePuzzles(Grid* x, Grid* y)
{
	if (x->s1->valor == y->s1->valor && \
		x->s2->valor == y->s2->valor && \
		x->s3->valor == y->s3->valor && \
		x->s4->valor == y->s4->valor && \
		x->s5->valor == y->s5->valor && \
		x->s6->valor == y->s6->valor && \
		x->s7->valor == y->s7->valor && \
		x->s8->valor == y->s8->valor && \
		x->s9->valor == y->s9->valor) {
		return true;
	}
	return false;
}

void Node::PrintPuzzle()
{
	cout << "[" << puzzle->s1->valor << " " << puzzle->s2->valor << " " << puzzle->s3->valor << "]" << endl;
	cout << "[" << puzzle->s4->valor << " " << puzzle->s5->valor << " " << puzzle->s6->valor << "]" << endl;
	cout << "[" << puzzle->s7->valor << " " << puzzle->s8->valor << " " << puzzle->s9->valor << "]" << endl;
}

void Node::Heuristica_M()
{
}

void Node::Heuristica_E()
{
}


bool Node::GerarFilhos(Lista<Node>* Frontier, Lista<Node>* Explored, int &Qtde_Verif)
{
	Node* aux = new Node;
	aux = this->MoveRi();

	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveLe();
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveUp();
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveDn();
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}
	return false;
}

bool Node::BuscarNodeLista(Lista<Node>* list, Node* Alvo)
{
	Elemento<Node>* Index = new Elemento<Node>;
	Index = list->GetIni();
	while (Index != NULL) {
		if (Index->dado->ComparePuzzles(Index->dado->puzzle, Alvo->puzzle)) 
		{
		return true;
		}
		Index = Index->proximo;
	}
	

	return false;
}

Node* Node::MoveRi()
{
	Node* NodeRi = new Node(puzzle);
	NodeRi->puzzle->WhereEmpty();
	if (NodeRi->puzzle->Empty->Ri == NULL) 
	{
		delete NodeRi;
		return nullptr;
	}
	else {
		NodeRi->puzzle->Empty->valor = NodeRi->puzzle->Empty->Ri->valor;
		NodeRi->puzzle->Empty->Ri->valor = 0;
		NodeRi->parent = this;
		NodeRi->path_cost = this->path_cost + 1;
		return NodeRi;
	}
}

Node* Node::MoveLe()
{
	Node* NodeLe = new Node(puzzle);
	NodeLe->puzzle->WhereEmpty();
	if (NodeLe->puzzle->Empty->Le == NULL)
	{
		delete NodeLe;
		return nullptr;
	}
	else {
		NodeLe->puzzle->Empty->valor = NodeLe->puzzle->Empty->Le->valor;
		NodeLe->puzzle->Empty->Le->valor = 0;
		NodeLe->parent = this;
		NodeLe->path_cost = this->path_cost + 1;
		return NodeLe;
	}
	
}

Node* Node::MoveUp()
{
	Node* NodeUp = new Node(puzzle);
	NodeUp->puzzle->WhereEmpty();
	if (NodeUp->puzzle->Empty->Up == NULL)
	{
		delete NodeUp;
		return nullptr;
	}
	else {
		NodeUp->puzzle->Empty->valor = NodeUp->puzzle->Empty->Up->valor;
		NodeUp->puzzle->Empty->Up->valor = 0;
		NodeUp->parent = this;
		NodeUp->path_cost = this->path_cost + 1;
		return NodeUp;
	}

}

Node* Node::MoveDn()
{
	Node* NodeDn = new Node(puzzle);
	NodeDn->puzzle->WhereEmpty();
	if (NodeDn->puzzle->Empty->Dn == NULL)
	{
		delete NodeDn;
		return nullptr;
	}
	else {
		NodeDn->puzzle->Empty->valor = NodeDn->puzzle->Empty->Dn->valor;
		NodeDn->puzzle->Empty->Dn->valor = 0;
		NodeDn->parent = this;
		NodeDn->path_cost = this->path_cost + 1;
		return NodeDn;
	}

}
