#include <iostream>
#include "Maze.h"
#include "Stack.h"
#include <vector>
#include <fstream>
#include <string>
#include <random>

/*
		 Implementation of maze functionalities.

TO BE IMPLEMENTED:
maze generation algorithm.

- initializing the maze
- selecting random walls to knock down
- Ensuring each cell is reachable with a UNIIQUE path.
-------------------------------------------------------------------------------------------------------------------------------

TO BE IMPLEMENTED.

** path finding algorithm

- using stack to backtrack
when dead ends are encountered
*/

using namespace std;

/* Implementations of those in Maze.h */

// start with constructor

Maze::Maze(int M, int N) : M(M), N(N) {
	// 2D grid Arrayi için memory açýyoruz:

	grid = new Cell * [M];
	for (unsigned int i = 0; i < M; i++) {
		grid[i] = new Cell[N];
		for (unsigned int j = 0; j < N; j++) {
			grid[i][j].x = j;
			grid[i][j].y = i;
			grid[i][j].leftWall = true;
			grid[i][j].rightWall = true;
			grid[i][j].upWall = true;
			grid[i][j].downWall = true;
		}
	}
}



// destructor 
Maze::~Maze() {
	// Deallocating the grid
	for (unsigned elem = 0; elem < M; elem++) {
		delete[] grid[elem]; // row'larý deleteliyoruz
	}
	delete[]grid; // deleting the array of pointers
}

Maze::Maze(const Maze& other) : M(other.M), N(other.N) {
	grid = new Cell * [M];
	for (int i = 0; i < M; ++i) {
		grid[i] = new Cell[N];
		for (int j = 0; j < N; ++j) {
			grid[i][j] = other.grid[i][j];
		}
	}
}

Maze& Maze::operator=(const Maze& other) {
	if (this != &other) {
		// Free the existing resource.
		for (int i = 0; i < M; ++i) {
			delete[] grid[i];
		}
		delete[] grid;

		// Copy the size and allocate new memory.
		M = other.M;
		N = other.N;
		grid = new Cell * [M];
		for (int i = 0; i < M; ++i) {
			grid[i] = new Cell[N];
			for (int j = 0; j < N; ++j) {
				grid[i][j] = other.grid[i][j];
			}
		}
	}
	return *this;
}



void Maze::generateMaze() {

	random_device rd;  // Non-deterministic random number generator
	mt19937 gen(rd()); // Mersenne Twister pseudo-random generator of 32-bit numbers
	uniform_int_distribution<> distrib(0, 3); // Uniform distribution between 0 and 3

	Stack<Cell*> cellStack;
	Cell* currentCell = &grid[0][0];
	currentCell->visited = true;
	cellStack.push(currentCell);

	while (!cellStack.isEmpty()) {
		currentCell = cellStack.top();
		auto neighbors = getUnvisitedNeighbors(currentCell);
		int randNum = distrib(gen);

		if (!neighbors.empty()) {
			Cell* nextCell = neighbors[randNum % neighbors.size()];
			removeWalls(currentCell, nextCell);
			nextCell->visited = true;
			cellStack.push(nextCell);
		}
		else {
			cellStack.pop(); // No unvisited neighbors, backtrack.
		}
	}
}



vector<Maze::Cell*> Maze::getUnvisitedNeighbors(Cell* cell) {
	vector<Cell*> unvisited;
	int dx[] = { -1, 1, 0, 0 }; // Left, Right
	int dy[] = { 0, 0, -1, 1 }; // Up, Down
	for (int i = 0; i < 4; ++i) {
		int nx = cell->x + dx[i], ny = cell->y + dy[i];
		if (nx >= 0 && nx < N && ny >= 0 && ny < M && !grid[ny][nx].visited) {
			unvisited.push_back(&grid[ny][nx]);
		}
	}
	return unvisited;
}

// This function correctly remove walls between current and next cells
void Maze::removeWalls(Cell* current, Cell* next) {
	int dx = next->x - current->x;
	int dy = next->y - current->y;
	if (dx == 1 && dy == 0) { current->rightWall = next->leftWall = false; } // Next is to the right
	else if (dx == -1 && dy == 0) { current->leftWall = next->rightWall = false; } // Next is to the left
	else if (dy == 1 && dx == 0) { current->upWall = next->downWall = false; } // Next is above
	else if (dy == -1 && dx == 0) { current->downWall = next->upWall = false; } // Next is below
}

