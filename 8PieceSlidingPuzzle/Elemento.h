#pragma once
#define NULL 0
template <typename T>
class Elemento // cria struct de elemento com ponteiros de anterior e proximo
{
public:
	T* dado = new T;
	Elemento* proximo = NULL;
	Elemento* anterior = NULL;
};


