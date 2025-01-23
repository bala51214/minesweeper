Minesweeper Game
Welcome to the Minesweeper game! This is a console-based implementation of the classic Minesweeper game, where you uncover cells on a grid to avoid hidden bombs. The game includes different difficulty levels and keeps track of player statistics.

Features
Multiple Difficulty Levels: Choose between Easy (5x5), Medium (7x7), and Hard (9x9) grids.
Player Statistics: Track the number of games played, won, and lost for each player.
Dynamic Board Layout: The board layout adjusts based on the selected difficulty level.
Bomb Placement: Randomly places bombs on the grid, ensuring a unique game experience each time.
How to Play
Select Difficulty: Choose a difficulty level when prompted.
Enter Cell Number: Enter a number between 1 and the total number of cells to uncover that cell.
Avoid Bombs: If you uncover a bomb, the game is over. If you uncover all non-bomb cells, you win!
Player Stats: Your game statistics are saved and displayed after each game.
Instructions
Compile and Run: Compile the code using a C++ compiler and run the executable.
Enter Your Name: When prompted, enter your name to track your game statistics.
Follow Prompts: Follow the on-screen prompts to play the game.
Code Overview
Board Initialization: The board is initialized with cells and bombs are placed randomly.
Cell Uncovering: The number of adjacent bombs is displayed when a cell is uncovered.
Game Logic: The game checks for win/loss conditions after each move.
Player Statistics: Player statistics are loaded from and saved to a file.
Example
Select Difficulty Level:
1. Easy (5x5)
2. Medium (7x7)
3. Hard (9x9)
Enter your choice: 3

Enter a number between 1 and 81 to uncover the cell
Enter a cell number (1-81): 5

Congratulations! You cleared the board. You won!
Requirements
Windows OS: The game uses Windows-specific libraries for console manipulation.
C++ Compiler: Ensure you have a C++ compiler installed to compile the code.
Contributing
Feel free to fork this repository and submit pull requests for any improvements or bug fixes.

License
This project is open-source and available under the MIT License.
