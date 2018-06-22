#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include "stdafx.h"
#include "Node.h"

bool Node::mark() {

	if (this == nullptr || this->marked == true) {
		return false;
	}

	this->marked = true;
	if (this->goal) {
		return true;
	}
	return false;
}

int Node::getTotalCost() {
	return cost + distance;
}