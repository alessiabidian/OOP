#pragma once
#include "Carte.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class CarteRepo {
	vector<Carte> all;
	/*
	metoda privata verifica daca exista deja c in repository
	*/
	bool exist(const Carte& c);// const;
public:
	CarteRepo() = default;
	//nu permitem copierea de obiecte
	CarteRepo(const CarteRepo& ot) = delete;
	/*
	Salvare pet
	arunca exceptie daca mai exista o carte cu acelasi titlu si autor
	*/
	virtual void store(const Carte& c);

	/*
	Cauta
	arunca exceptie daca nu exista carte
	*/
	const Carte& find(string type, string species);// const;

	/*
	returneaza toate cartile salvate
	*/
	const vector<Carte>& getAll() const noexcept;

	/*
	Modifica o carte sau arunca exceptie
	*/
	void modify(const Carte& c, int poz);

	/*
	Sterge o carte sau arunca exceptie
	*/
	virtual void sterge(int poz);

	/*
	Sterge cartile cu anii care NU sunt divizibili cu un k dat
	*/
	void sterge_daca(int k);

	virtual void sterge_carte(const Carte& c);

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class CarteRepoException {
	string msg;
public:
	CarteRepoException(string m) :msg{ m } {}
	string getErrorMessage() {
		return this->msg;
	}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const CarteRepoException& ex);
};

ostream& operator<<(ostream& out, const CarteRepoException& ex);

class CarteRepositoryFile : public CarteRepo {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	* Salveaza datele din fisier
	* Format: titlu,artist,gen,durata\n
	*/
	void saveToFile();
public:
	CarteRepositoryFile(string fname) :CarteRepo(), filename{ fname } {
		loadFromFile();
	};
	void store(const Carte& c) override;
};


void testeRepo();