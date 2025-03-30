#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Function declarations
void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);
bool isValidMove(char board[3][3], int position);
void makeMove(char board[3][3], int position, char symbol);
bool checkWin(char board[3][3], char symbol);
bool isBoardFull(char board[3][3]);
void convertPosition(int position, int *row, int *col);

int main() {
    char board[3][3];
    char player1, player2, currentPlayer;
    bool gameRunning = true;
    char playAgain;

    // Seed random number generator
    srand(time(NULL));

    do {
        // Initialize the board
        initializeBoard(board);

        // Randomly assign X and O
        if (rand() % 2 == 0) {
            player1 = 'X';
            player2 = 'O';
        } else {
            player1 = 'O';
            player2 = 'X';
        }

        // Randomly select who goes first
        currentPlayer = (rand() % 2 == 0) ? player1 : player2;

        printf("Player 1 is %c\n", player1);
        printf("Player 2 is %c\n", player2);
        printf("Player with %c goes first!\n", currentPlayer);

        while (gameRunning) {
            int position;
            displayBoard(board);

            printf("Player (%c), enter position (1-9): ", currentPlayer);
            scanf("%d", &position);

            if (position < 1 || position > 9) {
                printf("Invalid position! Please enter a number between 1 and 9.\n");
                continue;
            }

            if (!isValidMove(board, position)) {
                printf("Position already taken! Try again.\n");
                continue;
            }

            makeMove(board, position, currentPlayer);

            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                printf("Player %c wins!\n", currentPlayer);
                gameRunning = false;
            } else if (isBoardFull(board)) {
                displayBoard(board);
                printf("Game is a tie!\n");
                gameRunning = false;
            } else {
                currentPlayer = (currentPlayer == player1) ? player2 : player1;
            }
        }

        printf("Would you like to play again? (y/n): ");
        scanf(" %c", &playAgain);
        if (playAgain == 'y' || playAgain == 'Y') {
            gameRunning = true;
        }
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}

void initializeBoard(char board[3][3]) {
    int num = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num + '0';
            num++;
        }
    }
}

void displayBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

void convertPosition(int position, int *row, int *col) {
    position--; // Convert to 0-based index
    *row = position / 3;
    *col = position % 3;
}

bool isValidMove(char board[3][3], int position) {
    int row, col;
    convertPosition(position, &row, &col);
    return board[row][col] != 'X' && board[row][col] != 'O';
}

void makeMove(char board[3][3], int position, char symbol) {
    int row, col;
    convertPosition(position, &row, &col);
    board[row][col] = symbol;
}

bool checkWin(char board[3][3], char symbol) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}