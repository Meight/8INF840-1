#include "stdafx.h"
#include "Node.h"
#include <thread>
using namespace std;

Node::Node() :
	next(nullptr),previous(nullptr),data(0) {}

Node::Node(Node * n, int value) :
	previous(nullptr),next(n),data(value) {}

Node::~Node() {

	if (next && previous) {
		next->previous = previous;
		previous->next = next;
	}
	else {
		if (previous) {
			previous->next = next;
		}
		if (next) {
			next->previous = previous;
		}
	}

}

int Node::sum() {
	return sum(true) + sum(false)-data;
}



int Node::sum(bool direction) {
	if (direction) {
		if (next) {
			return data+next->sum(direction);
		}
		else {
			return data;
		}
	}
	else {
		if (previous) {
			return data + previous->sum(direction);
		}
		else {
			return data;
		}
	}
}

