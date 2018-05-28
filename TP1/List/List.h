#pragma once
#include "Node.h"
using namespace std;

class List {

public:
	Node * head;

public:
	List();
	List(Node * n);

	~List();

	void remove(int value);
	void add(int value);
	void printList();

};