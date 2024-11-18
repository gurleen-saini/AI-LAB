#include <iostream>
#include <time.h>
using namespace std;

int rows, cols;  
int countSolutions = 0; 

void printBoard(int **board) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool canPlace(int **board, int row, int col) {
    int moves[8][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };

    for (int i = 0; i < 8; i++) {
        int newRow = row + moves[i][0];
        int newCol = col + moves[i][1];
        
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
            if (board[newRow][newCol] == 1) {
                return false; 
            }
        }
    }
    return true;
}

void Nknights(int **board, int knightsLeft, int row, int col) {
    if (knightsLeft == 0) {
        countSolutions++;
        cout << "Solution " << countSolutions << ":" << endl;
        printBoard(board);
        return;
    }

    if (row >= rows) return;

    if (col >= cols) {
        Nknights(board, knightsLeft, row + 1, 0);
        return;
    }

    int cellsLeft = (rows * cols) - (row * cols + col);
    if (cellsLeft < knightsLeft) return;

    if (canPlace(board, row, col)) {
        board[row][col] = 1;  
        Nknights(board, knightsLeft - 1, row, col + 1);
        board[row][col] = 0;
    }

    Nknights(board, knightsLeft, row, col + 1);
}

int main() {
    double startTime, endTime, totalTime;
    cout << "Enter size of board (rows and columns): ";
    cin >> rows >> cols;

    int **board = new int*[rows]; 
    for (int i = 0; i < rows; i++) {
        board[i] = new int[cols]();
    }

    cout << "Enter number of knights: ";
    int knights;
    cin >> knights;

    startTime = clock();
    Nknights(board, knights, 0, 0); 
    endTime = clock();
    totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC; // Correct time calculation

    if (countSolutions == 0) {
        cout << "No solution exists!" << endl;
    } else {
        cout << "Total solutions: " << countSolutions << endl;
    }
    cout << "Time taken: " << totalTime << " seconds" << endl;

    for (int i = 0; i < rows; i++) {
        delete[] board[i]; 
    }
    delete[] board;

    return 0;
}
