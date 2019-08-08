#include "Node.h"


Node::Node()
{
	parent = NULL;
	puzzle = NULL;
	h = 1;
	path_cost = 0;
}

Node::Node(Grid* x) // inicializa o Nó a partir de um grid
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
	h = 1;
}

Node::~Node() //destrutor
{
	delete parent;
	delete puzzle;
}

bool Node::IsGoal() //verifica se é o objetivo
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

bool Node::ComparePuzzles(Grid* x, Grid* y) //verifica igualdade de grids de dois nós
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

void Node::PrintPuzzle() //imprime puzzle
{
	cout << "[" << puzzle->s1->valor << " " << puzzle->s2->valor << " " << puzzle->s3->valor << "]" << endl;
	cout << "[" << puzzle->s4->valor << " " << puzzle->s5->valor << " " << puzzle->s6->valor << "]" << endl;
	cout << "[" << puzzle->s7->valor << " " << puzzle->s8->valor << " " << puzzle->s9->valor << "]" << endl;
}

void Node::Heuristica_M() //calcula heuristica de manhattan
{
	h = 0;
	if (puzzle->s1->valor != 1) // heuristica do tile S1
	{
		if (puzzle->s1->valor == 2 || puzzle->s1->valor == 4) {
			h += 1;
		}
		if (puzzle->s1->valor == 3 || puzzle->s1->valor == 5 || puzzle->s1->valor == 7) {
			h += 2;
		}
		if (puzzle->s1->valor == 6 || puzzle->s1->valor == 8) {
			h += 3;
		}
		if (puzzle->s1->valor == 0) {
			h += 4;
		}
	}
	if (puzzle->s2->valor != 2) // heuristica do tile S2
	{
		if (puzzle->s2->valor == 1 || puzzle->s2->valor == 3 || puzzle->s2->valor == 5) {
			h += 1;
		}
		if (puzzle->s2->valor == 4 || puzzle->s2->valor == 6 || puzzle->s2->valor == 8) {
			h += 2;
		}
		if (puzzle->s2->valor == 7 || puzzle->s2->valor == 0) {
			h += 3;
		}
	}
	if (puzzle->s3->valor != 3) // heuristica do tile S3
	{
		if (puzzle->s3->valor == 2 || puzzle->s3->valor == 6) {
			h += 1;
		}
		if (puzzle->s3->valor == 1 || puzzle->s3->valor == 5 || puzzle->s3->valor == 0) {
			h += 2;
		}
		if (puzzle->s3->valor == 4 || puzzle->s3->valor == 8) {
			h += 3;
		}
		if (puzzle->s3->valor == 7) {
			h += 4;
		}
	}
	if (puzzle->s4->valor != 4) // heuristica do tile S4
	{
		if (puzzle->s4->valor == 1 || puzzle->s4->valor == 5 || puzzle->s4->valor == 7) {
			h += 1;
		}
		if (puzzle->s4->valor == 2 || puzzle->s4->valor == 6 || puzzle->s4->valor == 8) {
			h += 2;
		}
		if (puzzle->s4->valor == 3 || puzzle->s4->valor == 0) {
			h += 3;
		}
	}
	if (puzzle->s5->valor != 5) // heuristica do tile S5
	{
		if (puzzle->s5->valor == 2 || puzzle->s5->valor == 4 || puzzle->s5->valor == 6 || puzzle->s5->valor == 8) {
			h += 1;
		}
		if (puzzle->s5->valor == 1 || puzzle->s5->valor == 3 || puzzle->s5->valor == 7 || puzzle->s5->valor == 0) {
			h += 2;
		}
	}
	if (puzzle->s6->valor != 6) // heuristica do tile S6
	{
		if (puzzle->s6->valor == 3 || puzzle->s6->valor == 5 || puzzle->s6->valor == 0) {
			h += 1;
		}
		if (puzzle->s6->valor == 2 || puzzle->s6->valor == 4 || puzzle->s6->valor == 8) {
			h += 2;
		}
		if (puzzle->s6->valor == 1 || puzzle->s6->valor == 7) {
			h += 3;
		}
	}
	if (puzzle->s7->valor != 7) // heuristica do tile S7
	{
		if (puzzle->s7->valor == 4 || puzzle->s7->valor == 8) {
			h += 1;
		}
		if (puzzle->s7->valor == 1 || puzzle->s7->valor == 5 || puzzle->s7->valor == 0) {
			h += 2;
		}
		if (puzzle->s7->valor == 2 || puzzle->s7->valor == 6) {
			h += 3;
		}
		if (puzzle->s7->valor == 3) {
			h += 4;
		}
	}
	if (puzzle->s8->valor != 8) // heuristica do tile S8
	{
		if (puzzle->s8->valor == 5 || puzzle->s8->valor == 7 || puzzle->s8->valor == 0) {
			h += 1;
		}
		if (puzzle->s8->valor == 2 || puzzle->s8->valor == 4 || puzzle->s8->valor == 6) {
			h += 2;
		}
		if (puzzle->s8->valor == 1 || puzzle->s8->valor == 3) {
			h += 3;
		}
	}
	if (puzzle->s9->valor != 0) // heuristica do tile S9
	{
		if (puzzle->s9->valor == 6 || puzzle->s9->valor == 8) {
			h += 1;
		}
		if (puzzle->s9->valor == 3 || puzzle->s9->valor == 5 || puzzle->s9->valor == 7) {
			h += 2;
		}
		if (puzzle->s9->valor == 2 || puzzle->s9->valor == 4) {
			h += 3;
		}
		if (puzzle->s9->valor == 1) {
			h += 4;
		}
	}
}

