#pragma once
#include "carte.h"
#include "carte_repo.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Carte carteAdaugata;
	CarteRepo& rep;
public:
	UndoAdauga(CarteRepo& rep, const Carte& c) :rep{ rep }, carteAdaugata{ c } {}
	void doUndo() override {
		rep.sterge_carte(carteAdaugata);
	}
};

class UndoSterge : public ActiuneUndo {
	Carte carteSters;
	CarteRepo& rep;
public:
	UndoSterge(CarteRepo& rep, const  Carte& c) :rep{ rep }, carteSters{ c } {}
	void doUndo() override {
		rep.store(carteSters);
	}
};

class UndoModifica : public ActiuneUndo {
	Carte carteModificata;
	CarteRepo& rep;
	int pozitiademodificat;
public:
	UndoModifica(CarteRepo& rep, const  Carte& c, int poz) :rep{ rep }, carteModificata{ c }, pozitiademodificat{ poz } {}
	void doUndo() override {
		rep.modify(carteModificata, pozitiademodificat);
	}
};