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
	*  enfile la pi�ce p dans la file des pi�ces � traiter
	*  enfile la pi�ce soit dans une file vide, soit dans une file qui contient d�j� des exemplaires de la pi�ce en question
	*/
	void enfiler(Piece);

	/*
	*  v�rfie si toutes les files de la machine ne sont pas vides
	*  renvoie true si toutes les files ont au moins 1 �l�ment, renvoie false sinon
	*/
	bool traitementPossible();

	/*
	*  traite une pi�ce
	*/
	void traiterPiece(int);

	/*
	*  v�rifie la fin du traitement en cours
	*  renvoie true si le traitement est termin�, false sinon
	*/
	bool verifFinTraiement(int);

	/*
	*  v�rifie la fin de la panne en cours
	*  renvoie true si la panne est termin�, false sinon
	*/
	bool verifFinPanne(int);

	/*
	*  passe l'�tat de la machine � "en panne"
	*/
	void tombeEnPanne(int);

	/*
	*  fait fontionner la machine
	*  renvoie true si une pi�ce a �t� trait�e lors de cette it�ration, false sinon
	*/
	bool fonctionner(int);

private:
	File<Piece>** fileTab; // tableau de files, de taille nombreFiles
	Etat etat;
	int finPanne;
	int finTraitement;
	int tempsTraitement; // temps de traitement d'une pi�ce, en secondes
	int nombreFiles;
};

