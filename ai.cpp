#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

void printBoard(const vector<vector<char>> &board) {
    cout << "\n";
    for (const auto &row : board) {
        for (int i = 0; i < row.size(); ++i) {
            cout << row[i];
            if (i < row.size() - 1) cout << " | ";
        }
        cout << "\n";
        if (&row != &board.back()) cout << "---------\n";
    }
    cout << "\n";
}

bool isMovesLeft(const vector<vector<char>> &board) {
    for (const auto &row : board)
        for (char cell : row)
            if (cell == EMPTY) return true;
    return false;
}

int evaluate(const vector<vector<char>> &board) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return 10;
            else if (board[row][0] == PLAYER) return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return 10;
            else if (board[0][col] == PLAYER) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return 10;
        else if (board[0][0] == PLAYER) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return 10;
        else if (board[0][2] == PLAYER) return -10;
    }
    return 0;
}

int minimax(vector<vector<char>> &board, int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>> &board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };
    int row, col;
    while (isMovesLeft(board) && evaluate(board) == 0) {
        printBoard(board);
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (board[row][col] != EMPTY) {
            cout << "Invalid move! Try again." << endl;
            continue;
        }
        board[row][col] = PLAYER;
        if (!isMovesLeft(board) || evaluate(board) != 0) break;
        pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = AI;
    }
    printBoard(board);
    int result = evaluate(board);
    if (result == 10) cout << "AI wins!\n";
    else if (result == -10) cout << "You win!\n";
    else cout << "It's a draw!\n";
    return 0;
}