//vector<char> Maze::getAccessibleNeighbors(Maze & maze, Cell* cell, int M, int N){
//    char direction;
//    vector<char> output;
//    
//    int x = cell->x;
//    int y = cell->y;
//    
//    if(direction != 'u' && y != (M-1) && !grid[y+1][x].downWall && grid[y+1][x].unvisited) // up
//        output.push_back('u');
//    if(direction != 'd' && y != 0 && !grid[y-1][x].upWall && grid[y-1][x].unvisited) // down
//        output.push_back('d');
//    if(direction != 'r' && x != (N-1) && !grid[y][x+1].leftWall && grid[y][x+1].unvisited) // right
//        output.push_back('r');
//    if(direction != 'l' && x != 0 && !grid[y][x-1].rightWall && grid[y][x-1].unvisited) // left
//        output.push_back('l');
//    
//    return output;
//    
//}


vector<Maze::Cell*> Maze::getAccessibleNeighbors(Cell* cell) {
	vector<Cell*> accessible;
	// Directions: Up, Down, Left, Right
	int dx[] = { 0, 0, -1, 1 };
	int dy[] = { -1, 1, 0, 0 };

	for (int i = 0; i < 4; ++i) {
		int nx = cell->x + dx[i], ny = cell->y + dy[i];

		if (nx >= 0 && nx < N && ny >= 0 && ny < M && !grid[ny][nx].isPath) {

			accessible.push_back(&grid[ny][nx]);
		}
	}
	return accessible;
}
bool Maze::isWallBetween(Cell* cell1, Cell* cell2) {
	// Determine the direction of cell2 relative to cell1
	int dx = (cell2->x - cell1->x);
	int dy = (cell2->y - cell1->y);

	if (dx == 1 && dy == 0) { // cell2 is to the right of cell1
		return cell1->rightWall; // Check right wall of cell1 and left wall of cell2
	}
	else if (dx == -1 && dy == 0) { // cell2 is to the left of cell1
		return cell1->leftWall; // Check left wall of cell1 and right wall of cell2
	}
	else if (dy == -1 && dx == 0) { // cell2 is below cell1
		return cell1->downWall; // Check down wall of cell1 and up wall of cell2
	}
	else if (dy == 1 && dx == 0) { // cell2 is above cell1
		return cell1->upWall; // Check up wall of cell1 and down wall of cell2
	}

	// If cell2 is not directly adjacent to cell1, we cannot check for a wall between them
	return true; // Or handle this case as needed
}

Stack<Maze::Cell*> Maze::pathFinder(Maze& maze, int entryX, int entryY, int exitX, int exitY) {
	random_device rd;  // Non-deterministic random number generator
	mt19937 gen(rd()); // Mersenne Twister pseudo-random generator of 32-bit numbers
	uniform_int_distribution<> distrib(0, 3); // Uniform distribution between 0 and 3
	//start with the entry point
	Cell* currentCell = &grid[entryY][entryX];
	Stack<Cell*> pathStack;
	currentCell->isPath = true;
	pathStack.push(currentCell);

	while (currentCell->x != exitY || currentCell->y != exitX) {

		auto neighbours = getAccessibleNeighbors(currentCell);
		int randNum = distrib(gen);
		if (!neighbours.empty()) {
			Cell* nextCell = neighbours[randNum % neighbours.size()];
			if (!isWallBetween(currentCell, nextCell)) {
				nextCell->isPath = true;
				pathStack.push(nextCell);
				currentCell = pathStack.top();
			}
		}
		else {
			pathStack.pop();
			currentCell = pathStack.top();
		}
	}

	return pathStack;
}







void Maze::printMaze(std::ofstream& file) {
	// First, print the dimensions of the maze
	file << M << " " << N << std::endl;

	// Then print the cell information in row-major order
	for (int y = 0; y < M; y++) { // Ensure M is used for rows
		for (int x = 0; x < N; x++) { // Ensure N is used for columns
			Cell& cell = grid[y][x]; // Accessing with correct row and column
			file << "x=" << x << " y=" << y; // Output x and y as per loop variables, reflecting actual positions
			file << " l=" << (cell.leftWall ? "1" : "0")
				<< " r=" << (cell.rightWall ? "1" : "0")
				<< " u=" << (cell.upWall ? "1" : "0")
				<< " d=" << (cell.downWall ? "1" : "0") << std::endl;
		}
	}
}





void Maze::printPath(std::ofstream& file, Stack<Cell*>& stacktoPrint) {

	while (!stacktoPrint.isEmpty()) {
		Cell* curCell = stacktoPrint.top();
		file << curCell->y << " " << curCell->x << endl;
		stacktoPrint.pop();

	}

}
