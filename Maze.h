#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Stack.h"
using namespace std;
class Maze {
public:
	struct Cell {
		int x, y;
		bool leftWall, rightWall, upWall, downWall; // Wall Presence
		bool visited = false;
		bool isPath = false;
		bool unvisited = true;
	};

	Maze(int M, int N); //constructor : M X N dimension
	~Maze(); //destructor : makeEmpty
	Maze(const Maze& other); // Copy constructor
	Maze& operator=(const Maze& other); // Copy assignment operator
	void generateMaze();
	vector<Cell*> getUnvisitedNeighbors(Cell* cell);
	void removeWalls(Cell* current, Cell* next);
	void printMaze(ofstream& file);
	bool isAccessible(Cell* current, Cell* neighbor, int dx, int dy);
	//	vector<Maze::Cell*>getAccessibleNeighbors(Cell* current);
	//	bool findPath(int x, int y, int exitX, int exitY);
	Stack<Cell*> pathFinder(Maze& maze, int entryX, int entryY, int exitX, int exitY);
	void printPath(std::ofstream& file, Stack<Cell*>& stacktoPrint);
	bool isWallBetween(Cell* cell1, Cell* cell2);
	vector<Cell*>getAccessibleNeighbors(Cell* cell);
private:
	Cell** grid; // 2D array of cells
	int M, N;





};
