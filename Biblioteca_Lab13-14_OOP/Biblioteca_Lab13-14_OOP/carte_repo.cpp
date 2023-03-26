#include "carte_repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>

using std::ostream;
using std::stringstream;
using std::find_if;
using std::remove_if;

void CarteRepo::store(const Carte& c)
{
	if (exist(c)) {
		throw CarteRepoException("Exista deja carte cu titlul:" + c.getTitlu() + " si autor:" + c.getAutor());
	}
	all.push_back(c);
}

void CarteRepo::modify(const Carte& c, int poz)
{
	if (poz > all.size() || poz <= 0) {
		throw CarteRepoException("Nu exista carte cu pozitia:" + poz);
	}
	all.at(poz - 1) = c;
}

void CarteRepo::sterge(int poz)
{
	if (poz > all.size() || poz <= 0) {
		throw CarteRepoException("Nu exista carte cu pozitia:" + poz);
	}
	all.erase(all.begin() + poz - 1);
}

void CarteRepo::sterge_carte(const Carte& c) {
	auto found = std::find_if(all.begin(), all.end(), [c](const Carte& cc) {
		return cc.getAutor() == c.getAutor() && cc.getTitlu() == c.getTitlu();
		});
	if (found == all.end()) {
		throw CarteRepoException{ "Carte inexistenta!" };
	}
	//stergem carte
	auto rez = all.erase(found);
}

void CarteRepo::sterge_daca(int k)
{
	//sterge cartile cu anii care NU sunt divizibili cu un k dat
	all.erase(std::remove_if(all.begin(), all.end(), [k](const Carte& c) {return ((c.getAn() % k) != 0); }), all.end());
}

bool CarteRepo::exist(const Carte& c) {
	//const {
	try {
		find(c.getTitlu(), c.getAutor());
		return true;
	}
	catch (CarteRepoException&) {
		return false;
	}
}
/*
Cauta
arunca exceptie daca nu exista carte
*/
const Carte& CarteRepo::find(string titlu, string autor) {
	// const {
	//for (const auto& c : all) {
	//	if (c.getTitlu() == titlu && c.getAutor() == autor) {
	//		return c;
	//	}
	//}
	////daca nu exista arunc o exceptie
	//throw CarteRepoException("Nu exista carte cu titlul:" + titlu + " si autor:" + autor);

	vector<Carte>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Carte& c) {
			return c.getTitlu() == titlu && c.getAutor() == autor;
		});

	//daca nu exista arunc o exceptie
	if (f != this->all.end())
		return (*f);
	else
		throw CarteRepoException("Nu exista carte cu titlul:" + titlu + " si autor:" + autor);
}

/*
returneaza toate cartile salvate
*/
const vector<Carte>& CarteRepo::getAll() const noexcept {
	return all;
}


ostream& operator<<(ostream& out, const CarteRepoException& ex) {
	out << ex.msg;
	return out;
}

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;

void CarteRepositoryFile::loadFromFile() {
	ifstream carteFile(this->filename);
	if (!carteFile.is_open()) {
		throw CarteRepoException("Cannot read from file " + filename);
	}
	string line;
	while (getline(carteFile, line))
	{
		string titlu, autor, gen;
		int an = 0;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		//Citire linie de tip "Titlu,Artist,Gen,Durata"
		//separam linia cu separator = ,
		//se pot citi/scrie datele in fisier dupa cum va este usor
		//1 atribut pe o linie, sau pe o linie toate atributele, separate de spatiu etc
		while (getline(linestream, current_item, ','))
		{
			//we should do some checks here, make sure
			//that what we read is correct, throw exception otherwise
			//or 'clean' data we read
			//e.g. remove trailing spaces
			//as of now, if in file we have Venom, Eminem,... and we search
			//find("Venom","Eminem") - no space before artist, it won't work
			if (item_no == 0) titlu = current_item;
			if (item_no == 1) autor = current_item;
			if (item_no == 2) gen = current_item;
			if (item_no == 3) an = std::stoi(current_item); // stod(current_item);
			item_no++;
		}
		Carte s{ titlu, autor, gen, an };

		CarteRepo::store(s);


	}
	carteFile.close();
}

