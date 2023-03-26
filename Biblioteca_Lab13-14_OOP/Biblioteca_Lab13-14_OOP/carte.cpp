#include "carte.h"


bool cmpTitlu(const Carte& c1, const Carte& c2) {
	return c1.getTitlu() < c2.getTitlu();
}

bool cmpAutor(const Carte& c1, const Carte& c2) {
	return c1.getAutor() < c2.getAutor();
}

