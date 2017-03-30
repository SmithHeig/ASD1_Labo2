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
        if (isInBoard(line, col)) {
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
        if (isInBoard(line, col)) {
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
    size_t j = 3;//colonne centrale 
    for (unsigned i = 0; i < NB_COLUMNS; ++i) {
        if (temp.isValidMove(i)) {
            playerScore = temp.bestScore(i, depth, -1000000, 1000000, p);
            cout << i << " " << playerScore << endl;
        }
       j+=(pow(-1, i+1))*i;//a expliquer
        if (temp.isValidMove(j)) {
            playerScore = temp.bestScore(j, depth, -1000000, 1000000, p);
            if (playerScore >= scores.at(0).second) {
                if (playerScore == scores.at(0).second) {
                    scores.push_back(make_pair(j, playerScore));
                } else {
                    scores.clear();
                    scores.push_back(make_pair(j, playerScore));
                }
            }
        }
    }
    for (size_t i = 0; i < scores.size() ; ++i){
       if (scores.at(i).first == 3) {
          return 3;
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
    int scoreOppenent = 0;
    int playerScore = -1000;
    P4 temp;
    temp = *this;

    temp.playInColumn(node, player);
    if (temp.isWinner(player) || depth == 0 || temp.isFull()) {
        playerScore = (depth + 1) * temp.heuristic(player); // to determinate
    } else {
        int bestValue = -1000000;
        for (unsigned i = 0; i < NB_COLUMNS; ++i) {
            if (temp.isValidMove(i)) {
                scoreOppenent = temp.bestScore(i, depth - 1, -1 * b, -1 * a, Player(-player));
                if (scoreOppenent > bestValue) {
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

void P4::operator=(const P4& p4) {
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

int P4::heuristic(Player p) {
    if (isWinner(p)) {
        return 100;
    } else {
        unsigned maxHorizontal = testHeuristicHorizontal(p);
        unsigned maxVertical = testHeuristicVertical(p);
        if(maxHorizontal >= maxVertical){
            return maxHorizontal;
        } else {
            return maxVertical;
        }
    }
}

int P4::testHeuristicHorizontal(Player p) {
    bool left = true;
    bool right = true;
    unsigned cmpt = 0;
    unsigned lastLeft = currentColumn;
    unsigned lastRight = currentColumn;
    for (int i = 0; i < 5; ++i) {
        // left
        if (currentColumn + i < NB_COLUMNS && board.at(currentLine).at(currentColumn + i) == p && right) {
            cmpt++;
        } else {
            // end right side
            if (right) {
                lastRight += i;
            }
            right = false;
        }
        // right
        if (currentColumn - i < 0 && isInBoard(currentLine, currentColumn - i) && board.at(currentLine).at(currentColumn - i) == p && left) {
            cmpt++;
        } else {
            //end left side
            if (left) {
                lastLeft -= i;
            }
            left = false;
        }
    }
    if (lastLeft >= 0 && lastRight < NB_COLUMNS && board.at(currentLine).at(lastRight) == EMPTY && board.at(currentLine).at(lastLeft) == EMPTY) {
        cout << "test" << endl;
        // _xxx_
        if (cmpt == 3) {
            return 90;
        }
            // _xx_
        else if (cmpt == 2) {
            return 50;
            // _x_
        } else {
            return 10;
        }
    } else if (((lastLeft < 0 || board.at(currentLine).at(lastLeft) != EMPTY) && lastRight < NB_COLUMNS &&
            board.at(currentLine).at(lastRight) == EMPTY)
            || ((lastRight >= NB_COLUMNS || board.at(currentLine).at(lastRight) != EMPTY) && lastLeft >= 0 &&
            board.at(currentLine).at(lastLeft) == EMPTY)) {
        // _xxxo or oxxx_
        if (cmpt == 3) {
            return 75;
            // _xxo or oxx_
        } else if (cmpt == 2) {
            return 25;
            // _xo or ox_
        } else {
            return 5;
        }
        // sourounded by enemey
    } else {
        return 1;
    }
}

int P4::testHeuristicVertical(Player p) {
    unsigned cmpt = 0;
        for(int i = currentLine; i >= 0; --i){
            if(board.at(i).at(currentColumn) == p){
                cmpt ++;
            }
            else {
                break;
            }
        }
        if(cmpt == 3) {
            return 50;
        } else if(cmpt == 2){
            return 20;
        } else {
            return 2;
        }
}

bool P4::isInBoard(int line, int col) const {
    return line >= 0 && line < NB_LINES && col >= 0 && col < NB_COLUMNS;
}