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

void P4::playInColumn(unsigned column, Player p) {
    if (isValidMove(column)) {
        for (unsigned i = 0; i < NB_LINES; ++i) {
            if (board.at(i).at(column) == EMPTY) {
                board.at(i).at(column) = p;
                currentColumn = column;
                currentLine = i;
                break;
            }
        }
    }
}

bool P4::isValidMove(unsigned column) const {
    if (column < NB_COLUMNS) {
        if (board.at(NB_LINES - 1).at(column) == EMPTY) {
            return true;
        }
    }
    return false;
}

unsigned P4::chooseNextMove(Player p, unsigned depth) {
    // initialising the random function 
    static bool first = true;
    if (first) {
        srand((unsigned int) time(NULL));
        first = !first;
    }

    vector<pair<int, int>> bestScores;
    bestScores.push_back(make_pair(0, -100000)); // set bestScore

    int playerScore;
    unsigned j = 3;//start from the central column
    for (unsigned i = 0; i < NB_COLUMNS; ++i) {
        j += unsigned((pow(-1 , i + 1)) * int(i));//column 3 4 2 5 1 6 0
        if (isValidMove(j)) {
            playerScore = scoreMove(j, depth, -1000000, 1000000, p);
            cout << j << " " << playerScore << endl;
            if (playerScore >= bestScores.at(0).second) {
                if (playerScore == bestScores.at(0).second) {
                    bestScores.push_back(make_pair(j, playerScore));
                } else {
                    bestScores.clear();
                    bestScores.push_back(make_pair(j, playerScore));
                }
            }
        }
    }
    for (unsigned i = 0; i < bestScores.size() ; ++i){
       if (bestScores.at(i).first == 3) {
          return 3;
       }
    }    
    return bestScores.at(rand() % bestScores.size()).first;
}

int P4::scoreMove(const int column, int depth, int alpha, int beta, const Player player) {
    int scoreOppenent = 0;
    int playerScore = -1000;
    playInColumn(column, player);
    unsigned col = currentColumn;
    unsigned line = currentLine;
    if (isWinner(player) || depth == 0 || isFull()) {
        playerScore = (depth + 1) * heuristic(player); // to determinate
    } else {
        int bestValue = -1000000;
        for (unsigned i = 0; i < NB_COLUMNS; ++i) {
            if (isValidMove(i)) {
                scoreOppenent = scoreMove(i, depth - 1, -1 * beta, -1 * alpha, Player(-player));
                if (scoreOppenent > bestValue) {
                    bestValue = scoreOppenent;
                }
                alpha = alpha > scoreOppenent ? alpha : scoreOppenent;
                if (alpha >= beta) {
                    break;
                }
            }
        }
        playerScore = bestValue * -1;
    }
    board.at(line).at(col) = EMPTY;
    return playerScore;
}

bool P4::isWinner(const Player& p) {
    int firstEl = currentColumn,
            lastEl = currentColumn,
            slope = 0;
    unsigned cmptLine = nbSerieLine(p,lastEl,firstEl),
            cmptColumn = nbSerieColumn(p),
            cmptDiago = nbSerieDiago(p,lastEl,firstEl,slope);
    if(cmptLine == 4){
        return true;
    } else if(cmptColumn == 4){
        return true;
    } else if(cmptDiago == 4){
        return true;
    }
    return false;
}

unsigned P4::heuristic(const Player& p){
    if (isWinner(p)) {
        return 100;
    } else {
        unsigned maxHorizontal = testHeuristicHorizontal(p);
        unsigned maxVertical = testHeuristicVertical(p);
        unsigned maxDiago = testHeuriticDiago(p);
        // << maxHorizontal << " " << maxVertical << " " << maxDiago << endl;
        if(maxHorizontal >= maxVertical && maxHorizontal >= maxDiago){
            return maxHorizontal;
        } else if(maxVertical >= maxHorizontal && maxVertical >= maxDiago){
            return maxVertical;
        } else if(maxDiago >= maxHorizontal && maxDiago >= maxVertical){
            return maxDiago;
        }
    }
    return 0;
}

