// List.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <thread>
#include "List.h"
#include "Node.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[], char *envp[])
{
	List list = List(new Node());
	Node n;
	
	for (int i = 1; i < 50; i++) {
		list.add(i);
	}
	list.printList();
	std::cout << "Sum of the list : " << endl << list.head->sum();
	list.~List();
	std::this_thread::sleep_for(2s);
    return 0;
}

void addnode(List list, int i){
	list.add(i);
}

