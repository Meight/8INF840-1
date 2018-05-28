#include "stdafx.h"
#include "List.h"
#include "Node.h"
#include <iostream>
#include <thread>

using namespace std;

List::List():
	head(nullptr){}

List::List(Node * n) :
	head(n){}

List::~List() {
	while (head != nullptr) {
		Node * n = head->next;
		head->~Node();
		head = n;
	}
}

void List::remove(int value) {
	Node * n = head;
	bool first = true;
	while (n != nullptr) {
		if (n->data == value) {
			if (n->next) {
				n->next->previous = n->previous;
			}
			if (n->previous) {
				n->previous->next = n->next;
			}
			if (first) {
				head = n->next;
			}
			n->~Node();
			return;
		}
		first = false;
	}
}

void List::add(int value) {

	Node * n = new Node();
	n->data = value;
	n->next = head;
	n->previous = nullptr;
	head->previous = n;
	head = n;
}


void List::printList() {
	Node * n = head;
	std::cout << "List data : " << endl;
	while (n) {
		std::cout << n->data << "  ";
		n = n->next;
	}
	std::cout << endl;
}

