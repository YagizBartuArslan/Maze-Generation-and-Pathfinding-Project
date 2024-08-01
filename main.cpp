#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include "Maze.h"
#include "Stack.h"
#include <random>



/*                                                              CS300 - MAZE HOMEWORK 1

                                                  Created by: Yaðýz Bartu Arslan - ID: 31235 - Sabanci University
Start Date: 07.03.2024
End Date: 18.03.2024

   ## Description

   - Implement a program - generates random maze of size M (rows) X N (columns)

   then

   - Implement a function - finds the path between designated entry and exit points in maze.

-----------------------------------------------------------------------------------------------------
   ### MUSTS TO DO IN HOMEWORK ###

    - Implement a STACK using a LINKEDLIST data structure (cannot use vectors in stack implementation.)

    - STACK class MUST be a TEMPLATE - based class. (to store basic data types, structs or classes in stack.)

-----------------------------------------------------------------------------------------------------
    ### THE MAZE ####


    - M rows X N columns -> Mazes (yani 2D vectors)

    - Left bottom of the maze -> coordinate (0,0)


-----------------------------------------------------------------------------------------------------
    ## Rules for a given 2D Vectors ##

    - Every cell must be reachable from any other cell.

    - There MUST be ONLY ONE path from a cell to another.

    - yani bir cellden diðerine birden fazla path olursa eðer, program patlar.

-----------------------------------------------------------------------------------------------------
    ## Program Flow ##

    2 phases:

     ** In both phases, MUST USE STACKS to solve the problem.
        1. The maze generation
        2. Finding a path for given entry and exit points
            -> Finding a path has a great chance to be implemented by using DFS algorithm
            -> DFS (Depth - First Search) , recursive algorithm; uses backtracking principle.

-----------------------------------------------------------------------------------------------------

    ## Maze Generation ##

    - generate K random M X N mazes -> using stacks for given M,N, and K values

    - Idea to generataze maze: To knock down walls between 2 cells,
      iteratively, until no unvisited cell remains.
     -So: Must to knowck down EXACTLY M X N -1 walls.

    - Each step, maze rules must apply all the time.

-----------------------------------------------------------------------------------------------------

     ## Basic Steps ##

     1: Start with an initially empty stack.

     2: Push (0,0) cell to your stack.

     3: Use the top element (currentCell) in the stack
        -> for choosing the next cell to be added to maze.

     4: Chosse a RANDOM wall of the currentCell to add a new unvisited cell to maze.

     5: Knock down the wall and add the new cell to the stack.

     6: If no wall exists to knock down for the currentCell
        -> BACKTRACK using the stack until you find a cell which has an unvisited neighbour cell.

     7: Continue steps 3-6 until no cell remains unvisited


 ---------------------------------------------------------------------------------------------------------
   ##   Path Discovery in a maze   ##

    Finding a path almost = to maze generation process.

    - First: program asks user which maze should be chosen among the ones generated in the first phase.

      Then:

      1: Start -> with an initally empty stack.

      2: Push the entry cell to stack. (entry will be entered by the user.)

      3: Use the top element in the stack -> to choose the next cell to visit.

      4: cannot find any cell to go ? -> BACKTRACK using the stack until find an unvisited cell to go.

      5: Continue steps 3-4
        -> until reaching the EXIT point.

      ! NOTE ! : The path generated in this phase MUST BE UNIQUE.

      Can assume that:
        * inputs, entered by user, are valid; -> do not inputcheck.
        * The entry and exit points of the mazes are on the edges or corners of the mazes.

   ---------------------------------------------------------------------------------------------------------
     ## Input and Output ##

     in first phase:
        Program asks 3 input: K, M and N.
        assume: M,N > 1 and K>0 (integers)
     Program should be able to generate huge mazes also.

     Mazes will be written into a file "maze_mazeID.txt" , mazeID will go from 1 to K
     such as : maze_1.txt and maze_4.txt

    Output:
    - In the first line, sizes of the maze, M and N, must be given.

    - In the following lines, for each cell, the x and y coordinates of the cell,
    as well as the walls of the cells, must be given.
    If there is a wall on the left (l), right (r), up (u), down (d), assign 1 to the wall, if not: assign 0.
    For example, in the maze_1.txtr below, at (0,0) cell,
    there are walls on the left,right, and down side, but not on the up side.

    maze1.txt:
    ______________________________
   | 5   4                        |
   | x=0  y=0  l=1  r=1  u=0  d=1 |
   | x=1  y=0  l=1  r=0  u=1  d=1 |
   | x=2  y=0  l=0  r=0  u=1  d=1 |
   | ...                          |
   |______________________________|

   In the second phase: (after the mazes are generated)
   -> program asks user to enter 5 more inputs: mazeID, entryX, entryY, exitX and exitY. | 1<= mazeID < K
   mazeID : the specific mazes that are generated in the first phase to be traveled.

    Example: mazeID = 3, program must find a path for the 3rd maze.

    - entryX and entryY = the coordinates for entry point
    - exitX and exitY = the coordinates for exit point.

    ! Note !
    y coordinates -> become the row of the maze.
    x coordinates -> become the column of the maze.

    Example: (2,4) -> refers: 4th row and 2nd column

    The output : will be written to a file named " maze_mazeID_path_entryX_entryY_exitX_exitY.txt

    Example: consider a maze: mazeID = 2, entry = (0,0) , exit = (3,4)
    -> filename will be: "maze_2_path_0_0_3_4.txt"

    In the output file, the coordinates of the cells to get the exit point from entry point
    must be written line by line.

     maze2_path_0_0_3_4.txt:
    ______________________________
   | 0 0                          |
   | ...                          |
   | ...                          |
   | 3 4                          |
   |                              |
   |______________________________|

  */


  //                                User interaction, file input / output, and application flow control.
  // TO DO's IN main.cpp:

  // - Handle user inputs for maze dimensions, entry, and exit poins.
  // - manage the selection of mazes.
  // - Using this to call the appropriate maze generation 
  // and path finding functions and handle file outputs

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Initialize random seed for maze generation

    int K, M, N;
    cout << "Enter the number of mazes: ";
    cin >> K;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> M >> N;

    vector<Maze> mazes; // Vector to store Maze objects

    // Generate mazes and write them to files
    for (int i = 1; i <= K; ++i) {
        mazes.emplace_back(M, N); // Add new maze directly to vector
        mazes.back().generateMaze(); // Generate maze for the last added maze

        ofstream file("maze_" + to_string(i) + ".txt");
        if (!file) {
            cerr << "Error opening file for maze " << i << endl;
            return 1;
        }

        mazes.back().printMaze(file); // Print the maze
        file.close();
       // cout << "Maze " << i << " generated and saved to maze_" << i << ".txt" << endl;
    }

    cout << "All mazes are generated." << endl;

    int mazeID;
    cout << "Enter a maze ID between 1 and " << K << " to find a path: ";
    cin >> mazeID;

    int entryX, entryY, exitX, exitY;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entryX >> entryY;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row):  ";
    cin >> exitX >> exitY;

    // Directly use the selected maze for pathfinding
    Maze& selectedMaze = mazes[mazeID - 1];
    Stack<Maze::Cell*> stacktoPrint = selectedMaze.pathFinder(selectedMaze, entryX, entryY, exitX, exitY);

    ofstream pathFile("maze_" + to_string(mazeID) + "_path_" + to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt");
    if (!pathFile) {
        cerr << "Error opening file for path output" << endl;
        return 1;
    }
    Stack<Maze::Cell*> stacktoPrint_reversed;

    // It reversed the path_discovered stack.
    while (!stacktoPrint.isEmpty()) {
        Maze::Cell* temp = stacktoPrint.top();
        stacktoPrint.pop();
        stacktoPrint_reversed.push(temp);
    }

    selectedMaze.printPath(pathFile, stacktoPrint_reversed);
    pathFile.close();
   // cout << "Path from (" << entryX << ", " << entryY << ") to (" << exitX << ", " << exitY << ") saved to maze_" << mazeID << "path" << to_string(entryX) << "" << to_string(entryY) << "" << to_string(exitX) << "_" << to_string(exitY) << ".txt" << endl;

    return 0;
}
