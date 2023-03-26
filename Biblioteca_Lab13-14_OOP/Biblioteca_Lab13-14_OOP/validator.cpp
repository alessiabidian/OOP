#include "validator.h"
#include <assert.h>
#include <sstream>

void CarteValidator::validate(const Carte& c) {
	vector<string> msgs;
	if (c.getAn() < 0) msgs.push_back("An negativ!!!");
	if (c.getAn() < 1800) msgs.push_back("An invalid!!!");
	if (c.getTitlu().size() == 0) msgs.push_back("Titlu vid!!!");
	if (c.getAutor().size() == 0) msgs.push_back("Autor vid!!!");
	if (c.getGen().size() == 0) msgs.push_back("Gen vid!!!");

	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	CarteValidator v;
	Carte c{ "","","", -1 };
	try {
		v.validate(c);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

	Carte c1{ "","","", 1600 };
	try {
		v.validate(c1);
	}
	catch (ValidateException& ve) {

		auto mesaj = ve.getErrorMessages();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}