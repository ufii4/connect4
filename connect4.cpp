#include<iostream>

int main();

void startTheGame();

void printBoard(char board[6][7]);

void askForOperation(int &col, char player);

char *fitInTheMove(char board[6][7], int col, char player, int *turn);

bool checkWinStatus(char board[6][7], char &p_winner);

void markWinnerRow(char *p_start, char dir);

void initializeBoard(char (&board)[6][7]);

int main() {
    startTheGame();
}

void startTheGame() {
    //	Create the board as a char array
    char board[6][7];
    initializeBoard(board);

    for (int k = 1; true; k++) {
        char player{'x'};
        if ((k % 2) == 1) {
            player = 'x';
        } else {
            player = 'o';
        }
        printBoard(board);
        int col{0};
        askForOperation(col, player);
        if (col >= 0 && col <= 6) {
            fitInTheMove(board, col, player, &k);
            char winner{'_'};
            if (checkWinStatus(board, winner) && winner != '*') {
                printBoard(board);
                initializeBoard(board);
                std::cout << winner << " won" << std::endl
                          << "Play again? (y, n)";
                char y_or_n;
                std::cin >> y_or_n;
                bool resume = y_or_n == 'y';
                if (resume) {
                    initializeBoard(board);
                    k = 1;
                } else {
                    break;
                }
            } else if (winner == '*') {
                std::cout << "Draw!" << std::endl
                          << "Play again? (y, n)";
                char y_or_n;
                std::cin >> y_or_n;
                bool resume = y_or_n == 'y';
                if (resume) {
                    initializeBoard(board);
                    k = 1;
                } else {
                    break;
                }
            }
        } else {
// 			Bug fixed: Entering a column that is not on the board
            std::cout << "Please enter a valid column!" << std::endl
                      << "Resume? (y, n)";
            bool resume;
            char answer;
            std::cin >> answer;
            resume = ('y' == answer);
            if (resume) {
                k--;
            } else {
                break;
            }

        }
    }
    std::cout << "Game over!";
}

//	Print the current board to the console
void printBoard(char board[6][7]) {
    std::cout << 0 << ' ' << 1 << ' ' << 2 << ' ' << 3 << ' ' << 4 << ' ' << 5
              << ' ' << 6 << ' ' << std::endl;
    for (int k = 0; k < 6; k++) {
        for (int i = 0; i < 7; i++) {
            std::cout << board[k][i] << ' ';
        }
        std::cout << std::endl;
    }
}

//	Ask for player input
void askForOperation(int &col, char player) {
    std::cout << "Turn: " << player << std::endl << "Enter a col: ";
    std::cin >> col;
    std::cout << std::endl;
}


char *fitInTheMove(char board[6][7], int col, char player, int* turn) {
    int k = 6;
    while (board[k][col] != '_') {
        k--;
    }
// 	Bug fixed: Adding a move to the column that is full
    if (k < 0) {
        std::cout << "The board is too small :)" << std::endl;
        *turn = *turn - 1;
        return *board;
    }

    board[k][col] = player;
    return *board;
}

//	Check if there is a winner and if the board is full
bool checkWinStatus(char board[6][7], char &p_winner) {
    char dir;
    for (int col = 0; col < 4; col++) {
        for (int row = 5; row > 3; row--) {
            if ((board[row][col] != '_'
                 && board[row][col] == board[row - 1][col + 1])
                && (board[row][col] == board[row - 2][col + 2])
                && (board[row][col] == board[row - 3][col + 3])) {
                p_winner = board[row][col];
                dir = 'f';
                markWinnerRow(&board[row][col], dir);
                break;
            }
        }
        for (int row = 0; row < 3; row++) {
            if ((board[row][col] != '_'
                 && board[row][col] == board[row + 1][col + 1])
                && (board[row][col] == board[row + 2][col + 2])
                && (board[row][col] == board[row + 3][col + 3])) {
                p_winner = board[row][col];
                dir = 'd';
                markWinnerRow(&board[row][col], dir);
                break;
            }
        }
    }
    for (int col = 0; col < 7; col++) {
        for (int row = 5; row > 4; row--) {
            if ((board[row][col] != '_'
                 && board[row][col] == board[row - 1][col])
                && (board[row][col] == board[row - 2][col])
                && (board[row][col] == board[row - 3][col])) {
                p_winner = board[row][col];
                dir = 'v';
                markWinnerRow(&board[row][col], dir);
                break;
            }
        }
    }
    for (int row = 5; row >= 0; row--) {
        for (int col = 0; col < 4; col++) {
            if ((board[row][col] != '_'
                 && board[row][col] == board[row][col + 1])
                && (board[row][col] == board[row][col + 2])
                && (board[row][col] == board[row][col + 3])) {
                p_winner = board[row][col];
                dir = 'h';
                markWinnerRow(&board[row][col], dir);
                break;
            }
        }
    }

    for (int i = 0; i <= 6; i++) {
        if (board[0][i] == '_') {
            if (p_winner != '_') {
                return true;
            } else return false;
        }
    }
    p_winner = '*';
    return true;
}

//	Mark the row that ends the game
void markWinnerRow(char *p_start, char dir) {
    if (dir == 'f') {
        for (int i = 0; i < 4; i++) {
            *p_start = '*';
            p_start -= 6;
        }
    }
    if (dir == 'd') {
        for (int i = 0; i < 4; i++) {
            *p_start = '*';
            p_start += 8;
        }
    }
    if (dir == 'h') {
        for (int i = 0; i < 4; i++) {
            *p_start = '*';
            p_start += 1;
        }
    }
    if (dir == 'v') {
        for (int i = 0; i < 4; i++) {
            *p_start = '*';
            p_start -= 7;
        }
    }
}

// 	Fill the board with empty signs
void initializeBoard(char (&board)[6][7]) {
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 6; row++) {
            board[row][col] = '_';
        }
    }
}

