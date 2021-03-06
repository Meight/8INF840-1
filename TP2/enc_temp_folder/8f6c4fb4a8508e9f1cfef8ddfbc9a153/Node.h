#pragma once
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
using namespace std;


class Node {

public:
	int size;

	Node() : marked(false), goal(false), predecessor(nullptr), cost(0){

	}

	int distance;
	int cost;
	bool marked;
	bool goal;
	int x;
	int y;
	list <Node *> neighbors;
	Node * predecessor;

	void addNeighbor(Node * n) { neighbors.push_back(n); }
	bool mark();
	int getTotalCost();


};
