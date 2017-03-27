#include "P4.h"
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

P4::P4() {
    board.resize(NB_LINES);
    for (unsigned i = 0; i < NB_LINES; ++i) {
        board.at(i).resize(NB_COLUMNS);
        for (unsigned j = 0; j < NB_COLUMNS; ++j) {
            board.at(i).at(j) = EMPTY;
        }
    }
}

void P4::reset() {
    for (unsigned i = 0; i < NB_LINES; ++i) {
        for (unsigned j = 0; j < NB_COLUMNS; ++j) {
            board.at(i).at(j) = EMPTY;
        }
    }
}

void P4::playInColumn(size_t c, Player p) {
    if (isValidMove(c)) {
        for (unsigned i = 0; i < NB_LINES; ++i) {
            if (board.at(i).at(c) == EMPTY) {
                board.at(i).at(c) = p;
                currentColumn = c;
                currentLine = i;
                break;
            }
        }
    }
}

bool P4::isWinner(Player p) const {
    unsigned cmpt = 0;
    
    // Test diagonal 1
    int line = currentLine - 3;
    int col = currentColumn - 3;
    for (; col <= currentColumn + 3; ++col, ++line) {
        if (line >= 0 && line < NB_LINES && col >= 0 && col < NB_COLUMNS) {
            if (board.at(line).at(col) == p) {
                ++cmpt;
                if (cmpt == 4) {
                    return true;
                }
            } else {
                cmpt = 0;
            }
        }
    }

    cmpt = 0;
    line = currentLine - 3;
    col = currentColumn + 3;
    for (; col >= currentColumn - 3; --col, ++line) {
        if (line >= 0 && line < NB_LINES && col >= 0 && col < NB_COLUMNS ) {
            if (board.at(line).at(col) == p) {
                ++cmpt;
                if (cmpt == 4) {
                    return true;
                }
            } else {
                cmpt = 0;
            }
        }
    }
    
    // Test horizontal
    cmpt = 0;
    for (int i = 0; i < NB_COLUMNS; ++i) {
        if (board.at(currentLine).at(i) == p) {
            cmpt++;
            if (cmpt == 4) {
                return true;
            }
        } else {
            cmpt = 0;
        }
    }

    // Test vertical
    cmpt = 0;
    for (int i = int(currentLine); i >= 0; --i) {
        if (board.at(i).at(currentColumn) == p) {
            ++cmpt;
            if (cmpt == 4) {
                return true;
            }
        } else {
            cmpt = 0;
        }
    }

    // no winner
    return false;
}

bool P4::isValidMove(size_t c) const {
    if (c < NB_COLUMNS) {
        if (board.at(NB_LINES - 1).at(c) == EMPTY) {
            return true;
        }
    }
    return false;
}

size_t P4::chooseNextMove(Player p, unsigned depth) {
    P4 temp = *this;
    // initialising the random function 
    static bool first = true;
    if (first) {
        srand((unsigned int) time(NULL));
        first = !first;
    }

    vector<pair<int, int>> scores;
    scores.push_back(make_pair(0, -100000)); // set bestScore
    
    int playerScore;
    for (unsigned i = 0; i < NB_COLUMNS; ++i) {
        if (temp.isValidMove(i)) {
            playerScore = temp.bestScore(i, depth, -1000000, 1000000, p);
            cout << i << " " << playerScore << endl;
            if (playerScore >= scores.at(0).second) {
                if (playerScore == scores.at(0).second) {
                    scores.push_back(make_pair(i, playerScore));
                } else {
                    scores.clear();
                    scores.push_back(make_pair(i, playerScore));
                }
            }
        }
    }
    return scores.at(rand() % scores.size()).first;
}

string P4::getName() const {
   return CODERS_NAME;
}

ostream& operator<<(ostream& stream, const P4& p4) {
    for (int i = p4.NB_LINES - 1; i >= 0; --i) {
        for (int j = 0; j < p4.NB_COLUMNS; ++j) {
            stream << "|";
            if (p4.board.at(i).at(j) == X) {
                stream << "X";
            } else if (p4.board.at(i).at(j) == O) {
                stream << "O";
            } else {
                stream << " ";
            }
        }
        stream << "|" << endl;
    }
    for (unsigned i = 0; i < p4.NB_COLUMNS; ++i) {
        stream << " " << i;
    }
    stream << endl;
    return stream;
}

int P4::bestScore(int node, int depth, int a, int b, Player player) {
    //int heuristicValue = 100;
    int scoreOppenent = 0;
    int playerScore = -1000;
    P4 temp;
    temp = *this;

    temp.playInColumn(node, player);
    if (temp.isWinner(player)) {
        playerScore = depth; // to determinate
    }
    else if (depth == 0 || temp.isFull()) {
        playerScore = 0;
    } else {
        int bestValue = -1000000;
        for (unsigned i = 0; i < NB_COLUMNS; ++i) {
            if (temp.isValidMove(i)) {
                scoreOppenent = temp.bestScore(i, depth - 1, -1 * b, -1 * a, Player(-player));
                if(scoreOppenent > bestValue){
                    bestValue = scoreOppenent;
                }
                a = a > scoreOppenent ? a : scoreOppenent;
                if (a >= b) {
                    break;
                }
            }
        }
        playerScore = bestValue * -1;
    }
    return playerScore;
}

void P4::eraseMove(int line, int column) {
    board.at(line).at(column) = EMPTY;
}

void P4::operator = (const P4& p4) {
    board = p4.board;
    currentColumn = p4.currentColumn;
    currentLine = p4.currentLine;
}

bool P4::isFull() {
    for (unsigned i = 0; i < NB_COLUMNS; ++i) {
        if (board.at(NB_LINES - 1).at(i) == EMPTY) {
            return false;
        }
    }
    return true;
}


