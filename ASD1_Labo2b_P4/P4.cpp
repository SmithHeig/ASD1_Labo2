#include "P4.h"
#include <iostream>
#include <ctime>
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
    // Test horizontal
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

    // Test diagonal 1
    cmpt = 0;
    int line = currentLine - 3;
    int col = currentColumn - 3;
    for (; col < int(currentColumn) + 3; ++col, ++line) {
        if (line >= 0 && line < NB_LINES && isValidMove(col)) {
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
    for (; col > int(currentColumn) - 3; --col, ++line) {
        cout << line << " " << col << endl;
        if (line >= 0 && line < NB_LINES && isValidMove(col)) {
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
    // initialising the random function
    static bool first = true;
    if (first) {
       srand ((unsigned int)time (NULL));
       first = !first;
    }
    
    vector<pair<int,int>> scores;
    scores.at(0) = make_pair(0,-100000); // set bestScore
    int playerScore;
    for(unsigned i = 0; i < NB_COLUMNS; ++i){
        if(isValidMove(i)){
            playerScore = bestScore(i,depth,p);
            if(playerScore >= scores.at(0).second){
                if(playerScore == scores.at(0).second){
                    scores.push_back(make_pair(i,playerScore));
                } else {
                    scores.clear();
                    scores.push_back(make_pair(i,playerScore));
                }
            }
        }
    }
    return scores.at(rand() % scores.size()).first;
}

string P4::getName() const {

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

int P4::bestScore(int node, int depth, Player player) {
    int heuristicValue = 10;
    int score;
    playInColumn(node, player);
    if (depth == 0 || isWinner(player)) {
        return player * heuristicValue; // to determinate
    }

    int bestValue = -1000000;
    for (unsigned i = 0; i < NB_LINES; ++i) {
        for (unsigned j = 0; j < NB_COLUMNS; ++j) {
            if (isValidMove(j)) {
                score = bestScore(j, depth - 1, Player(-player)) * -1;
                bestValue = bestValue < score ? score: bestValue;
            }
        }
    }
    board.at(currentLine).at(currentColumn) == EMPTY; // Reset du coups jouer
    return bestValue;
}
