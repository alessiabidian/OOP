#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Carte {
	std::string titlu;
	std::string autor;
	std::string gen;
	int an;
public:
	Carte() = delete;
	Carte(const string t, const string aut, const string g, int a) :titlu{ t }, autor{ aut }, gen{ g }, an{ a }{}

	/*Pet(const Pet& ot):type{ ot.type }, species{ ot.species }, price{ ot.price } {
		cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}*/

	Carte(const Carte& ot) :titlu{ ot.titlu }, autor{ ot.autor }, gen{ ot.gen }, an{ ot.an }{
		//cout << "[SONG] Copy constructor called." << endl; 
	};
	Carte& operator=(const Carte& ot) {
		this->titlu = ot.titlu;
		this->autor = ot.autor;
		this->gen = ot.gen;
		this->an = ot.an;
		return (*this);
	};

	string getTitlu() const {
		return titlu;
	}
	string getAutor() const {
		return autor;
	}
	string getGen() const {
		return gen;
	}
	int getAn() const noexcept {
		return an;
	}
};
/*
Compara dupa titlu
returneaza true daca c1.titlu e mai mic decat c2.titlu
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);

/*
Compara dupa autor
returneaza true daca c1.autor e mai mic decat c2.autor
*/
bool cmpAutor(const Carte& c1, const Carte& c2);

