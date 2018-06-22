#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include "stdafx.h"
#include "Node.h"

bool Node::mark() { //cette fonction marque le noeud comme visit� et renvoi true ou false en fonction de si il a d�j� �t� visit� ou non.

	if (this == nullptr || this->marked == true) {
		return false;
	}

	this->marked = true;
	if (this->goal) {
		return true;
	}
	return false;
}

int Node::getTotalCost() { //cette fonction renvoie le co�t total du noeud
	return cost + distance;
}