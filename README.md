# Maze Generation and Pathfinding Project

### Description

This project is part of the CS300 course at Sabanci University. The goal is to create a program that generates random mazes of size MxN and finds the path between designated entry and exit points in the maze using a stack-based implementation. The project consists of two phases:

1. Maze generation
2. Pathfinding in the generated maze

### Features

- **Maze Generation**: Generates K random MxN mazes using stacks.
- **Pathfinding**: Finds a unique path from a given entry point to an exit point using Depth-First Search (DFS) and backtracking.
- **File I/O**: Saves the generated mazes and paths to text files.

### Requirements

- Implement a stack using a linked list data structure (cannot use vectors for the stack implementation).
- The stack class must be a template-based class.
- Use the stack for both maze generation and pathfinding.

### Files

- `main.cpp`: Handles user interaction, file input/output, and the main application flow.
- `Maze.h` and `Maze.cpp`: Defines the Maze class and its methods for maze generation and pathfinding.
- `Stack.h`: Defines the Stack class template used for both maze generation and pathfinding.
- `mazeDrawer.exe`: Executable for visualizing the generated mazes (Windows version).
- `libpwinthread-1.dll`: Required DLL for `mazeDrawer.exe` (Windows version).

### How to Run

1. **Clone the repository**:
    ```sh
    git clone https://github.com/YOUR_GITHUB_USERNAME/maze-generation-pathfinding.git
    cd maze-generation-pathfinding
    ```

2. **Compile the code**:
    ```sh
    g++ -o maze main.cpp Maze.cpp
    ```

3. **Run the executable**:
    ```sh
    ./maze
    ```

4. **Maze Drawer**:
   - To visualize the generated mazes, use the provided `mazeDrawer.exe` (or the corresponding file for your OS). 
   - Place `mazeDrawer.exe` (or `mazeDrawer.linux`/`mazeDrawer.mac`) in the same directory as your maze files and follow the instructions provided in `Homework1.pdf`.

### Example Usage

1. **Generating Mazes**:
    - Enter the number of mazes (K).
    - Enter the number of rows (M) and columns (N) for each maze.

2. **Finding Paths**:
    - Select a maze ID to find a path in one of the generated mazes.
    - Enter the entry (x, y) coordinates.
    - Enter the exit (x, y) coordinates.

### Sample Run

```plaintext
Enter the number of mazes: 5
Enter the number of rows and columns (M and N): 20 32
All mazes are generated.
Enter a maze ID between 1 and 5 to find a path: 1
Enter x and y coordinates of the entry points (x, y): 0 0
Enter x and y coordinates of the exit points (x, y): 31 19
Path from (0, 0) to (31, 19) saved to maze_1_path_0_0_31_19.txt

### File Formats
Maze File (maze_mazeID.txt):
  5 4
  x=0 y=0 l=1 r=1 u=0 d=1
  x=1 y=0 l=1 r=0 u=1 d=1
  x=2 y=0 l=0 r=0 u=1 d=1
  ...
Path File (maze_mazeID_path_entryX_entryY_exitX_exitY.txt):
  0 0
  ...
  3 4

Contributing
Contributions are welcome! Please fork the repository and create a pull request with your changes.

  1. Fork the project.
  2. Create your feature branch (git checkout -b feature/AmazingFeature).
  3. Commit your changes (git commit -m 'Add some AmazingFeature').
  4. Push to the branch (git push origin feature/AmazingFeature).
  5. Open a pull request.

License
Distributed under the MIT License. See LICENSE for more information.

Author
Yağız Bartu Arslan - Junior Computer Science & Engineering Student at Sabanci University


