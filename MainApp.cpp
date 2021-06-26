#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <crtdbg.h>

#include "TestApp.h"
#include "ConsoleApp.h"
#include "RepositoryApp.h"
#include "CosApp.h"
#include "ServiceApp.h"
#include "DomainApp.h"
#include "ValidatoriApp.h"
#include "RepoAppFISIER.h"
#include "RepoAppLab.h"


using namespace std;


int main() {



	cout << " - Inchiriere Filme - Lab. 6-7 / 8-9 - " << endl;

	{
		//Testare
		Tests testeApp{};
		testeApp.runAllTests();


		//Repository FISIER
		//RepoFilmeFIS repoFilme{"DataApp.txt"};


		//Repository Lab
		//RepoLab repoFilme{0.5};


		//Repository LISTA
		RepoFilme repoFilme{};

		//Filme
		//Film f1{ "The Martian","SF",2015,"Matt Damon" };
		//Film f2{ "Extraction","Actiune",2020,"Chris Hemsworth" };
		//Film f3{ "Bad Boys For Life","Comedie",2020,"Will Smith & Martin Lawrence" };
		//Film f4{ "Ready Player One","SF",2018,"Tye Sheridan" };
		//Film f5{ "Bird Box","Groaza",2018,"Sarah Paulson" };

		//Filme default
		//repoFilme.addFilm(f1);
		//repoFilme.addFilm(f2);
		//repoFilme.addFilm(f3);
		//repoFilme.addFilm(f4);
		//repoFilme.addFilm(f5);


		//Cos Inchirieri
		CosInchirieri cosFilme{};

		//Validatori
		const Validare validator{};

		//Service
		ServFilme servFilme{ repoFilme,cosFilme,validator };

		//UI
		Console uiApp{ servFilme };
		//uiApp.runApp();
	}
	cout << " - Aplicatie inchisa - " << endl;

	_CrtDumpMemoryLeaks();

	return 0;
}

/*
------------------------------------------------------------ LAB. Inchiriere Filme ------------------------------------------------------------------------------

Cerințe generale:
	– Creați o aplicație C++, folosiți paradigma orientat obiect
	– Aplicația are interfața utilizator tip consola
	– Utilizați procesul de dezvoltare bazat pe funcționalități (Feature driven
	development). Identificați funcționalitățile și planificați-le pe doua iterații
	– Folosiți o arhitectură stratificata (UI / Services(GRASP Controller) / Repository).
	Creati clase pentru: Domain, Service, UI, Repository.
	– Toate funcțiile necesare vor fi specificate și testate. (Test Code Coverage >99% la
	toate modulele in afara de UI)
	– Fara warninguri (in Visual Studio warning level /W4, treat warning as errors)
	– Const Correctness:
		– folosiți calificativul const pentru variabile/parametrii care nu sunt modificați
		– folosiți calificativul const pentru metode care nu modifica starea obiectelor
		– transmiteți parametrii prin const & peste tot unde este posibil
		– evitați copierea obiectelor când nu este necesar
	– Fără copii inutile in aplicație (vector stl - se accepta cele de la adaugare / clasa proprie Template pt. lista - se accepta cele de la filtrare)
	– Fără memory leak
	– Soluționat majoritatea erorilor raportate de linter: Activat „code analysis on
	build” selectat „"C++ Core Check rules". Va încurajez ca la fiecare
	eroare/sugestie raportata sa citiți partea relevanta din guidline (eroarea din VS
	oferă un link către secțiune), este e metoda buna pentru a explora limbajul
	C++. Daca va merge greu compilarea puteți sa activați doar din când in când
	analiza pentru a vedea ce erori raportează
 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

[Lab. 6-7]


P2 Închiriere filme

Creați o aplicație care permite:
	· gestiunea unei liste de filme. Film: titlu, gen, anul apariției, actor principal (Iteratia 1)
	· adăugare, ștergere, modificare și afișare filme (Iteratia 1)
	· căutare film (Iteratia 1)
	· filtrare filme după: titlu, anul apariției (Iteratia 2)
	· sortare filme după titlu, actor principal, anul apariției + gen (Iteratia 2)


Cerințe Iterație 1:
	– Folosiți clasa std::string si clasa std::vector din STL (librăria standard C++)
	– Nu folosiți pointeri.
	– Nu alocați dinamic.

Cerințe Iterația 2:
	– Înlocuiți clasa std::vector cu o clasa proprie parametrizata (Template) care
	implementează o lista folosind structura de date lista înlănțuita sau vector
	dinamic (la alegere).
	– Validarea datelor. Utilizatorul este anunțat printr-un mesaj daca: introduce
	valori de intrare greșite; încearcă sa adauge o entitate de doua ori, încearcă
	sa șteargă / modifice o entitate inexistenta (se vor folosi excepții)
	– Creați o diagramă UML a claselor pentru a schița arhitectura aplicației

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

[Lab. 8-9]


Cerințe Iterația 1:
	• Modificați aplicația: folosiți clasa vector din STL si înlocuiți toate for-urile din
	aplicație cu algoritmi din STL si varianta c++11 de for (range for). Exemplu
	de algoritmi: copy_if (la filtrare), find_if (căutare), sort
	• Folosiți excepții pentru a raporta erori (creați clase proprii pentru excepții).
	• Adăugați funcționalitatea noua (descris la fiecare problema).


Cerințe Iterația 2:
	Adăugați partea cu salvarea in fișiere pentru produse/filme/cărți, etc.
	Adăugați posibilitatea de undo pentru operațiile: adaugă, șterge si modifică.
	Pentru implementare folosiți moștenire si polimorfism:
		• Creați o clasa abstracta ActiuneUndo care are o singura metoda: doUndo.
		• Creați 3 clase derivate UndoAdauga, UndoSterge, UndoModifica care in
		metoda doUndo implementează partea care reface situația de dinaintea
		adăugării/ștergerii/modificării.
		• In controller se v-a tine o lista de ActiuniUndo care se pot executa in orice
		moment. Se va face un apel polimorfic la metoda doUndo.
		• Acordați atenție gestiunii memoriei, evitați fenomenul de slicing.


P2 (fct. noua) Introduceți posibilitatea de a crea un cos de închirieri. Utilizatorul poate crea
interactiv o lista de filme pe care dorește sa le închirieze.
Adăugați următoarele acțiuni (elemente de meniu):
	• Golește cos: șterge toate filmele din cos.
	• Adaugă in cos: adaugă in cos un film după titlu
	• Generează cos: utilizatorul introduce numărul total de filme, coșul se
	populează aliator cu filme
	• Export. Salvează cos in fișier: CVS sau HTML. Se face salvarea in fișier doar
	când s-a selectat acest meniu, coșul nu este persistent (la repornire aplicație
	coșul este din nou gol), utilizatorul introduce numele fișierului unde se
	salvează la fiecare export.
 După fiecare acțiune utilizator se afișează numărul total al filmelor din cos

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/