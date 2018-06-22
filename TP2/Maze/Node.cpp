#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include "stdafx.h"
#include "Node.h"

bool Node::mark() { //cette fonction marque le noeud comme visité et renvoi true ou false en fonction de si il a déjà été visité ou non.

	if (this == nullptr || this->marked == true) {
		return false;
	}

	this->marked = true;
	if (this->goal) {
		return true;
	}
	return false;
}

int Node::getTotalCost() { //cette fonction renvoie le coût total du noeud
	return cost + distance;
}