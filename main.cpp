#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;



int ROWS = 9;
int COLS = 9;
int BOMBS = 15;

#define MAX_PLAYERS 100 //Maximum number of players
char board[9][9];
bool revealed[9][9];
char ch = 219;
int numToCell[9][9];


struct Player {
    string name;
    int gamesPlayed;
    int gamesWon;
    int gamesLost;
};
Player players[MAX_PLAYERS];
int totalPlayers = 0;

void gotoRowCol(int rpos, int cpos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void horiline(int row) {
    for (int i = 10; i <= (10 + COLS * 12); i++) {
        gotoRowCol(row, i);
        cout << ch;
    }
}

void vertline(int col) {
    for (int i = 4; i <= (4 + ROWS * 4); i++) {
        gotoRowCol(i, col);
        cout << ch;
    }
}

void boardLayout() {

    for (int i = 4; i <= (4 + ROWS * 4); i += 4) {
        horiline(i);
    }

    for (int i = 10; i <= (10 + COLS * 12); i += 12) {
        vertline(i);
    }
}

void initializeBoard() {
    int num = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '.';
            numToCell[i][j] = num++;
            revealed[i][j] = false;
        }
    }
}

void printBoardNumbers() {
    int n = 1;
    for (int i = 4; i <= (4 + ROWS * 4 - 2); i += 4) {
        for (int j = 10; j <= (10 + COLS * 12 - 2); j += 12) {
            gotoRowCol(i + 2, j + 2);
            cout << n++;
        }
    }
}

void placeBombs() {
    srand(time(0));
    int placedBombs = 0;

    while (placedBombs < BOMBS) {
        int num = (rand() % (ROWS * COLS)) + 1; // Random number between 1 and ROWS*COLS

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (numToCell[i][j] == num && board[i][j] != 'B') {
                    board[i][j] = 'B';
                    placedBombs++;
                    break;
                }
            }

        }
    }
}

int countAdjacentBombs(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                if (board[newRow][newCol] == 'B') {
                    count++;
                }
            }
        }
    }
    return count;
}

bool revealCell(int row, int col) {
    if (revealed[row][col]) return true;
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return true;

    revealed[row][col] = true;
    int bombs = countAdjacentBombs(row, col);

    gotoRowCol(7 + row * 4 ,12 + col * 12 );
    if (bombs > 0) {
        cout << bombs;
    } else {
        cout << "0";


        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && !revealed[newRow][newCol]) {
                    revealCell(newRow, newCol);
                }
            }
        }
    }
    return false;
}

bool handleUserInput() {
    while (true) {
        int cellNum;
        gotoRowCol(42, 0);
        cout << "\nEnter a cell number (1-" << ROWS * COLS << "): ";
        cin >> cellNum;

        if (cellNum < 1 || cellNum > ROWS * COLS) {
            cout << "Invalid cell number! Try again.";
            continue;
        }


        int row = (cellNum - 1) / COLS;
        int col = (cellNum - 1) % COLS;

        if (board[row][col] == 'B') {

            gotoRowCol(45, 0);
            cout << "Boom! You hit a bomb. Game over!" << endl;
            return false;
        } else {
            revealCell(row, col);
        }


        bool won = true;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != 'B' && !revealed[i][j]) {
                    won = false;
                    break;
                }
            }
        }
        if (won) {
            gotoRowCol(45, 0);
            cout << "Congratulations! You cleared the board. You won!" << endl;
            return true;
        }
    }
}

void selectDifficulty() {
    int level;
    cout << "Select Difficulty Level:\n";
    cout << "1. Easy (5x5)\n";
    cout << "2. Medium (7x7)\n";
    cout << "3. Hard (9x9)\n";
    cout << "Enter your choice: ";
    cin >> level;

    switch (level) {
        case 1:
            ROWS = 5;
            COLS = 5;
            BOMBS = 5;
            break;
        case 2:
            ROWS = 7;
            COLS = 7;
            BOMBS = 10;
            break;
        case 3:
            ROWS = 9;
            COLS = 9;
            BOMBS = 15;
            break;
        default:
            cout << "Invalid choice! Defaulting to Hard (9x9).\n";
            ROWS = 9;
            COLS = 9;
            BOMBS = 15;
            break;
    }
}

void loadPlayerStats() {
    ifstream file("player_stats.txt");
    if (!file.is_open()) return;

    totalPlayers = 0;
    while (file >> players[totalPlayers].name >> players[totalPlayers].gamesPlayed
                >> players[totalPlayers].gamesWon >> players[totalPlayers].gamesLost) {
        totalPlayers++;
        if (totalPlayers >= MAX_PLAYERS) break;
    }
    file.close();
}

void savePlayerStats() {
    ofstream file("player_stats.txt", ios::trunc);
    if (!file.is_open()) return;

    for (int i = 0; i < totalPlayers; i++) {
        file << players[i].name << " " << players[i].gamesPlayed << " "
             << players[i].gamesWon << " " << players[i].gamesLost << "\n";
    }
    file.close();
}

int findPlayerIndex(const string& name) {
    for (int i = 0; i < totalPlayers; i++) {
        if (players[i].name == name) return i;
    }
    return -1;
}

void printAllPlayerStats() {
    cout << "\nAll Player Statistics:\n";
    cout << "---------------------------------------------------\n";
    cout << "Name\tGames Played\tGames Won\tGames Lost\n";
    cout << "---------------------------------------------------\n";
    for (int i = 0; i < totalPlayers; i++) {
        cout << players[i].name << "\t" << players[i].gamesPlayed << "\t\t"
             << players[i].gamesWon << "\t\t" << players[i].gamesLost << "\n";
    }
    cout << "---------------------------------------------------\n";
}

int main() {
    loadPlayerStats();

    string playerName;
    cout<<endl;
    cout << "Enter your name: ";
    cin >> playerName;
    cout<<endl;

    int playerIndex = findPlayerIndex(playerName);
    if (playerIndex == -1) {
        // New player
        playerIndex = totalPlayers++;
        players[playerIndex] = {playerName, 0, 0, 0};
    }

    selectDifficulty();
    gotoRowCol(9, 0);
    cout<<"INSTRUCTIONS :";
    cout<<endl;
    cout<<"Enter a number between 1 and "<<ROWS*COLS<<" to uncover the cell";
    cout<<endl;

    while (true) {
        int input;
        cout << "\nEnter any number to start or 0 to exit the game: ";
        cin >> input;

        if (input == 0) {
            cout << "\nThank you for playing!\n";
            savePlayerStats();
            printAllPlayerStats();
            break;
        }

        players[playerIndex].gamesPlayed++;
        system("CLS");

        initializeBoard();
        boardLayout();
        printBoardNumbers();
        placeBombs();

        bool result = handleUserInput();
        if (result) {
            players[playerIndex].gamesWon++;
        } else {
            players[playerIndex].gamesLost++;
        }
    }

    return 0;
}