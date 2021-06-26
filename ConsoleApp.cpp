#include <iostream>
#include <string>
#include <vector>
//#include <gsl.h>
#include <map>
#include <iterator>

//#include "myVectorDinamic.h"
#include "ConsoleApp.h"
#include "ErrorsApp.h"

using namespace std;


void Console::meniu() {
	
	cout << endl << endl << "\tMENIU Filme\n" << endl;
	cout << "1. Afisare lista" << endl;
	cout << "2. Adaugare" << endl;
	cout << "3. Modificare" << endl;
	cout << "4. Stergere" << endl;
	cout << "5. Cautare" << endl;
	cout << "6. Sortare" << endl;
	cout << "7. Filtrare" << endl;
	cout << "8. Raport genuri filme" << endl;
	
	cout << "\n+ - Cos cumparaturi" << endl;
	cout << "\n< - Undo" << endl;
	cout << "\nX - Inchidere aplicatie" << endl;
}

void Console::afisare(const vector<Film>& filme) {
	if (filme.size() == 0)
		cout << "\t-empty-" << endl;
	else {
		for (auto& f : filme)
			cout << f.getTitlu() << " | " << f.getGen() << " | " << f.getAn() << " | " << f.getActor() << endl;
	}
}

void Console::afisareCos(const vector<Film>& filme) {
	cout << "\nCosul dumneavoastra: "<< filme.size() << " filme \n";
	if (filme.size() == 0)
		cout << "\t-empty-" << endl;
	else {
		for (auto& f : filme)
			cout << f.getTitlu() << endl;
	}
}


void Console::cosCumparaturi() {
	
	string comSec;

	while (comSec != "X") {

		cout << "\n\n\tCOS Inchirieri\n\n";
		cout << "1. Golire cos\n";
		cout << "2. Adaugare in cos\n";
		cout << "3. Generare cos\n";
		cout << "4. Export\n";
		cout << "\nX - Inapoi la meniul principal" << endl;

		afisareCos(serv.getCos());

		cout << "\nIntroduceti comanda:";
		cin >> comSec;

		if (comSec == "1") {
			cout << "Golire cos...\n";
			serv.golesteCos();
			cout << "Cosul a fost golit.\n";
		}
		else if (comSec == "2") {
			string titluF;
			cout << "\nAdaugare in cos\n";
			cout << "Introduceti titlul: ";
			getline(cin >> ws, titluF);
			const int ok = serv.addInCos(titluF);
			if (ok == 1)
				cout << "Film adaugat.\n";
			else
				cout << "Filmul nu exista.\n";
		}
		else if (comSec == "3") {
			string nr;
			cout << "\nGenerare cos\n";
			cout << "Introduceti numarul de filme: ";
			getline(cin >> ws, nr);
			const int ok = serv.generareCos(stoi(nr));
			if(ok==0)
				cout << "Cosul a fost generat.\n";
			else
				cout << "Date invalide!\n";
		}
		else if (comSec == "4") {
			string fis;
			cout << "\nExportare cos\n";
			cout << "Introduceti nume fisier: ";
			getline(cin >> ws, fis);
			serv.exportData(fis);
			cout << "Exportare reusita.\n";
		}
		else if (comSec == "x" || comSec == "x") {
			comSec = 'X';
		}
		else
			cout << "Comanda inexistenta!\n";

	}
}



