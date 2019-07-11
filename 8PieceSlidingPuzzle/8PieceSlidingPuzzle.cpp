
#include "Grid.h"
#include "Tile.h"
#include "Lista.h"
#include "Elemento.h"
#include "Node.h"
#include <iostream>
#define NULL 0

using namespace std;

void DSolution(Elemento<Node>* Alvo) {
	// Cria lista guardando a solucao seguindo o parent de todos os nós acima da solucao.
	Lista<Node>* Solucao = new Lista<Node>;
	Node* SolTrace = new Node;
	SolTrace = Alvo->dado;
	while (SolTrace != NULL)
	{
		Solucao->InsereInicio(SolTrace);
		SolTrace = SolTrace->parent;
	}
	// imprime Solucao em ordem
	Elemento<Node>* PrintIndex = new Elemento<Node>;
	PrintIndex = Solucao->GetIni();
	while (PrintIndex != NULL)
	{
		cout << endl;
		PrintIndex->dado->PrintPuzzle();
		PrintIndex = PrintIndex->proximo;
	}
}

void BFS(Grid* Puzzle)
{
	// Cria estrutura para armazenamento dos itens ja explorados e da fornteira a ser explorada
	Lista<Node>* frontier = new Lista<Node>(); // Cria a lista para armazenar os nós na fronteira de exploracao
	Lista<Node>* explored = new Lista<Node>(); // Cria a lista para guardar os nós explorados previamente
	Node* NPuzzle = new Node(Puzzle); //Cria no node puzzle para inserir na fronteira
	frontier->InsereFinal(NPuzzle); // Insere o Node Puzzle na fronteira para comecar a exploracao.
	int Qtde_Verificacoes = 0;


	// inicio da exploracao BFS para encontrar a solucao.
	bool isGoal = false;
	Elemento<Node>* Alvo = new Elemento<Node>;

	Alvo = frontier->GetIni();


	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	Qtde_Verificacoes++;

	while (isGoal == false) // enquanto nao encontrar a solucao...
	{

		explored->InsereFinal(frontier->RetiraInicio());
		Alvo = explored->GetFim();
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle();
		cout << "Gerando filhos do alvo: " << endl;
		isGoal = Alvo->dado->GerarFilhos(frontier, explored, Qtde_Verificacoes);
		if (isGoal) {
			Alvo = explored->GetFim();
		}
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
	}


	DSolution(Alvo);

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes e " << Alvo->dado->path_cost << " movimentos." << endl;

	cout << "Fim" << endl;
}


void DFS(Grid * Puzzle){
	// Cria estrutura para armazenamento dos itens ja explorados e da fornteira a ser explorada
	Lista<Node>* frontier = new Lista<Node>(); // Cria a lista para armazenar os nós na fronteira de exploracao
	Lista<Node>* explored = new Lista<Node>(); // Cria a lista para guardar os nós explorados previamente
	Node* NPuzzle = new Node(Puzzle); //Cria no node puzzle para inserir na fronteira
	frontier->InsereFinal(NPuzzle); // Insere o Node Puzzle na fronteira para comecar a exploracao.
	int Qtde_Verificacoes = 0;

	// inicio da exploracao BFS para encontrar a solucao.
	bool isGoal = false;
	Elemento<Node>* Alvo = new Elemento<Node>;
	
	Alvo = frontier->GetIni();
	
	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	Qtde_Verificacoes++;

	while (isGoal == false) // enquanto nao encontrar a solucao...
	{

		explored->InsereFinal(frontier->GetFim()->dado);
		Alvo = explored->GetFim();
		frontier->RetiraFinal();
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle();
		cout << "Gerando filhos do alvo: " << endl;
		isGoal = Alvo->dado->GerarFilhos(frontier, explored, Qtde_Verificacoes);
		if (isGoal) {
			Alvo = explored->GetFim();
		}
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
	}


	DSolution(Alvo);

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes e " << Alvo->dado->path_cost << " movimentos." << endl;

	cout << "Fim" << endl;
}

void A_STAR(Grid* Puzzle) {

}


int main()
{
	try {
		
		// Definicao do quebra cabeca / puzzle a ser resolvido
		//Grid* Puzzle; // BFS 13 movimentos DFS 44665
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 1; Puzzle->s3->valor = 6;
		//Puzzle->s4->valor = 3; Puzzle->s5->valor = 2; Puzzle->s6->valor = 8;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 0; Puzzle->s9->valor = 5;

		//Grid* Puzzle; // BFS 16 movimentos DFS 30214
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 2; Puzzle->s3->valor = 5;
		//Puzzle->s4->valor = 6; Puzzle->s5->valor = 0; Puzzle->s6->valor = 3;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 1; Puzzle->s9->valor = 8;

		//Grid* Puzzle; // BFS 20 movimentos DFS 23008
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 8; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 7; Puzzle->s5->valor = 2; Puzzle->s6->valor = 5;
		//Puzzle->s7->valor = 6; Puzzle->s8->valor = 1; Puzzle->s9->valor = 0;

		//Grid* Puzzle; // Direct Goal
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 1; Puzzle->s2->valor = 2; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 4; Puzzle->s5->valor = 5; Puzzle->s6->valor = 6; 
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 8; Puzzle->s9->valor = 0;

			Grid* Puzzle; // BFS 3 movimento, DFS 319 Movimento
		Puzzle = new Grid;
		Puzzle->s1->valor = 1; Puzzle->s2->valor = 0; Puzzle->s3->valor = 2;
		Puzzle->s4->valor = 4; Puzzle->s5->valor = 5; Puzzle->s6->valor = 3;
		Puzzle->s7->valor = 7; Puzzle->s8->valor = 8; Puzzle->s9->valor = 6;

		//Grid* Puzzle; // BFS 1 movimento, DFS 1 Movimento
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 1; Puzzle->s2->valor = 2; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 4; Puzzle->s5->valor = 5; Puzzle->s6->valor = 0;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 8; Puzzle->s9->valor = 6;

		A_STAR(Puzzle);

		cin.get();

		return 0;
	}
	catch (const exception exc) {
		cout << "Ocorreu um erro!" << endl;
		cerr << exc.what() << endl;
	}
}

