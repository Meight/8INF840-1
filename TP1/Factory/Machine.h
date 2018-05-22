#pragma once

#include "File.h"
#include "Piece.h"

enum Etat { LIBRE, OCCUPEE, PANNE };

class Machine {
public:
	Machine(int, Piece);
	~Machine();
	Etat getEtat() const;
	int getFinTraitement() const;

	void enfiler(Piece);

	bool traitementPossible();
	void traiterPiece(int);
	bool verifFinTraiement(int);
	bool verifFinPanne(int);
	void tombeEnPanne(int);

	bool fonctionner(int);

private:
	File<Piece>** fileTab;
	Etat etat;
	int finPanne;
	int finTraitement;
	int tempsTraitement;
	int nombreFiles;
};

