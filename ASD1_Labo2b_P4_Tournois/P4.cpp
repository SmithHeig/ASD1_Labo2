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

bool P4::isWinner(Player p) {
    int lastLeft = currentColumn,
            lastRight = currentColumn,
            pente = 0;
    unsigned cmptLine = nbSerieLine(p,lastRight,lastLeft),
            cmptColumn = nbSerieColumn(p),
            cmptDiago = nbSerieDiago(p,lastRight,lastLeft,pente);
    if(cmptLine == 4){
        return true;
    } else if(cmptColumn == 4){
        return true;
    } else if(cmptDiago == 4){
        return true;
    }
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

string P4::getName() const {
    return CODERS_NAME;
}

size_t P4::chooseNextMove(Player p, unsigned depth) {
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
        j+=size_t((pow(-1, i+1))*int(i));//a expliquer
        if (isValidMove(j)) {
            playerScore = bestScore(j, depth, -1000000, 1000000, p);
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

int P4::bestScore(int node, int depth, int a, int b, Player player) {
    int scoreOppenent = 0;
    int playerScore = -1000;
    playInColumn(node, player);
    unsigned col = currentColumn;
    unsigned line = currentLine;
    if (isWinner(player) || depth == 0 || isFull()) {
        playerScore = (depth + 1) * heuristic(player); // to determinate
    } else {
        int bestValue = -1000000;
        for (unsigned i = 0; i < NB_COLUMNS; ++i) {
            if (isValidMove(i)) {
                scoreOppenent = bestScore(i, depth - 1, -1 * b, -1 * a, Player(-player));
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
    board.at(line).at(col) = EMPTY;
    return playerScore;
}

unsigned P4::heuristic(Player p){
    if (isWinner(p)) {
        return 100;
    } else {
        unsigned maxHorizontal = testHeuristicHorizontal(p);
        unsigned maxVertical = testHeuristicVertical(p);
        unsigned maxDiago = testHeuriticDiago(p);
        if(maxHorizontal >= maxVertical && maxHorizontal >= maxDiago){
            return maxHorizontal;
        } else if(maxVertical >= maxHorizontal && maxVertical >= maxDiago){
            return maxVertical;
        } else if(maxDiago >= maxHorizontal && maxDiago >= maxVertical){
            return maxDiago;
        }
    }
}

unsigned P4::testHeuristicHorizontal(Player p) const{
    int lastLeft = currentColumn, 
            lastRight = currentColumn,
            currentPos = board.at(currentLine).at(lastLeft);
    unsigned cmpt = nbSerieLine(p,lastRight,lastLeft);
    if (lastLeft >= 0 && lastRight < int(NB_COLUMNS) && currentPos == EMPTY && currentPos == EMPTY) {
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
    } else if (((lastLeft < 0 || currentPos != EMPTY) && lastRight < int(NB_COLUMNS) &&
            currentPos == EMPTY)
            || ((lastRight >= int(NB_COLUMNS) || currentPos != EMPTY) && lastLeft >= 0 &&
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

unsigned P4::testHeuristicVertical(Player p) const{
    int cmpt = nbSerieColumn(p);
    if(cmpt == 3) {
        return 20;
    } else if(cmpt == 2){
        return 10;
    } else {
        return 2;
    }
}

unsigned P4::testHeuriticDiago (Player p) const{
    int lastLeft = currentColumn, 
            lastRight = currentColumn,
            pente = 0;
    unsigned cmpt = nbSerieDiago(p,lastRight, lastLeft,pente);
    int higthRight = currentLine + ((lastRight - currentLine) * pente);
    int higthLeft = currentLine - (currentLine - lastLeft * pente);
    bool isInBoardLeft = isInBoard(higthLeft,lastLeft);
    bool isInBoardRight = isInBoard(higthRight,lastRight);
    int posLeft;
    int posRight;
    if(isInBoardLeft){
        posLeft = board.at(higthLeft).at(lastLeft);
    } else {
        posLeft = -p;
    }
    if(isInBoardRight){
        posRight = board.at(higthRight).at(lastRight);
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
            return 50;
            // _x_
        } else {
            return 10;
        }
    } else if ((posLeft != EMPTY && posRight == EMPTY)
            || (posRight != EMPTY &&posLeft == EMPTY)) {
        // _xxxo or oxxx_
        if (cmpt == 3) {
            return 30;
            // _xxo or oxx_
        } else if (cmpt == 2) {
            return 20;
            // _xo or ox_
        } else {
            return 5;
        }
        // sourounded by enemey
    } else {
        return 1;
    }
    
}

unsigned P4::nbSerieDiago (Player p, int& lastRight, int& lastLeft, int& pente) const{
    int lastRightDiag1 = currentColumn,
            lastLeftDiag1 = currentColumn,
            lastRightDiag2 = currentColumn,
            lastLeftDiag2 = currentColumn;
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
                lastRightDiag1 += i;
            }
            rightDiag1 = false;
        }
        if(i > 0) {
            if(int(currentColumn) - i >= 0 && int(currentLine) - i >= 0  && board.at(int(currentLine) - i).at(int(currentColumn) - i) == p && leftDiag1){
                ++cmptDiag1;
            } else {
                if(leftDiag1){
                    lastLeftDiag1 += i;
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
                lastRightDiag2 += i;
            }
            rightDiag2 = false;
        }
        if(i > 0){
            if(int(currentColumn) - i >= 0 && currentLine + i < NB_LINES  && board.at(currentLine + i).at(int(currentColumn) - i) == p && leftDiag2){
                cmptDiag2 ++;
            } else {
                if(leftDiag2){
                    lastLeftDiag2 += i;
                }
                leftDiag2 = false;
            }
        }
        
    }
    if(cmptDiag1 >= cmptDiag2){
        lastLeft = lastLeftDiag1;
        lastRight = lastRightDiag1;
        pente = 1;
        return cmptDiag1;
    } else{
        lastLeft = lastLeftDiag2;
        lastRight = lastRightDiag2;
        pente = -1;
        return cmptDiag2;
    }
}
 
unsigned P4::nbSerieLine(Player p, int& lastRight, int& lastLeft) const{
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
                lastRight += i;
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
                    lastLeft -= i;
                }
                left = false;
            }
        }
    }
    return cmpt;
}

unsigned P4::nbSerieColumn(Player p) const{
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

bool P4::isInBoard(int line, int col) const {
    return line >= 0 && line < int(NB_LINES) && col >= 0 && col < int(NB_COLUMNS);
}

void P4::operator=(const P4& p4) {
    board = p4.board;
    currentColumn = p4.currentColumn;
    currentLine = p4.currentLine;
}

bool P4::isFull() const{
    for (unsigned i = 0; i < NB_COLUMNS; ++i) {
        if (board.at(NB_LINES - 1).at(i) == EMPTY) {
            return false;
        }
    }
    return true;
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