unsigned P4::testHeuristicHorizontal(const Player& p) const{
    int firstEl = currentColumn, 
            lastEl = currentColumn,
            currentPos = board.at(currentLine).at(currentColumn);
    unsigned cmpt = nbSerieLine(p,lastEl,firstEl);
    if (firstEl >= 0 && lastEl < int(NB_COLUMNS) && currentPos == EMPTY && currentPos == EMPTY) {
        // _xxx_
        if (cmpt == 3) {
            return 90;
        }
        // _xx_
        else if (cmpt == 2) {
            return 60;
        // _x_
        } else {
            return 10;
        }
    } else if (((firstEl < 0 || currentPos != EMPTY) && lastEl < int(NB_COLUMNS) &&
            currentPos == EMPTY)
            || ((lastEl >= int(NB_COLUMNS) || currentPos != EMPTY) && firstEl >= 0 &&
            currentPos == EMPTY)) {
        // _xxxo or oxxx_
        if (cmpt == 3) {
            return 50;
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

unsigned P4::testHeuristicVertical(const Player& p) const{
    int cmpt = nbSerieColumn(p);
    if(cmpt == 3) {
        return 20;
    } else if(cmpt == 2){
        return 10;
    } else {
        return 2;
    }
}

unsigned P4::testHeuriticDiago (const Player& p) const{
    int firstEl = currentColumn, 
            lastEl = currentColumn,
            slope = 0;
    unsigned cmpt = nbSerieDiago(p,lastEl, firstEl,slope);
    int higthRight = currentLine + ((lastEl - currentLine) * slope);
    int higthLeft = currentLine - (currentLine - firstEl * slope);
    bool isInBoardLeft = isInBoard(higthLeft,firstEl);
    bool isInBoardRight = isInBoard(higthRight,lastEl);
    int posLeft;
    int posRight;
    if(isInBoardLeft){
        posLeft = board.at(higthLeft).at(firstEl);
    } else {
        posLeft = -p;
    }
    if(isInBoardRight){
        posRight = board.at(higthRight).at(lastEl);
    } else {
        posRight = -p;
    }
    if(posLeft == EMPTY && posRight == EMPTY){
        // _
        // 0x
        // 00x
        // 000x
        // 0x0x_
        if (cmpt == 3) {
            return 90;
        }
            // _xx_
        else if (cmpt == 2) {
            return 20;
            // _x_
        } else {
            return 10;
        }
    } else if ((posLeft != EMPTY && posRight == EMPTY)
            || (posRight != EMPTY && posLeft == EMPTY)) {
        // _xxxo or oxxx_
        if (cmpt == 3) {
            return 30;
            // _xxo or oxx_
        } else if (cmpt == 2) {
            return 15;
            // _xo or ox_
        } else {
            return 5;
        }
        // sourounded by enemey
    } else {
        return 1;
    }
    
}

unsigned P4::nbSerieDiago (const Player& p, int& lastEl, int& firstEl, int& slope) const{
    int lastElDiag1 = currentColumn,
            firstElDiag1 = currentColumn,
            lastElDiag2 = currentColumn,
            firstElDiag2 = currentColumn;
    bool rightDiag1 = true,
            leftDiag1 = true,
            rightDiag2 = true,
            leftDiag2 = true;
    unsigned cmptDiag1 = 0,
            cmptDiag2 = 0;
   
    for(int i = 0; i < 4; ++i){
        // Diag 1
        if(currentColumn + i < NB_COLUMNS && currentLine + i < NB_LINES  && board.at(currentLine + i).at(currentColumn + i) == p&& rightDiag1){
            ++cmptDiag1;
        } else {
            // end right side
            if (rightDiag1) {
                lastElDiag1 += i;
            }
            rightDiag1 = false;
        }
        if(i > 0) {
            if(int(currentColumn) - i >= 0 && int(currentLine) - i >= 0  && board.at(int(currentLine) - i).at(int(currentColumn) - i) == p && leftDiag1){
                ++cmptDiag1;
            } else {
                if(leftDiag1){
                    firstElDiag1 += i;
                }
                leftDiag1 = false;
            }
        }
        
        // Diag 2
        if(currentColumn + i < NB_COLUMNS && int(currentLine) - i >= 0 && board.at(int(currentLine) - i).at(currentColumn + i) == p && rightDiag2){
            ++cmptDiag2;
        } else {
            // end right side
            if (rightDiag2) {
                lastElDiag2 += i;
            }
            rightDiag2 = false;
        }
        if(i > 0){
            if(int(currentColumn) - i >= 0 && currentLine + i < NB_LINES  && board.at(currentLine + i).at(int(currentColumn) - i) == p && leftDiag2){
                cmptDiag2 ++;
            } else {
                if(leftDiag2){
                    firstElDiag2 += i;
                }
                leftDiag2 = false;
            }
        }
        
    }
    if(cmptDiag1 >= cmptDiag2){
        firstEl = firstElDiag1;
        lastEl = lastElDiag1;
        slope = 1;
        return cmptDiag1;
    } else{
        firstEl = firstElDiag2;
        lastEl = lastElDiag2;
        slope = -1;
        return cmptDiag2;
    }
}
 
unsigned P4::nbSerieLine(const Player& p, int& lastEl, int& firstEl) const{
    bool left = true;
    bool right = true;
    unsigned cmpt = 0;
    for (int i = 0; i < 4; ++i) {
        // right
        if (currentColumn + i < NB_COLUMNS && board.at(currentLine).at(currentColumn + i) == p && right) {
            ++cmpt;
        } else {
            // end right side
            if (right) {
                lastEl += i;
            }
            right = false;
        }
        // left
        if(i > 0){
            if (int(currentColumn) - i >= 0 && board.at(int(currentLine)).at(int(currentColumn) - i) == p && left) {
                ++cmpt;
            } else {
                //end left side
                if (left) {
                    firstEl -= i;
                }
                left = false;
            }
        }
    }
    return cmpt;
}

unsigned P4::nbSerieColumn(const Player& p) const{
    unsigned cmpt = 0;
    for(int i = currentLine; i >= 0; --i){
        if(board.at(i).at(currentColumn) == p){
            ++cmpt;
        }
        else {
            break;
        }
    }
    return cmpt;
}

bool P4::isInBoard(const int line, const int col) const {
    return line >= 0 && line < int(NB_LINES) && col >= 0 && col < int(NB_COLUMNS);
}

bool P4::isFull() const{
    for (unsigned i = 0; i < NB_COLUMNS; ++i) {
        if (board.at(NB_LINES - 1).at(i) == EMPTY) {
            return false;
        }
    }
    return true;
}

string P4::getName() const {
    return CODERS_NAME;
}

void P4::operator = (const P4& p4) {
    board = p4.board;
    currentColumn = p4.currentColumn;
    currentLine = p4.currentLine;
}

ostream& operator << (ostream& stream, const P4& p4) {
    for (int i = p4.NB_LINES - 1; i >= 0; --i) {
        for (int j = 0; j < int(p4.NB_COLUMNS); ++j) {
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