void CarteRepositoryFile::saveToFile() {
	ofstream carteOutput(this->filename);
	if (!carteOutput.is_open())
		throw CarteRepoException("Cannot write to file " + filename);
	for (auto& carte : getAll()) {
		carteOutput << carte.getTitlu() << "," << carte.getAutor() << ",";
		carteOutput << carte.getGen() << "," << carte.getAn() << endl;
	}
	carteOutput.close();
}

void CarteRepositoryFile::store(const Carte& c) {

	CarteRepo::store(c);

	saveToFile();
}

void testModificaRepo()
{
	CarteRepo rep;
	rep.store(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	Carte c1{ "Micul print", "Antoine de Saint - Exupery", "biografic", 1998 };
	rep.modify(c1, 1);
	assert(rep.find("Micul print", "Antoine de Saint - Exupery").getTitlu() == "Micul print");

	Carte c2{ "Lolita", "Vladimir Nabokov", "romantic", 1989 };

	try {
		rep.modify(c2, 5);
	}
	catch (const CarteRepoException&) {
		assert(true);
	}
}

void testStergeRepo()
{
	CarteRepo rep;
	rep.store(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	rep.store(Carte{ "Lolita", "Vladimir Nabokov", "romantic", 1989 });

	assert(rep.getAll().size() == 2);

	rep.sterge(1);

	assert(rep.getAll().size() == 1);

	try {
		rep.sterge(5);
	}
	catch (const CarteRepoException&) {
		assert(true);
	}

	try {
		rep.sterge_carte(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	}
	catch (const CarteRepoException&) {
		assert(true);
	}
}

void testAdauga() {
	CarteRepo rep;
	rep.store(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("Maitreyi", "Mircea Eliade").getTitlu() == "Maitreyi");

	rep.store(Carte{ "Micul print", "Antoine de Saint - Exupery", "biografic", 1998 });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu acelasi tip si specie
	try {
		rep.store(Carte{ "Maitreyi", "Mircea Eliade", "realist", 1933 });
		//assert(false);
	}
	catch (const CarteRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("c", "c");
		//assert(false);
	}
	catch (const CarteRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}

	try {
		rep.find("bla", "cla");
		//assert(false);
	}
	catch (CarteRepoException& re) {
		auto mesaj = re.getErrorMessage();
		assert(mesaj.find("exista") >= 0);
	}
}

void testCauta() {
	CarteRepo rep;
	rep.store(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	rep.store(Carte{ "Micul print", "Antoine de Saint - Exupery", "biografic", 1998 });

	auto p = rep.find("Maitreyi", "Mircea Eliade");
	assert(p.getAutor() == "Mircea Eliade");
	assert(p.getTitlu() == "Maitreyi");

	//arunca exceptie daca nu gaseste
	try {
		rep.find("a", "b");
		//assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testeFileRepo() {
	std::ofstream ofs;
	ofs.open("test_books.txt", std::ofstream::out | std::ofstream::trunc);
	ofs << "Maitreyi,Mircea Eliade,biografic,1933\n";
	ofs << "Ferma animalelor,George Orwell,istoric,2000\n";
	ofs << "Lolita,Vladimir Nabokov,romantic,1989\n";
	ofs << "Fluturi,Irina Binder,romantic,2016\n";
	ofs.close();
	try {
		CarteRepositoryFile testRepoF{ "test_books2.txt" };
	}
	catch (CarteRepoException&) {
		assert(true);
	}
	CarteRepositoryFile testRepoF{ "test_books.txt" };
	assert(testRepoF.getAll().size() == 4);


	auto foundBook = testRepoF.find("Fluturi", "Irina Binder");
	assert(foundBook.getAutor() == "Irina Binder");
	assert(foundBook.getAn() == 2016);
	assert(foundBook.getGen() == "romantic");

	Carte carte1{ "Maitreyi", "Mircea", "bio", 1933 };

	testRepoF.store(carte1);
	assert(testRepoF.getAll().size() == 5);
	Carte foundBook2 = testRepoF.find("Ferma animalelor", "George Orwell");
	assert(foundBook2.getAn() == 2000);

	try {
		CarteRepositoryFile testRepoF2{ "" };
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testModificaRepo();
	testCauta();
	testeFileRepo();
	testStergeRepo();
}
