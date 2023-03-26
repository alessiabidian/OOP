#pragma once
#include "carte.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock
#include "Observer.h"

using std::vector;
class Basket : public Observable {
private:
	vector<Carte> basketBooks;
public:
	Basket() = default;
	/*
	* Adauga o carte in cos
	* @param c: melodia care se adauga (Carte)
	*
	* post: melodia va fi adaugata la playlist
	*/
	void addBookToBasket(const Carte& c);
	/*
	* Elimina toate melodiile din cos
	* post: cosul este gol
	*/
	void emptyBasket();
	/*
	* Adauga un numar random de carti in cos
	*
	* @param originalBooks: cartile din care se alege (vector<Carte>)
	* @param howMany: cate carti se adauga (int)
	*
	* post: cartile sunt adaugate in cosul curent
	*/
	void addRandomBooks(vector<Carte> originalBooks, int howMany);
	/*
	* Returneaza un vector care contine toate cartile din cos
	*/
	const vector<Carte>& getAllBooksFromBasket();

	//string filename;
	void saveToFile(string filename);
};

void testeBasket();
