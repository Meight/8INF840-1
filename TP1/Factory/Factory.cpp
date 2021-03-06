// Factory.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "File.h"
#include "Machine.h"
#include <iostream>
#include <ctime>

int main() {
	srand(time(0));

	int piecesAssemblees, temps;
	bool teteUsinee, jupeUsinee, axeUsine, pistonFabrique;
	Machine *MT, *MJ, *MA, *MP;

	MT = new Machine(120, Piece::TETE);
	MJ = new Machine(180, Piece::JUPE);
	MA = new Machine(150, Piece::AXE);
	MP = new Machine(60, Piece::PISTON);

	piecesAssemblees = 0; // nombre de pistons assemblés
	temps = 0; // temps écoulé en secondes

	while (piecesAssemblees < 100) { // on s'arrête dès que 100 pistons sont montés
		
		if (temps % 10 == 0) { // on envoie une pièce du carton vers les machines toutes les 10 secondes
			switch (rand() % 3) {
			case 0: MT->enfiler(Piece::TETE); break;
			case 1: MJ->enfiler(Piece::JUPE); break;
			case 2: MA->enfiler(Piece::AXE); break;
			}
		}	

		teteUsinee = MT->fonctionner(temps);
		jupeUsinee = MJ->fonctionner(temps);
		axeUsine = MA->fonctionner(temps);
		pistonFabrique = MP->fonctionner(temps);

		if (teteUsinee)
			MP->enfiler(Piece::TETE);
		if (jupeUsinee)
			MP->enfiler(Piece::JUPE);
		if (axeUsine)
			MP->enfiler(Piece::AXE);
		if (pistonFabrique)
			piecesAssemblees++;

		temps++;		
	}

	std::cout << "Temps pour monter les 100 pistons: " << (double)temps / 60 << " minutes\n";

	system("PAUSE");
    return 0;
}

