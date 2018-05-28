#include "stdafx.h"
#include "Machine.h"

Machine::Machine(int t, Piece p) {
	int i;
	etat = LIBRE;
	tempsTraitement = t;
	nombreFiles = (p == Piece::PISTON) ? 3 : 1; // si la machine produit des pistons elle a trois files, sinon elle en a une

	// on crée le tableau de files
	fileTab = new File<Piece>*[nombreFiles];
	// on crée chaque file
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
		if (fileTab[i]->estVide() || fileTab[i]->premier() == p) { // on enfile la pièce dans la bonne file
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
		fileTab[i]->defiler(); // on défile un élément de chacune des files

	finTraitement = temps + tempsTraitement; // calcule la fin du traitement en fonction du temps courant

}

bool Machine::verifFinTraiement(int temps) {
	if (temps > finTraitement) {
		etat = LIBRE; // l'état de la machine repasse en libre
		return true;
	}
	return false;
}

bool Machine::verifFinPanne(int temps) {
	if (temps > finPanne) {
		etat = LIBRE; // l'état de la machine repasse en libre
		return true;
	}
	return false;
}

void Machine::tombeEnPanne(int temps) {
	etat = PANNE;
	finPanne = temps + 300 + (rand() % 300); // calcule la durée de la panne, aléatoirement entre 5 et 10 minutes (300 et 600 secondes)
}

bool Machine::fonctionner(int temps) {
	if (getEtat() == PANNE) // si la machine est en panne, on vérifie si la panne est terminée
		verifFinPanne(temps);

	else if (getEtat() == OCCUPEE) { // si la machine est en train de traiter une pièce, on vérifie si le traitement est terminé
		if (verifFinTraiement(temps)) {
			if (((double)rand() / RAND_MAX) < 0.25) // la machine a 25% de chance de tomber en panne
				tombeEnPanne(temps);
			return true; // une pièce a été traitée
		}
	}

	else if (traitementPossible()) // si la machine est libre et qu'un traitement est possible, on traite une pièce
		traiterPiece(temps);

	return false; // aucune pièce n'a été traitée lors de cette itération
}