void Node::Heuristica_E() //calcula heuristica de numero de pecas fora do lugar correto
{
	h = 0;
	if (puzzle->s1->valor != 1) {
		h++;
	}
	if (puzzle->s2->valor != 2) {
		h++;
	}
	if (puzzle->s3->valor != 3) {
		h++;
	}
	if (puzzle->s4->valor != 4) {
		h++;
	}
	if (puzzle->s5->valor != 5) {
		h++;
	}
	if (puzzle->s6->valor != 6) {
		h++;
	}
	if (puzzle->s7->valor != 7) {
		h++;
	}
	if (puzzle->s8->valor != 8) {
		h++;
	}
	if (puzzle->s9->valor != 0) {
		h++;
	}
	return;
}


bool Node::GerarFilhos(Lista<Node>* Frontier, Lista<Node>* Explored, int &Qtde_Verif) //gera filhos do nó pai com os movimentos possiveis
{
	Node* aux = new Node; //cria nó auxiliar para realizar movimento
	aux = this->MoveRi(); //nó auxiliar é igual ao movimento do espaco paraa direita

	if (aux != NULL) //se o nó for nao nulo
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) { //verifica se ja esta inserido na fronteira ou no explorado
			cout << "Inserido na fronteira" << endl;
			if (aux->IsGoal()) { // verifica se é o objetivo
				Explored->InsereFinal(aux); //se for o objetivo insere no fim do explorado
				return true;
			}
			Frontier->InsereFinal(aux); //se nao insere no fim da fronteira
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveLe(); //segue os mesmos passos de MoveRi, mas movimenta o espaco para esquerda
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Frontier->InsereFinal(aux);
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveUp(); //segue os mesmos passos de MoveRi, mas movimenta o espaco para cima
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Frontier->InsereFinal(aux);
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveDn(); //segue os mesmos passos de MoveRi, mas movimenta o espaco para baixo
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			cout << "Inserido na fronteira" << endl;
			if (aux->IsGoal()) {
				Explored->InsereFinal(aux);
				return true;
			}
			Frontier->InsereFinal(aux);
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}
	return false;
}

void Node::GerarFilhos_Informado(Lista<Node>* Frontier, Lista<Node>* Explored, int& Qtde_Verif) //gera filhos com calculo de heuristica
{
	Node* aux = new Node; //cria nó auxiliar para realizar movimento
	aux = this->MoveRi(); //nó auxiliar é igual ao movimento do espaco paraa direita

	if (aux != NULL) //se o nó for nao nulo
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) { //verifica se ja esta inserido na fronteira ou no explorado
			aux->Heuristica_M(); //calcula heuristica do nó
			aux->path_cost = this->path_cost + aux->h; //calcula path cost acumulado
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux); //insere nó na fronteira
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveLe(); //segue os mesmos passos de MoveRi, mas movimenta o espaco para esquerda
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			aux->Heuristica_M();
			aux->path_cost = this->path_cost + aux->h;
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveUp(); //segue os mesmos passos de MoveRi, mas movimenta o espaco para cima
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			aux->Heuristica_M();
			aux->path_cost = this->path_cost + aux->h;
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}

	aux = this->MoveDn(); //segue os mesmos passos de MoveRi, mas movimenta o espaco para baixo
	if (aux != NULL)
	{
		if (!(BuscarNodeLista(Explored, aux) || BuscarNodeLista(Frontier, aux))) {
			aux->Heuristica_M();
			aux->path_cost = this->path_cost + aux->h;
			cout << "Inserido na fronteira" << endl;
			Frontier->InsereFinal(aux);
			Qtde_Verif++;
		}
		else
		{
			cout << "Ja existe no explorado ou na fronteira" << endl;
		}
	}
	return;
}

bool Node::BuscarNodeLista(Lista<Node>* list, Node* Alvo) // busca um nó em uma lista
{
	Elemento<Node>* Index = new Elemento<Node>;
	Index = list->GetIni(); //inializa elemento auxiliar de busca
	while (Index != NULL) { //enquanto o index nao for nulo
		if (Index->dado->ComparePuzzles(Index->dado->puzzle, Alvo->puzzle)) //verifica se o grid do nó é igual ao elemento da lista
		{
		return true;
		}
		Index = Index->proximo; //pega proximo elemento
	}
	

	return false;
}

Node* Node::MoveRi() //move espaco para direita
{
	Node* NodeRi = new Node(puzzle); //cria novo nó
	NodeRi->puzzle->WhereEmpty(); //encontra localizacao do espaco
	if (NodeRi->puzzle->Empty->Ri == NULL) //se o elemento a direita do espaco for null
	{
		delete NodeRi; //deleta elemento criado
		return nullptr;
	}
	else { //se nao
		NodeRi->puzzle->Empty->valor = NodeRi->puzzle->Empty->Ri->valor; //move valor do tile da direita do espaco
		NodeRi->puzzle->Empty->Ri->valor = 0; //zera tal elemento
		NodeRi->parent = this; //atribui a este elemento o pai dele
		NodeRi->path_cost = this->path_cost + NodeRi->h; //calcula path cost
		return NodeRi; //retorna elemento
	}
}

Node* Node::MoveLe() //os mesmos passos do MoveRi, mas movendo o espaco para a esquerda
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
		NodeLe->path_cost = this->path_cost + NodeLe->h;
		return NodeLe;
	}
	
}

Node* Node::MoveUp() // os mesmos passos do MoveRi, mas movendo o espaco para cima
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
		NodeUp->path_cost = this->path_cost + NodeUp->h;
		return NodeUp;
	}

}

Node* Node::MoveDn() // os mesmos passos do MoveRi, mas movendo o espaco para baixo
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
		NodeDn->path_cost = this->path_cost + NodeDn->h;
		return NodeDn;
	}

}
