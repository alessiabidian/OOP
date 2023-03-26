#pragma once
#include <string>
#include "carte.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : msgs) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class CarteValidator {
public:
	void validate(const Carte& c);
};

void testValidator();