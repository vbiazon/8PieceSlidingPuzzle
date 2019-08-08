
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

void Max_Min_Heuristica_A_STAR(Lista<Node>* frontier, Index* index) { // Funcao para retirada da posicao dos ós de menor e maior valor da fronteira para o A*

	index->Aux = frontier->GetIni(); //Pega endereco do primeiro elemento
	int CustoMin = 1000000;
	int CustoMax = 0;
	while (index->Aux != NULL) { // verifica se o elemento é nulo, caso seja acaba o loop
		if (index->Aux->dado->h + index->Aux->dado->path_cost > CustoMax) //caso o path cost seja maior que o custo maximo atual, este será o elemento de maior path cost
		{
			index->Max = index->Aux;
			CustoMax = index->Aux->dado->h + index->Aux->dado->path_cost;
		}
		if (index->Aux->dado->h + index->Aux->dado->path_cost < CustoMin) //caso o path cost seja menor que o custo minimo atual, este será o elemento de menor path cost
		{
			index->Min = index->Aux;
			CustoMin = index->Aux->dado->h + index->Aux->dado->path_cost;
		}
		index->Aux = index->Aux->proximo; //pega proximo elemento
	}
}

void Max_Min_Heuristica_HC(Lista<Node>* frontier, Index* index) { // Funcao para retirada da posicao dos ós de menor e maior valor da fronteira para o Hill Climb

	index->Aux = frontier->GetIni();
	int CustoMin = 1000000;
	int CustoMax = 0;
	while (index->Aux != NULL) {// verifica se o elemento é nulo, caso seja acaba o loop
		if (index->Aux->dado->h > CustoMax) //caso a heuristica seja maior que o custo maximo atual, este será o elemento de maior custo
		{
			index->Max = index->Aux;
			CustoMax = index->Aux->dado->h;
		}
		if (index->Aux->dado->h < CustoMin) //caso a heuristica seja menor que o custo minimo atual, este será o elemento de menor custo
		{
			index->Min = index->Aux;
			CustoMin = index->Aux->dado->h;
		}
		index->Aux = index->Aux->proximo;//pega proximo elemento
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

	Alvo = frontier->GetIni(); //pega o primeiro elemento da fronteira


	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	Qtde_Verificacoes++; //incrementa numero de verificacoes

	while (isGoal == false) // enquanto nao encontrar a solucao...
	{

		explored->InsereFinal(frontier->RetiraInicio()); //insere elemento no final da lista de explorados retirando o primeiro da fronteira
		Alvo = explored->GetFim();  //endereca alvo como o ultimo elemento do explorao
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle(); // imprime qual puzzle esta sendo avaliado
		cout << "Gerando filhos do alvo: " << endl;
		isGoal = Alvo->dado->GerarFilhos(frontier, explored, Qtde_Verificacoes); //gera os filhos do alvo e avalia se algum deles é objetivo
		if (isGoal) {  //se isgoal for verdadeiro
			Alvo = explored->GetFim(); //a solucao é o ultimo elemento da lista de explorados
		}
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl; // imprime numero de elementos na fronteira
	}


	movimentos = DSolution(Alvo) - 1; //calcula numero de movimentos necessarios para se resolver o problema e imprime solucao na tela

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
	
	Alvo = frontier->GetIni(); // pega o primeiro elemento da fronteira
	
	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	Qtde_Verificacoes++; //incrementa numero de verificacoes

	while (isGoal == false) // enquanto nao encontrar a solucao...
	{

		explored->InsereFinal(frontier->GetFim()->dado); //insere elemento no final da lista de explorados retirando o primeiro da fronteira
		Alvo = explored->GetFim(); //endereca alvo como o ultimo elemento do explorao
		frontier->RetiraFinal();
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle(); // imprime qual puzzle esta sendo avaliado
		cout << "Gerando filhos do alvo: " << endl;
		isGoal = Alvo->dado->GerarFilhos(frontier, explored, Qtde_Verificacoes); //gera os filhos do alvo e avalia se algum deles é objetivo
		if (isGoal) { //se isgoal for verdadeiro
			Alvo = explored->GetFim(); //a solucao é o ultimo elemento da lista de explorados
		}
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl; // imprime numero de elementos na fronteira
	}


	movimentos = DSolution(Alvo) - 1; //calcula numero de movimentos necessarios para se resolver o problema e imprime solucao na tela

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

	Alvo = frontier->GetIni(); // pega o primeiro elemento da fronteira

	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	explored->InsereFinal(frontier->RetiraFinal()); //insere elemento no final da lista de explorados retirando o ultimo da fronteira
	Qtde_Verificacoes++;

	while (isGoal == false) // enquanto nao encontrar a solucao expande os filhos...
	{
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle(); // imprime qual puzzle esta sendo avaliado
		cout << "Tem custo de caminho: " << Alvo->dado->path_cost << " e Heuristica: " << Alvo->dado->h << endl;
		cout << "Gerando filhos do alvo: " << endl;
		Alvo->dado->GerarFilhos_Informado(frontier, explored, Qtde_Verificacoes); //gera os filhos do alvo e avalia se algum deles é objetivo
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
		Max_Min_Heuristica_A_STAR(frontier, index_aux->dado); //verifica qual o nó de menor pathcost
		explored->InsereFinal(frontier->RetiraElemento(index_aux->dado->Min)); //insere no final da lista explored o elemento de menor custo
		Alvo = explored->GetFim(); //endereca nó alvo como o ultimo elemento da fronteira explored
		if (Alvo->dado->IsGoal()) { // se for o objetivo
			cout << "Solucao encontrada:" << endl; // imprime solucao encontrada
			break;
		}
		
	}


	movimentos = DSolution(Alvo) - 1; //calcula numero de movimentos necessarios para se resolver o problema e imprime solucao na tela

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

	Alvo = frontier->GetIni(); //pega o primeiro elemento da fronteira como alvo

	if (Alvo->dado->IsGoal()) { // caso o puzzle inserido já seja o objetivo
		isGoal = true; // isGoal é verdadeiro
		cout << "Solucao encontrada" << endl; // mostra solucao encontrada
	}
	explored->InsereFinal(frontier->RetiraFinal()); //insere na lista explored o ultimo elemento da fronteira
	Qtde_Verificacoes++;

	while (isGoal == false) // enquanto nao encontrar a solucao expande os filhos...
	{
		cout << "Alvo eh: " << endl;
		Alvo->dado->PrintPuzzle(); // imprime qual puzzle esta sendo avaliado
		cout << "Tem custo de caminho: " << Alvo->dado->path_cost << " e Heuristica: " << Alvo->dado->h << endl;
		cout << "Gerando filhos do alvo: " << endl;
		Alvo->dado->GerarFilhos_Informado(frontier, explored, Qtde_Verificacoes); //gera os filhos do alvo e avalia se algum deles é objetivo
		cout << "Numero de elementos na fronteira: " << frontier->Qtde << endl;
		Max_Min_Heuristica_HC(frontier, index_aux->dado); //verifica qual o elemento da fronteira de menor heuristica
		explored->InsereFinal(frontier->RetiraElemento(index_aux->dado->Min)); //insere no final da lista explored o elemento de menor custo
		Alvo = explored->GetFim(); // endereca alvo como ultimo elemento da lsita explored
		if (Alvo->dado->IsGoal()) { //se for obejtivo
			cout << "Solucao encontrada:" << endl; // imprime solucao encontrada
			break;
		}

	}


	movimentos = DSolution(Alvo) - 1; //calcula numero de movimentos necessarios para se resolver o problema e imprime solucao na tela

	cout << "O problema foi resolvido com " << Qtde_Verificacoes << " verificacoes,  " << movimentos << " movimentos e custo de caminho: " << Alvo->dado->path_cost + Alvo->dado->h << endl;

	cout << "Fim" << endl;
}

int main()
{
	try {
		

		//Problema proposto em sala
		 //Definicao do quebra cabeca / puzzle a ser resolvido
		Grid* Puzzle; // BFS 13 movimentos DFS 44665 A* (776 verificacoes, 13 movimentos)
		Puzzle = new Grid;
		Puzzle->s1->valor = 4; Puzzle->s2->valor = 1; Puzzle->s3->valor = 6;
		Puzzle->s4->valor = 3; Puzzle->s5->valor = 2; Puzzle->s6->valor = 8;
		Puzzle->s7->valor = 7; Puzzle->s8->valor = 0; Puzzle->s9->valor = 5;

		//Grid* Puzzle; // BFS 16 movimentos DFS 30214  A* (3143 verificacoes, 16 movimentos)
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 2; Puzzle->s3->valor = 5;
		//Puzzle->s4->valor = 6; Puzzle->s5->valor = 0; Puzzle->s6->valor = 3;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 1; Puzzle->s9->valor = 8;

		//Grid* Puzzle; // BFS 20 movimentos DFS 23008 A* (16975 verificacoes, 20 movimentos)
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 8; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 7; Puzzle->s5->valor = 2; Puzzle->s6->valor = 5;
		//Puzzle->s7->valor = 6; Puzzle->s8->valor = 1; Puzzle->s9->valor = 0;

		//Grid* Puzzle; // A* 21 movimentos Hill CLimb 45.
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 4; Puzzle->s2->valor = 8; Puzzle->s3->valor = 3;
		//Puzzle->s4->valor = 7; Puzzle->s5->valor = 2; Puzzle->s6->valor = 0;
		//Puzzle->s7->valor = 6; Puzzle->s8->valor = 1; Puzzle->s9->valor = 5;

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

		//		Grid* Puzzle; 
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 1; Puzzle->s2->valor = 8; Puzzle->s3->valor = 2;
		//Puzzle->s4->valor = 0; Puzzle->s5->valor = 4; Puzzle->s6->valor = 3;
		//Puzzle->s7->valor = 7; Puzzle->s8->valor = 6; Puzzle->s9->valor = 5;

		//		Grid* Puzzle; //BFS e A* 31 movimentos... BFS 181438 verificacoes de 181440 possiveis PIOR CASO
		//Puzzle = new Grid;
		//Puzzle->s1->valor = 8; Puzzle->s2->valor = 6; Puzzle->s3->valor = 7;
		//Puzzle->s4->valor = 2; Puzzle->s5->valor = 5; Puzzle->s6->valor = 4;
		//Puzzle->s7->valor = 3; Puzzle->s8->valor = 0; Puzzle->s9->valor = 1;



		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();

		t1 = high_resolution_clock::now();
		BFS(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao BFS: " << duration/1000 << "ms" << endl << endl;
		cout << "Pressione Enter para executar o proximo algoritmo de busca" << endl;
		cin.get();

		t1 = high_resolution_clock::now();
		DFS(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao DFS: " << duration/1000 << "ms" << endl << endl;
		cout << "Pressione Enter para executar o proximo algoritmo de busca" << endl;
		cin.get();


		t1 = high_resolution_clock::now();
		A_STAR(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao A*: " << duration/1000 << "ms" << endl << endl;
		cout << "Pressione Enter para executar o proximo algoritmo de busca" << endl;
		cin.get();

		t1 = high_resolution_clock::now();
		HILL_CLIMB(Puzzle);
		t2 = high_resolution_clock::now();
		duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Tempo de execucao HC: " << duration/1000 << "ms"<< endl << endl;
		cout << "Pressione Enter para executar o proximo algoritmo de busca" << endl;
		cin.get();

		return 0;
	}
	catch (const exception exc) {
		cout << "Ocorreu um erro!" << endl;
		cerr << exc.what() << endl;
	}
}

