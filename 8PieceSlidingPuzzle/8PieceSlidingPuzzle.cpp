
#include "Grid.h"
#include "Tile.h"
#include "Lista.h"
#include "Elemento.h"
#include "Node.h"
#include "Index.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using std::scientific;
using std::fixed;
using std::ios;


int DSolution(Elemento<Node>* Alvo) {
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
	return Solucao->Qtde;
}

void Max_Min_Heuristica_A_STAR(Lista<Node>* frontier, Index* index) {

	index->Aux = frontier->GetIni();
	int CustoMin = 1000000;
	int CustoMax = 0;
	while (index->Aux != NULL) {
		if (index->Aux->dado->h + index->Aux->dado->path_cost > CustoMax)
		{
			index->Max = index->Aux;
			CustoMax = index->Aux->dado->h + index->Aux->dado->path_cost;
		}
		if (index->Aux->dado->h + index->Aux->dado->path_cost < CustoMin)
		{
			index->Min = index->Aux;
			CustoMin = index->Aux->dado->h + index->Aux->dado->path_cost;
		}
		index->Aux = index->Aux->proximo;
	}
}

void Max_Min_Heuristica_HC(Lista<Node>* frontier, Index* index) {

	index->Aux = frontier->GetIni();
	int CustoMin = 1000000;
	int CustoMax = 0;
	while (index->Aux != NULL) {
		if (index->Aux->dado->h > CustoMax)
		{
			index->Max = index->Aux;
			CustoMax = index->Aux->dado->h;
		}
		if (index->Aux->dado->h < CustoMin)
		{
			index->Min = index->Aux;
			CustoMin = index->Aux->dado->h;
		}
		index->Aux = index->Aux->proximo;
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
	int movimentos = 0;

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


	movimentos = DSolution(Alvo) - 1;

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes e " << movimentos << " movimentos." << endl;

	cout << "Fim" << endl;
}

void DFS(Grid * Puzzle){
	// Cria estrutura para armazenamento dos itens ja explorados e da fornteira a ser explorada
	Lista<Node>* frontier = new Lista<Node>(); // Cria a lista para armazenar os nós na fronteira de exploracao
	Lista<Node>* explored = new Lista<Node>(); // Cria a lista para guardar os nós explorados previamente
	Node* NPuzzle = new Node(Puzzle); //Cria no node puzzle para inserir na fronteira
	frontier->InsereFinal(NPuzzle); // Insere o Node Puzzle na fronteira para comecar a exploracao.
	int Qtde_Verificacoes = 0;
	int movimentos = 0;

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


	movimentos = DSolution(Alvo) - 1;

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes e " << movimentos << " movimentos." << endl;

	cout << "Fim" << endl;
}

void A_STAR(Grid* Puzzle) {
	// Cria estrutura para armazenamento dos itens ja explorados e da fornteira a ser explorada
	Lista<Node>* frontier = new Lista<Node>(); // Cria a lista para armazenar os nós na fronteira de exploracao
	Lista<Node>* explored = new Lista<Node>(); // Cria a lista para guardar os nós explorados previamente
	Node* NPuzzle = new Node(Puzzle); //Cria no node puzzle para inserir na fronteira
	Elemento<Index>* index_aux = new Elemento<Index>; // Cria index de busca-auxiliar para guarda posicao do alvo do A*
	frontier->InsereFinal(NPuzzle); // Insere o Node Puzzle na fronteira para comecar a exploracao.
	int Qtde_Verificacoes = 0;
	int movimentos = 0;

	// inicio da exploracao BFS para encontrar a solucao.
	bool isGoal = false;
	Elemento<Node>* Alvo = new Elemento<Node>;

	Alvo = frontier->GetIni();

	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	explored->InsereFinal(frontier->RetiraFinal());
	Qtde_Verificacoes++;

	while (isGoal == false) // enquanto nao encontrar a solucao expande os filhos...
	{
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle();
		cout << "Tem custo de caminho: " << Alvo->dado->path_cost << " e Heuristica: " << Alvo->dado->h << endl;
		cout << "Gerando filhos do alvo: " << endl;
		Alvo->dado->GerarFilhos_Informado(frontier, explored, Qtde_Verificacoes);
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
		Max_Min_Heuristica_A_STAR(frontier, index_aux->dado);
		explored->InsereFinal(frontier->RetiraElemento(index_aux->dado->Min));
		Alvo = explored->GetFim();
		if (Alvo->dado->IsGoal()) {
			cout << "Solucao encontrada:" << endl;
			break;
		}
		
	}


	movimentos = DSolution(Alvo) - 1;

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes,  " << movimentos << " movimentos e custo de caminho: " << Alvo->dado->path_cost + Alvo->dado->h << endl;

	cout << "Fim" << endl;
}

void HILL_CLIMB(Grid* Puzzle) {
	// Cria estrutura para armazenamento dos itens ja explorados e da fornteira a ser explorada
	Lista<Node>* frontier = new Lista<Node>(); // Cria a lista para armazenar os nós na fronteira de exploracao
	Lista<Node>* explored = new Lista<Node>(); // Cria a lista para guardar os nós explorados previamente
	Node* NPuzzle = new Node(Puzzle); //Cria no node puzzle para inserir na fronteira
	Elemento<Index>* index_aux = new Elemento<Index>; // Cria index de busca-auxiliar para guarda posicao do alvo do A*
	frontier->InsereFinal(NPuzzle); // Insere o Node Puzzle na fronteira para comecar a exploracao.
	int Qtde_Verificacoes = 0;
	int movimentos = 0;

	// inicio da exploracao BFS para encontrar a solucao.
	bool isGoal = false;
	Elemento<Node>* Alvo = new Elemento<Node>;

	Alvo = frontier->GetIni();

	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	explored->InsereFinal(frontier->RetiraFinal());
	Qtde_Verificacoes++;

	while (isGoal == false) // enquanto nao encontrar a solucao expande os filhos...
	{
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle();
		cout << "Tem custo de caminho: " << Alvo->dado->path_cost << " e Heuristica: " << Alvo->dado->h << endl;
		cout << "Gerando filhos do alvo: " << endl;
		Alvo->dado->GerarFilhos_Informado(frontier, explored, Qtde_Verificacoes);
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
		Max_Min_Heuristica_HC(frontier, index_aux->dado);
		explored->InsereFinal(frontier->RetiraElemento(index_aux->dado->Min));
		Alvo = explored->GetFim();
		if (Alvo->dado->IsGoal()) {
			cout << "Solucao encontrada:" << endl;
			break;
		}

	}


	movimentos = DSolution(Alvo) - 1;

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes,  " << movimentos << " movimentos e custo de caminho: " << Alvo->dado->path_cost + Alvo->dado->h << endl;

	cout << "Fim" << endl;
}


int main()
{
	try {
		
		// Definicao do quebra cabeca / puzzle a ser resolvido
		//Grid* Puzzle; // BFS 13 movimentos DFS 44665 A* (776 verificacoes, 13 movimentos)
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 1; Puzzle->s3->valor = 6;
		//Puzzle->s4->valor = 3; Puzzle->s5->valor = 2; Puzzle->s6->valor = 8;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 0; Puzzle->s9->valor = 5;

		Grid* Puzzle; // BFS 16 movimentos DFS 30214  A* (3143 verificacoes, 16 movimentos)
		Puzzle = new Grid;
		Puzzle->s1->valor = 4; Puzzle->s2->valor = 2; Puzzle->s3->valor = 5;
		Puzzle->s4->valor = 6; Puzzle->s5->valor = 0; Puzzle->s6->valor = 3;
		Puzzle->s7->valor = 7; Puzzle->s8->valor = 1; Puzzle->s9->valor = 8;

		//Grid* Puzzle; // BFS 20 movimentos DFS 23008 A* (16975 verificacoes, 20 movimentos)
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 8; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 7; Puzzle->s5->valor = 2; Puzzle->s6->valor = 5;
		//Puzzle->s7->valor = 6; Puzzle->s8->valor = 1; Puzzle->s9->valor = 0;

		//Grid* Puzzle; // Direct Goal
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 1; Puzzle->s2->valor = 2; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 4; Puzzle->s5->valor = 5; Puzzle->s6->valor = 6; 
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 8; Puzzle->s9->valor = 0;

		//	Grid* Puzzle; // BFS 3 movimento, DFS 319 Movimento
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 1; Puzzle->s2->valor = 0; Puzzle->s3->valor = 2;
		//Puzzle->s4->valor = 4; Puzzle->s5->valor = 5; Puzzle->s6->valor = 3;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 8; Puzzle->s9->valor = 6;

		//Grid* Puzzle; // BFS 1 movimento, DFS 1 Movimento
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 1; Puzzle->s2->valor = 2; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 4; Puzzle->s5->valor = 5; Puzzle->s6->valor = 0;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 8; Puzzle->s9->valor = 6;


		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		BFS(Puzzle);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao BFS: " << duration/1000 << "ms" << endl << endl;
		cin.get();

		t1 = high_resolution_clock::now();
		DFS(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao DFS: " << duration/1000 << "ms" << endl << endl;
		cin.get();
		cin.get();

		 t1 = high_resolution_clock::now();
		A_STAR(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao A*: " << duration/1000 << "ms" << endl << endl;
		cin.get();

		t1 = high_resolution_clock::now();
		HILL_CLIMB(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao HC: " << duration/1000 << "ms"<< endl << endl;
		cin.get();


		//Lista<Node>* teste_lista = new Lista<Node>;
		//Node* teste_node = new Node;
		//Node* teste_node2 = new Node;
		//Node* teste_node3 = new Node;
		//
		//teste_node->puzzle = Puzzle;
		//teste_node->path_cost = 10;
		//teste_lista->InsereInicio(teste_node);
		//Node* teste_node6 = new Node;
		//teste_node6->puzzle = Puzzle;
		//teste_node6->path_cost = 30;
		//teste_lista->InsereInicio(teste_node6);
		//Node* teste_node4 = new Node;
		//teste_node4->puzzle = Puzzle;
		//teste_node4->path_cost = 50;
		//teste_lista->InsereInicio(teste_node4);
		//Node* teste_node5 = new Node;
		//teste_node5->puzzle = Puzzle;
		//teste_node5->path_cost = 20;
		//teste_lista->InsereInicio(teste_node5);
		//
		//Elemento<Index>* index_aux = new Elemento<Index>; // Cria index de busca-auxiliar para guarda posicao do alvo do A*
		//Max_Min_Heuristica_A_STAR(teste_lista, index_aux->dado);
		//teste_node2 = teste_lista->RetiraElemento(index_aux->dado->Min);
		//teste_node3 = teste_lista->RetiraElemento(index_aux->dado->Max);
		//teste_node3->Heuristica_M();
		//cout << teste_node3->h;



		//cout << "Primeira retirada(min): " << teste_node2->path_cost << "e segunda retirada(max): " << teste_node3->path_cost << endl;

		cin.get();

		return 0;
	}
	catch (const exception exc) {
		cout << "Ocorreu um erro!" << endl;
		cerr << exc.what() << endl;
	}
}

