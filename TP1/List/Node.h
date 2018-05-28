#pragma once

using namespace std;

class Node{
public :
	int data;
	Node * next;
	Node * previous;
	

public:
	Node();
	Node(Node * n, int value);

	~Node();

	//std::thread spawn();
	int sum();
	int sum(bool direction);

};