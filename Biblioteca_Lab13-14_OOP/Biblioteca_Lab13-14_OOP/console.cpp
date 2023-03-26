#include "console.h"

#include "carte.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using namespace std;

void ConsoleUI::tipareste(const vector<Carte>& books) {
	cout << "Lista de carti:\n";
	int i = 0;
	for (const auto& carte : books) {
		i++;
		cout << i << ") Titlu: " << carte.getTitlu() << "; Autor: " << carte.getAutor() << "; Gen: " << carte.getGen() << "; An: " << carte.getAn() << '\n';
	}
	cout << "Sfarsit lista carti\n";
}

void ConsoleUI::meniuUI() {
	cout << "Meniu:\n";
	cout << "1. Adauga\n2. Tipareste\n3. Sorteaza dupa titlu\n";
	cout << "4. Sorteaza dupa autor\n5. Sorteaza dupa gen + an\n6. Filtrare an\n";
	cout << "7. Filtrare dupa titlu\n8. Cauta\n9. Modifica\n";
	cout << "10. Sterge\n11. Cos de Inchirieri\n12. Sterge Daca - Anul nu e divizibil cu k\n";
	cout << "13. Undo\n0. Iesire\n";
	cout << "Dati comanda : ";
}

void ConsoleUI::adaugaUI() {
	string t, autor, g;
	int an;
	cin.sync();
	cin.get();
	cout << "Dati titlul:";
	getline(cin, t);
	cout << "Dati autorul:";
	getline(cin, autor);
	cout << "Dati genul:";
	getline(cin, g);
	cout << "Dati anul:";
	cin >> an;
	ctr.addCarte(t, autor, g, an);
	cout << "***Adaugat cu succes!\n";
}

void ConsoleUI::filtrareUI(int cmd) {
	if (cmd == 6)
	{
		cout << "Dati an maxim:";
		int an;
		cin >> an;
		tipareste(ctr.filtrareAnMaiMic(an));
	}
	else {
		cout << "Dati titlu pt filtrat:";
		string titlu;
		cin >> titlu;
		tipareste(ctr.filtrareTitlu(titlu));
	}
}

void ConsoleUI::cautareUI() {
	string titlu, autor;
	cin.sync();
	cin.get();
	cout << "Dati titlul de cautat:";
	getline(cin, titlu);
	cout << "Dati autorul:";
	getline(cin, autor);

	Carte carte = ctr.cautare(titlu, autor);
	cout << "Cartea gasita: " << "Titlu: " << carte.getTitlu() << "; Autor: " << carte.getAutor() << "; Gen: " << carte.getGen() << "; An: " << carte.getAn() << '\n';
}

void ConsoleUI::modificaUI() {
	string t, autor, g;
	int an, poz;
	cin.sync();
	cin.get();
	cout << "Dati pozitia cartii de modificat:";
	cin >> poz;
	cin.sync();
	cin.get();
	cout << "Dati titlul:";
	getline(cin, t);
	cout << "Dati autorul:";
	getline(cin, autor);
	cout << "Dati genul:";
	getline(cin, g);
	cout << "Dati anul:";
	cin >> an;
	ctr.modifyCarte(t, autor, g, an, poz);
	cout << "***Modificat cu succes!\n";
}

void ConsoleUI::stergeUI() {
	int poz;
	cin.sync();
	cin.get();
	cout << "Dati pozitia cartii de sters:";
	cin >> poz;

	ctr.deleteCarte(poz);
	cout << "***Sters cu succes!\n";
}

void ConsoleUI::sterge_dacaUI() {
	int k;
	cin.sync();
	cin.get();
	cout << "Dati numarul k:";
	cin >> k;

	ctr.delete_daca(k);
	cout << "***Sters cu succes!\n";
}

void ConsoleUI::printBasketMenu() {
	cout << "MENIU COS INCHIRIERI:" << endl;
	cout << "1. Adauga o carte in cos" << endl;
	cout << "2. Adauga carti random in cos" << endl;
	cout << "3. Goleste cosul" << endl;
	cout << "4. Afiseaza cosul curent" << endl;
	cout << "5. Export" << endl;
	cout << "6. Inapoi la meniul principal" << endl;
}

void ConsoleUI::AddToBasketUI() {
	string titlu, autor;
	cout << "Titlul cartii este:";
	getline(cin >> ws, titlu);

	cout << "Autorul cartii este:";
	getline(cin >> ws, autor);

	try {
		ctr.addToBasket(titlu, autor);
		cout << "Cartea s-a adaugat cu succes in cos." << endl;
	}
	catch (CarteRepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidateException& ve) {
		cout << "Cartea nu este valida!" << endl;
		cout << ve.getErrorMessages();
	}
}

void ConsoleUI::AddRandomToBasketUI() {
	int howManyToAdd;
	cout << "Cate carti sa se adauge in cos?";
	cin >> howManyToAdd;


	try {
		int howManyAdded = ctr.addRandomToBasket(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " carti in cos." << endl;
	}
	catch (CarteRepoException& re) {
		cout << re.getErrorMessage();
	}
}

void ConsoleUI::EmptyBasketUI() {
	ctr.emptyBasket();
	cout << "S-au sters toate cartile din cosul curent." << endl;
}

string ConsoleUI::ExportBasketUI() {
	string filename;
	cout << "Fisierul de export este:";
	getline(cin >> ws, filename);
	ctr.exportBasket(filename);
	cout << "S-au exportat toate cartile din cosul curent." << endl;
	return filename;
}

void ConsoleUI::BasketUI() {
	int cmd;
	string filename;
	int runningBasket = 1;
	while (runningBasket) {
		printBasketMenu();
		cout << "----Nr total de carti in cos: " << ctr.getBasketBooks().size() << endl;
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			AddToBasketUI();
			break;
		case 2:
			AddRandomToBasketUI();
			break;
		case 3:
			EmptyBasketUI();
			break;
		case 4:
			tipareste(ctr.getBasketBooks());
			break;
		case 5:
			filename = ExportBasketUI();
			break;
		case 6:
			runningBasket = 0;
			EmptyBasketUI();
			ctr.exportBasket(filename);
			break;
		default:
			break;
		}

	}
}

void ConsoleUI::addDefaultBooks()
{
	ctr.addCarte("Maitreyi", "Mircea Eliade", "biografic", 1933);
	ctr.addCarte("Maitreyi", "Mircea", "bio", 1933);
	ctr.addCarte("Ferma animalelor", "George Orwell", "istoric", 2000);
	ctr.addCarte("Lolita", "Vladimir Nabokov", "romantic", 1989);
	ctr.addCarte("Micul print", "Antoine de Saint-Exupery", "best", 1998);
	ctr.addCarte("Fluturi", "Irina Binder", "romantic", 2016);
}

void ConsoleUI::start() {
	addDefaultBooks();
	int cmd;

	while (true) {
		meniuUI();
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				tipareste(ctr.getAll());
				break;
			case 3:
				tipareste(ctr.sortByTitlu());
				break;
			case 4:
				tipareste(ctr.sortByAutor());
				break;
			case 5:
				tipareste(ctr.sortByGenAn());
				break;
			case 6:
				filtrareUI(cmd);
				break;
			case 7:
				filtrareUI(cmd);
				break;
			case 8:
				cautareUI();
				break;
			case 9:
				modificaUI();
				break;
			case 10:
				stergeUI();
				break;
			case 11:
				BasketUI();
				break;
			case 12:
				sterge_dacaUI();
				break;
			case 13:
				ctr.undo();
				cout << "***Undo realizat cu succes!\n";
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
			}
		}
		catch (const CarteRepoException& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}