
#include "stdafx.h"
#include "Maze.h"
#include <iostream>

int main()
{
	Maze * maze = new Maze(20);
	//maze->BFS();
	maze->Astar();
	return 0;
}