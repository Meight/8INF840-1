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
	Machine *MT, *MJ, *MA, *MP;

	MT = new Machine(120, Piece::TETE);
	MJ = new Machine(180, Piece::JUPE);
	MA = new Machine(150, Piece::AXE);
	MP = new Machine(60, Piece::PISTON);

	piecesAssemblees = 0;
	temps = 0;

	while (piecesAssemblees < 100) {
		if (temps % 10 == 0) {
			switch (rand() % 3) {
			case 0: MT->enfiler(Piece::TETE); break;
			case 1: MJ->enfiler(Piece::JUPE); break;
			case 2: MA->enfiler(Piece::AXE); break;
			}
		}	

		if (MT->fonctionner(temps))
			MP->enfiler(Piece::TETE);
		if (MJ->fonctionner(temps))
			MP->enfiler(Piece::JUPE);
		if (MA->fonctionner(temps))
			MP->enfiler(Piece::AXE);
		if (MP->fonctionner(temps))
			piecesAssemblees++;

		temps++;		
	}

	std::cout << "Temps pour monter les 100 pistons: " << temps << "sec\n";

	system("PAUSE");
    return 0;
}

