#pragma once
#include <iostream>

#include "ServiceApp.h"

using namespace std;


class Console {
private:
	ServFilme& serv;

	//info meniu
	void meniu();

	//fct afisare lista filme
	void afisare(const vector<Film>& filme);

	//fct afisare cos inchirieri
	void afisareCos(const vector<Film>& filme);

	//submeniu cos
	void cosCumparaturi();

public:
	//operatii clasa
	Console() noexcept = default;
	Console(ServFilme& serv) noexcept : serv{ serv } {}
	Console(const ServFilme& x) = delete;

	/*
	Functie care ruleaza aplicatia
	*/
	void runApp();

};
