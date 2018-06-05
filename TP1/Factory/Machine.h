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

	/*
	*  enfile la pièce p dans la file des pièces à traiter
	*  enfile la pièce soit dans une file vide, soit dans une file qui contient déjà des exemplaires de la pièce en question
	*/
	void enfiler(Piece);

	/*
	*  vérfie si toutes les files de la machine ne sont pas vides
	*  renvoie true si toutes les files ont au moins 1 élément, renvoie false sinon
	*/
	bool traitementPossible();

	/*
	*  traite une pièce
	*/
	void traiterPiece(int);

	/*
	*  vérifie la fin du traitement en cours
	*  renvoie true si le traitement est terminé, false sinon
	*/
	bool verifFinTraiement(int);

	/*
	*  vérifie la fin de la panne en cours
	*  renvoie true si la panne est terminé, false sinon
	*/
	bool verifFinPanne(int);

	/*
	*  passe l'état de la machine à "en panne"
	*/
	void tombeEnPanne(int);

	/*
	*  fait fontionner la machine
	*  renvoie true si une pièce a été traitée lors de cette itération, false sinon
	*/
	bool fonctionner(int);

private:
	File<Piece>** fileTab; // tableau de files, de taille nombreFiles
	Etat etat;
	int finPanne;
	int finTraitement;
	int tempsTraitement; // temps de traitement d'une pièce, en secondes
	int nombreFiles;
};

