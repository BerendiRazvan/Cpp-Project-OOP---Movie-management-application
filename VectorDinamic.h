#pragma once



template <typename eT>
class myVector {
private:
	int cap;
	int nrOfEl;
	eT** lista;

public:

	myVector(int size = 5);
	~myVector();


	//initializare
	void initializare(int from);

	//redimensionare x2
	void expand();

	//add push_back
	void push(const eT& element);

	const int& size() const { return this->nrOfEl; }

	eT& operator[] (const int index);

};



