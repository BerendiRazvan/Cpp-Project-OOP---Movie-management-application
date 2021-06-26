
#include "VectorDinamic.h"


template<typename eT>
myVector<eT>::myVector(int size) {
	this->cap = size;
	this->nrOfEl = 0;
	this->lista = new eT * [this->cap];

	initializare(this->nrOfEl);
}


template<typename eT>
myVector<eT>::~myVector() {
	for (int i = 0; i < nrOfEl; i++) {
		delete this->lista[i];
	}
	delete[] this->lista;
}

template<typename eT>
eT& myVector<eT>::operator[](const int index) {
	if (index < 0 || index >= this->nrOfEl)
		throw("INVALID!");
	return *this->lista[index];
}



template<typename eT>
void myVector<eT>::expand() {
	this->cap *= 2;

	eT** copiereLista = new eT * [this->cap];

	for (int i = 0; i < this->nrOfEl; i++)
	{
		copiereLista[i] = new eT(*this->lista[i]);
	}

	for (int i = 0; i < nrOfEl; i++) {
		delete this->lista[i];
	}
	delete[] this->lista;

	this->lista = copiereLista;

	initializare(this->nrOfEl);
}


template<typename eT>
void myVector<eT>::initializare(int from) {
	for (int i = from; i < cap; i++) {
		this->lista[i] = nullptr;
	}
}


template<typename eT>
void myVector<eT>::push(const eT& element) {
	if (this->nrOfEl >= this->cap) {
		this->expand();
	}

	this->lista[this->nrOfEl++] = new eT(element);
}



