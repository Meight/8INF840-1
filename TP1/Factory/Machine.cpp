#include "stdafx.h"
#include "Machine.h"

Machine::Machine(int t, Piece p) {
	int i;
	etat = LIBRE;
	tempsTraitement = t;
	nombreFiles = (p == Piece::PISTON) ? 3 : 1;
	fileTab = new File<Piece>*[nombreFiles];
	for (i = 0; i < nombreFiles; i++)
		fileTab[i] = new File<Piece>();
}


Machine::~Machine() {
}

Etat Machine::getEtat() const {
	return etat;
}

int Machine::getFinTraitement() const {
	return finTraitement;
}

void Machine::enfiler(Piece p) {
	int i;
	for (i = 0; i < nombreFiles; i++) {
		if (fileTab[i]->estVide() || fileTab[i]->premier() == p) {
			fileTab[i]->enfiler(p);
			return;
		}
	}
}

bool Machine::traitementPossible() {
	int i;
	for (i = 0; i < nombreFiles; i++)
		if (fileTab[i]->estVide())
			return false;
	return true;
}

void Machine::traiterPiece(int temps) {
	int i;

	etat = OCCUPEE;
	
	for (i = 0; i < nombreFiles; i++)
		fileTab[i]->defiler();

	finTraitement = temps + tempsTraitement;

}

bool Machine::verifFinTraiement(int temps) {
	if (temps > finTraitement) {
		etat = LIBRE;
		return true;
	}
	return false;
}

bool Machine::verifFinPanne(int temps) {
	if (temps > finPanne) {
		etat = LIBRE;
		return true;
	}
	return false;
}

void Machine::tombeEnPanne(int temps) {
	etat = PANNE;
	finPanne = temps + 300 + (rand() % 300);
}

bool Machine::fonctionner(int temps) {
	if (getEtat() == PANNE)
		verifFinPanne(temps);

	else if (getEtat() == OCCUPEE) {
		if (verifFinTraiement(temps)) {
			if (((double)rand() / RAND_MAX) < 0.25)
				tombeEnPanne(temps);
			return true;
		}
	}

	else if (traitementPossible())
		traiterPiece(temps);

	return false;
}