void Console::runApp() {
	string comanda;

	while (comanda!="X") {
		cout << "\n------------------------------";
		cout << "\n - COS Inchirieri: " << serv.dimCos() << " filme - \n";
		cout << "------------------------------";
		meniu();
		cout << "\nIntroduceti comanda:";
		cin >> comanda;

		if (comanda == "1") {
			cout << "\nLista de filme:\n";
			afisare(serv.getAllFilms());
		}
		else if (comanda == "2") {
			string titluF, genF, actorF,anF;
			cout << "\nAdaugare film\n";
			cout << "Introduceti titlul: ";
			getline(cin >> ws, titluF);
			cout << "Introduceti genul: ";
			getline(cin >> ws, genF);
			cout << "Introduceti anul: ";
			getline(cin >> ws, anF);
			cout << "Introduceti actorul principal: ";
			getline(cin >> ws, actorF);

			try {
				const auto& ok = serv.addFilmS(titluF, genF, anF, actorF);
				if (ok == 0)
					cout << "Adaugare realizata cu succes.\n";
				else
					cout << "Date invalide! Adaugare nerealizata.\n";
			}
			catch (ServException& err) {
				cout << err.returnError();
			}

		}
		else if (comanda == "3") {
			string titluF, genF, actorF, anF;
			cout << "\nModificare film\n";
			cout << "Introduceti titlul: ";
			getline(cin >> ws, titluF);
			cout << "Introduceti genul: ";
			getline(cin >> ws, genF);
			cout << "Introduceti anul: ";
			getline(cin >> ws, anF);
			cout << "Introduceti actorul principal: ";
			getline(cin >> ws, actorF);
			try{
			const auto& ok = serv.modificareFilmS(titluF, genF, anF, actorF);
			if (ok == 0)
				cout << "Modificare realizata cu succes.\n";
			else
				cout << "Date invalide! Modificare nerealizata.\n";
			}
			catch (ServException& err) {
				cout << err.returnError();
			}
		}
		else if (comanda == "4") {
			string titluF;
			cout << "\nStergere film\n";
			cout << "Introduceti titlul: ";
			getline(cin >> ws, titluF);
			try{
			if(serv.stergereFilmS(titluF)==0)
				cout << "Stergere realizata cu succes.\n";
			else
				cout << "Date invalide! Stergere nerealizata.\n";
			}
			catch (ServException& err) {
				cout << err.returnError();
			}
		}
		else if (comanda == "5") {
			string titluF;
			cout << "\nCautare film\n";
			cout << "Introduceti titlul: ";
			getline(cin >> ws, titluF);
			const int i = serv.cautareFilmS(titluF);
			if (i != -1) {
				cout << "Filmul gasit.\n";

				//afisare film daca e gasit
				cout << serv.getAllFilms()[i].getTitlu() << " | " << serv.getAllFilms()[i].getGen() << " | " << serv.getAllFilms()[i].getAn() << " | " << serv.getAllFilms()[i].getActor() << endl;
	
			}
			else
				cout << "Film inexistent.\n";

		}
		else if (comanda == "6") {
			string comSec;
			cout << "\nSortare filme\n";
			cout << "1. Titlu\n";
			cout << "2. An aparitie\n";

			cout << "\nAlegeti sortare:";
			cin >> comSec;

			if (comSec == "1") {
				serv.sortTitlu();
				auto& v = serv.getAllFilms();
				afisare(v);
			}
			else if (comSec == "2") {
				serv.sortAn();
				auto& v = serv.getAllFilms();
				afisare(v);
			}
			else
				cout << "Sortare inexistenta!\n";

		}
		else if (comanda == "7") {
			string comSec;
			cout << "\nFiltrare filme\n";
			cout << "1. Titlu\n";
			cout << "2. Actor principal\n";
			cout << "3. An aparitie si gen\n";

			cout << "\nAlegeti filtrare:";
			cin >> comSec;
			
			if (comSec == "1") {
				string text; 
				cout << "Introduceti titlu:";
				getline(cin >> ws, text);
				afisare(serv.filtruTitlu(text));
			}
			else if (comSec == "2") {
				string text;
				cout << "Introduceti actor:";
				getline(cin >> ws, text);
				afisare(serv.filtruActor(text));
			}
			else if (comSec == "3") {
				string nr;
				cout << "Introduceti an:";
				getline(cin >> ws, nr);
				string text;
				cout << "Introduceti gen:";
				getline(cin >> ws, text);

				afisare(serv.filtruAnGen(stoi(nr),text));
			}
			else
				cout << "Filtrare inexistenta!\n";
		}

		else if (comanda == "8") {
			cout << "\nRaport gen filme\n";

			map<string, int> raportMap;

			serv.raportFilme(raportMap);

			//afisare rezultat
			map<string, int>::iterator itr;
			for (itr = raportMap.begin(); itr != raportMap.end(); ++itr) {
				cout << itr->first << " - " << itr->second << '\n';

			}
			
		}

		else if (comanda == "+") {
			cosCumparaturi();
		}

		else if (comanda == "<") {
			try {
				serv.makeUNDO();
				cout << "Undo realizat.\n";
			}
			catch (ServException& err) {
				cout << err.returnError();
			}
		}

		else if (comanda == "x" || comanda == "X") {
			cout << "\nLa revedere!\n\n";
			comanda = 'X';
		}
		else {
			cout << "Comanda inexistenta!"<<endl;
		}
	}
}