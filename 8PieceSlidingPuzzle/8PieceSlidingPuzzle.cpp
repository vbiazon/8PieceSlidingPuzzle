
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
	int Qtde_Verificacoes = 1;

	// inicio da exploracao BFS para encontrar a solucao.
	bool isGoal = false;
	Elemento<Node>* Alvo = new Elemento<Node>;

	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}

	while (isGoal == false) // enquanto nao encontrar a solucao...
	{

		explored->InsereFinal(frontier->GetIni()->dado);
		Alvo = explored->GetFim();
		Qtde_Verificacoes++;
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle();
		cout << "Gerando do alvo: " << endl;
		Alvo->dado->GerarFilhos(frontier, explored, isGoal);
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
		frontier->RetiraInicio();
	}


	DSolution(Alvo);

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes e " << Alvo->dado->path_cost << " movimentos." << endl;

	cout << "Fim" << endl;
}

void DFS(Grid * Puzzle){

}

int main()
{
	try {
		
		// Definicao do quebra cabeca / puzzle a ser resolvido
		Grid* Puzzle;
		Puzzle = new Grid;
		Puzzle->s1->valor = 4;
		Puzzle->s2->valor = 1;
		Puzzle->s3->valor = 6;
		Puzzle->s4->valor = 3;
		Puzzle->s5->valor = 2;
		Puzzle->s6->valor = 8;
		Puzzle->s7->valor = 7;
		Puzzle->s8->valor = 0;
		Puzzle->s9->valor = 5;

		//Grid* Puzzle;
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4;
		//Puzzle->s2->valor = 2;
		//Puzzle->s3->valor = 5;
		//Puzzle->s4->valor = 6;
		//Puzzle->s5->valor = 0;
		//Puzzle->s6->valor = 3;
		//Puzzle->s7->valor = 7;
		//Puzzle->s8->valor = 1;
		//Puzzle->s9->valor = 8;

		//Grid* Puzzle;
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4;
		//Puzzle->s2->valor = 8;
		//Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 7;
		//Puzzle->s5->valor = 2;
		//Puzzle->s6->valor = 5;
		//Puzzle->s7->valor = 0;
		//Puzzle->s8->valor = 6;
		//Puzzle->s9->valor = 1;



		BFS(Puzzle);


		cin.get();

		return 0;
	}
	catch (const exception exc) {
		cout << "Ocorreu um erro!" << endl;
		cerr << exc.what() << endl;
	}
}

