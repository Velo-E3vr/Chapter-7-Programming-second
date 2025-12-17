#include <iostream>
using namespace std;

const int SIZE = 3;

void initBoard(char board[SIZE][SIZE]);
void displayBoard(const char board[SIZE][SIZE]);
bool isValidMove(const char board[SIZE][SIZE], int row, int col);
void makeMove(char board[SIZE][SIZE], int row, int col, char player);
bool hasWinner(const char board[SIZE][SIZE], char player);
bool isTie(const char board[SIZE][SIZE]);
void switchPlayer(char& player);

int main() {
    char board[SIZE][SIZE];
    initBoard(board);

    char player = 'X';
    int row, col;

    while (true) {
        displayBoard(board);

        // Input loop until a legal move is entered
        cout << "Player " << player << ", enter row and column (1-3 1-3): ";
        cin >> row >> col;

        // convert to 0-based indexes
        row--; col--;

        while (!isValidMove(board, row, col)) {
            cout << "Invalid move. Try again (row col): ";
            cin >> row >> col;
            row--; col--;
        }

        makeMove(board, row, col, player);

        if (hasWinner(board, player)) {
            displayBoard(board);
            cout << "Player " << player << " wins!\n";
            break;
        }

        if (isTie(board)) {
            displayBoard(board);
            cout << "It's a tie!\n";
            break;
        }

        switchPlayer(player);
    }

    return 0;
}

/*********************************************************************
 * Function: initBoard
 * Description: Fills board with spaces.
 *********************************************************************/
void initBoard(char board[SIZE][SIZE]) {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            board[r][c] = ' ';
}

/*********************************************************************
 * Function: displayBoard
 * Description: Prints current board state.
 *********************************************************************/
void displayBoard(const char board[SIZE][SIZE]) {
    cout << "\n  1   2   3\n";
    for (int r = 0; r < SIZE; r++) {
        cout << r + 1 << " ";
        for (int c = 0; c < SIZE; c++) {
            cout << board[r][c];
            if (c < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (r < SIZE - 1) cout << " ---+---+---\n";
    }
    cout << "\n";
}

/*********************************************************************
 * Function: isValidMove
 * Description: Checks range and empty spot.
 *********************************************************************/
bool isValidMove(const char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    return board[row][col] == ' ';
}

/*********************************************************************
 * Function: makeMove
 * Description: Places player's mark.
 *********************************************************************/
void makeMove(char board[SIZE][SIZE], int row, int col, char player) {
    board[row][col] = player;
}

/*********************************************************************
 * Function: hasWinner
 * Description: Checks rows, cols, diagonals for 3 in a row.
 *********************************************************************/
bool hasWinner(const char board[SIZE][SIZE], char player) {
    // Rows
    for (int r = 0; r < SIZE; r++) {
        if (board[r][0] == player && board[r][1] == player && board[r][2] == player)
            return true;
    }

    // Columns
    for (int c = 0; c < SIZE; c++) {
        if (board[0][c] == player && board[1][c] == player && board[2][c] == player)
            return true;
    }

    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

/*********************************************************************
 * Function: isTie
 * Description: Tie if no empty spaces left.
 *********************************************************************/
bool isTie(const char board[SIZE][SIZE]) {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (board[r][c] == ' ')
                return false;
    return true;
}

/*********************************************************************
 * Function: switchPlayer
 * Description: Alternates X and O.
 *********************************************************************/
void switchPlayer(char& player) {
    player = (player == 'X') ? 'O' : 'X';
}
