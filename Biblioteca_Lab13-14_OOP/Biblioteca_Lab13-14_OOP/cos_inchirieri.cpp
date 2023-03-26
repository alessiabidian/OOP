#include "cos_inchirieri.h"
#include "biblioteca.h"
#include "assert.h"
#include <fstream>
using std::shuffle;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;

void Basket::addBookToBasket(const Carte& c) {
	this->basketBooks.push_back(c);
	notify();
}
void Basket::emptyBasket() {
	this->basketBooks.clear();
	notify();

}

void Basket::addRandomBooks(vector<Carte> originalBooks, int howMany) {
	shuffle(originalBooks.begin(), originalBooks.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (basketBooks.size() < howMany && originalBooks.size() > 0) {
		basketBooks.push_back(originalBooks.back());
		originalBooks.pop_back();
	}
	notify();

}
const vector<Carte>& Basket::getAllBooksFromBasket() {
	return this->basketBooks;
}

//export to cvs
void Basket::saveToFile(string filename) {
	ofstream carteOutput(filename);
	if (!carteOutput.is_open())
		throw CarteRepoException("Cannot write to file " + filename);
	for (auto& carte : getAllBooksFromBasket()) {
		carteOutput << carte.getTitlu() << "," << carte.getAutor() << ",";
		carteOutput << carte.getGen() << "," << carte.getAn() << endl;
	}
	carteOutput.close();
}

void testaddBookToBasket()
{
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
	ctr.addCarte("Maitreyi", "Mircea Eliade", "biografic", 1933);
	ctr.addCarte("Micul print", "Antoine de Saint - Exupery", "best", 1998);
	Basket inchirieri;

	vector<Carte> allBooks = ctr.getAll();
	inchirieri.addBookToBasket(allBooks[0]);
	assert(inchirieri.getAllBooksFromBasket()[0].getTitlu() == "Enigma Otiliei");
}

void testEmpty()
{
	Basket inchirieri;

	assert(inchirieri.getAllBooksFromBasket().size() == 0);

	inchirieri.addBookToBasket(Carte{ "Enigma Otiliei", "George Calinescu", "roman realist", 1938 });
	inchirieri.addBookToBasket(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	inchirieri.addBookToBasket(Carte{ "Micul print", "Antoine de Saint - Exupery", "best", 1998 });

	assert(inchirieri.getAllBooksFromBasket().size() == 3);

	inchirieri.emptyBasket();

	assert(inchirieri.getAllBooksFromBasket().size() == 0);
}

void testaddRandom()
{
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
	ctr.addCarte("Maitreyi", "Mircea Eliade", "biografic", 1933);
	ctr.addCarte("Micul print", "Antoine de Saint - Exupery", "best", 1998);
	Basket inchirieri;

	assert(inchirieri.getAllBooksFromBasket().size() == 0);

	inchirieri.addRandomBooks(ctr.getAll(), 2);

	assert(inchirieri.getAllBooksFromBasket().size() == 2);
}

void testeBasket()
{
	testaddBookToBasket();
	testaddRandom();
	testEmpty();
}