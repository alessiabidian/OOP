#include "Biblioteca_Lab1314_OOP.h"
#include "CarteStoreGUI.h"
#include <QtWidgets/QApplication>
#include "CarteGUIModele.h"
#include "cos_inchirieri.h"
#include "console.h"
#include "biblioteca.h"
#include "carte_repo.h"
#include "validator.h"

/*
3. Biblioteca
Creati o aplicatie care permite :
- gestiunea unei liste de carti. Carte : titlu, autor, gen, anul aparitiei
- adaugare DAP, stergere DAP, modificare DAP si afisare carti DAP
- cautare carte DAP
- filtrare carti dupa : titlu  Dap, anul aparitiei Dap
- sortare carti dupa titlu, autor, anul aparitiei + gen DAP
*/

void testAll() {
	testeRepo();
	testCtr();
	testValidator();
	testeBasket();
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	//CarteRepo rep;
	CarteRepositoryFile repoFile{ "books.txt" };
	CarteValidator val;
	//Biblioteca ctr{ rep,val };
	Biblioteca ctr{ repoFile,val };
	//CarteStoreGUI gui{ ctr };
	CarteStoreGUIModele gui{ ctr };

	//Biblioteca_Lab1011_OOPIter1 w;
	gui.show();
	return a.exec();
}