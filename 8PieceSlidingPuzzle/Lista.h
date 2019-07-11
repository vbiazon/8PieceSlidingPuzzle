#pragma once
#include "Elemento.h"
#include <iostream>
using namespace std;

template <typename T>
class Lista 
{
public:
	int Qtde = 0;
	Lista(); //Construtor
	~Lista(); //Destrutor
	void InsereFinal(T* x); //Insere elemento no final da lista
	void InsereInicio(T* x);// Insere elemento no inicio da lista
	T* RetiraFinal(); //Retira elemento do final da lista
	T* RetiraInicio(); //retira elemento do inicio da lista
	bool Busca(T* x); //Retorna ponteiro do elemento que contem x, se nao retonra NULL
	void Imprimir(); //Imprime a lista toda
	bool isEmpty(); //retorna true para lista vazia, false para lista nao fazia.
	Elemento<T>* GetIni(); // retorna o primeiro valor da Lista
	Elemento<T>* GetFim(); // retorna o ultimo valor da lista

protected:
	Elemento<T>* ini; //Guarda o ponteiro do inicio da lista ligada
	Elemento<T>* fim; //Guarda o ponteiro do fim da lista ligada

};



template <typename T>
Lista<T>::Lista() // construtor da lista
{
	Elemento<T>* ini = NULL;
	Elemento<T>* fim = NULL;
}

template<typename T>
Lista<T>::~Lista() //destrutor da lista
{
	Elemento<T>* tmp;

	tmp = ini;
	while (tmp != NULL) {
		ini = ini->proximo; //Atualiza o elemento da frente da fila
		delete tmp; // deleta elemento temporario
		tmp = ini; // atualiza tmp para proxima posicao
	}
}

template<typename T>
void Lista<T>::InsereFinal(T* x) { //insere elemento no fim da lista

	if (fim == NULL) { //se nao houver ponteiro para o elemento do fim da lista, esta vazio, chama funcao insereInicio.
		InsereInicio(x);
	}
	else {
		Elemento<T>* novo;
		novo = new Elemento<T>; // cria novo elemento no ponteiro novo
		novo->dado = x; //atribui o valor x ao valor do novo elemento
		fim->proximo = novo; //atualiza a posicao proximo do ultimo elemento para o novo elemneto
		novo->anterior = fim; // atualiza a posicao do elemento anterior do novo elemento para o elemento que era o ultimo
		fim = novo; //atribui a posicao de fim para o novo elemento
		Qtde++;
	}
}

template<typename T>
void Lista<T>::InsereInicio(T* x) { //insere elemento no inicio da lista
	Elemento<T>* novo;
	novo = new Elemento<T>; // cria novo elemento no ponteiro novo
	novo->dado = x; //atribui o valor x ao valor do novo elemento
	if (ini == NULL) { //Se nao houver ponteiro para o primeiro elemento da lista, significa que esta vazia logo o novo elemento é o primeiro e o ultimo
		ini = fim = novo;
		Qtde++;
	}
	else {
		novo->proximo = ini; //atualiza a posicao do proximo elemento do novo elemento como o elemento inicial
		ini->anterior = novo; // atualiza a posicao do anterior do elemento inicial para o novo elemento
		ini = novo; // o novo elemento é agora o elemento inicial
		Qtde++;
	}
}

template<typename T>
T* Lista<T>::RetiraFinal() { //retira valor do final da lista
	if (isEmpty()) { //Verifica se a lista esta vazia, se estiver lanca excecao
		throw std::exception("Lista vazia");
	}
	Elemento<T>* aux = fim; //guarda valor do elemento final numa variavel auxiliar
	if (fim->anterior == NULL) { //se o elemento anterior ao fim é nulo, só há um elemento na lista, logo se inicializa os ponteiros fim e ini
		fim = NULL;
		ini = NULL;
		Qtde--;
		return aux->dado;
	}
	else {
		fim->anterior->proximo = NULL; //se nao atualiza o valor do ponteiro proximo do elemento anterior ao final para null
		Elemento<T>* toDelete = fim;
		fim = fim->anterior; // atualiza o elemento anterior sendo o novo final da lista
		delete toDelete;
	}
	Qtde--;
	return aux->dado; //retorna valor armazenado
}

template<typename T>
T* Lista<T>::RetiraInicio() { //retira valor do inicio da lista

	if (isEmpty()) { //Verifica se a lista esta vazia, se estiver lanca excecao
		throw std::exception("Lista vazia");
	}
	T* aux = ini->dado; //guarda valor do elemento final numa variavel auxiliar
	if (ini->proximo == NULL) {//se o elemento proximo ao inicio é nulo, só há um elemento na lista, logo se inicializa os ponteiros fim e ini
		fim = NULL;
		ini = NULL;
		return aux;
	}
	ini->proximo->anterior = NULL; //se nao atualiza o valor do ponteiro anterior do elemento proximo ao inicio para null
	Elemento<T>* toDelete = ini;
	ini = ini->proximo; //atualiza o proximo elemento sendo o inicio da lista
	delete toDelete;
	Qtde--;
	return aux; //retorna valor armazenado

}

template<typename T>
bool Lista<T>::Busca(T* x) { //verifica se existe um valor armazenado na lista e retorna o ponteiro para a posicao caso exista
	if (isEmpty()) { //Verifica se a lista esta vazia, se estiver lanca excecao
		return false;
	}
	Elemento<T>* tmp = ini; //atribui um elemento temporario para o inicio da lista
	do {
		if (tmp->dado == x) { // verifica se o elemento coincide com o valor buscado
			return true; // se sim retorna ponteiro da posicao encontrada
		}
		tmp = tmp->proximo; //atualiza posicao do ponteiro para proximo elemento
	} while (tmp != NULL); // executa enquanto nao chegar no final
	return false; //se nao for encontrado retorna NULL

}

template<typename T>
void Lista<T>::Imprimir() { //imprime do comeco ao fim os valores da lista
	if (isEmpty()) { //Verifica se a lista esta vazia, se estiver lanca excecao
		throw std::exception("Lista vazia");
	}
	T* tmp = ini; //atribui um elemento temporario para o inicio da lista
	cout << "A lista armazenada e: ";
	do {
		cout << tmp->valor << " - ";
		tmp = tmp->proximo; //atualiza posicao do ponteiro para proximo elemento
	} while (tmp != NULL); // executa enquanto nao chegar no final
	cout << endl;

}

template<typename T>
bool Lista<T>::isEmpty() // varifica lista vazia
{
	return Qtde == 0; //se o ponteiro do inicio estiver vazio, a lista esta vazia, retorna true
}

template<typename T>
Elemento<T>* Lista<T>::GetIni()
{
	return ini; // retorna ponteiro para o elemento do inicio da lista
}

template<typename T>
Elemento<T>* Lista<T>::GetFim()
{
	return fim; // retorna ponteiro para o elemento do inicio da lista
}


