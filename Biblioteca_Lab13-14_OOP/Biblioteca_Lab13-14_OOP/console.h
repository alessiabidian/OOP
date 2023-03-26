#pragma once
#include "biblioteca.h"
#include "carte.h"
class ConsoleUI {
	Biblioteca& ctr;

	void meniuUI();
	void addDefaultBooks();
	/*
	Citeste datele de la tastatura si adauga Carte
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();
	/*
	Tipareste o lista de carti la consola
	*/
	void tipareste(const vector<Carte>& books);

	void filtrareUI(int cmd);

	void cautareUI();

	void modificaUI();

	void stergeUI();

	void sterge_dacaUI();

	void printBasketMenu();
	void BasketUI();
	void AddToBasketUI();
	void AddRandomToBasketUI();
	void EmptyBasketUI();
	string ExportBasketUI();

public:
	ConsoleUI(Biblioteca& ctr) :ctr{ ctr } {
	}
	//nu permitem copierea obiectelor
	ConsoleUI(const ConsoleUI& ot) = delete;

	void start();
};