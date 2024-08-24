#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

char board[MAX][MAX]; // 2D array to represent the chessboard

// Function to print the board
void print(int n) {
    int i, j;
    printf("Solution:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if it's safe to place a queen at position (r, c)
bool place(int r, int c, int n) {
    int i, j;
    // Check if there is a queen in the same column
    for (i = 0; i < r; i++) {
        if (board[i][c] == 'Q') {
            return false;
        }
    }
    // Check if there is a queen in the left diagonal
    for (i = r, j = c; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    // Check if there is a queen in the right diagonal
    for (i = r, j = c; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

// Function to solve the N-Queens problem recursively
void nqueens(int r, int n) {
    int c;
    // Base case: if all queens are placed
    if (r == n) {
        print(n);
        return;
    }
    // Try placing queen in each column of this row
    for (c = 0; c < n; c++) {
        if (place(r, c, n)) {
            // If it's safe to place queen at position (r, c), mark it and recursively try next row
            board[r][c] = 'Q';
            nqueens(r + 1, n);
            // Backtrack: remove queen from this position
            board[r][c] = '-';
        }
    }
}

int main() {
    int n, i, j;
    // Input the number of queens
    printf("Enter the number of queens (1 to %d): ", MAX);
    scanf("%d", &n);
    // Check if the input is valid
    if (n <= 0 || n > MAX) {
        printf("Invalid input. Number of queens must be between 1 and %d.\n", MAX);
        return 1;
    }
    // Initialize the chessboard with empty cells
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            board[i][j] = '-';
        }
    }
    // Solve the N-Queens problem starting from the first row
    nqueens(0, n);
    return 0;
}

