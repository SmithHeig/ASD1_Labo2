#include "P4.h"
#include <iostream>
using namespace std;

P4::P4(){
    board.resize(NB_LINES);
    for(unsigned i = 0; i < NB_LINES;++i){
        board.at(i).resize(NB_COLUMNS);
        for(unsigned j = 0; j < NB_COLUMNS; ++j){
            board.at(i).at(j) = EMPTY;
        }
    }
}

void P4::reset(){
   
}
    
void P4::playInColumn(size_t c, Player p){
    if(isValidMove(c)){
        for(unsigned i = 0; i < NB_LINES; ++i){
            if(board.at(i).at(c) == EMPTY){
                board.at(i).at(c) = p;
                break;
            }
        }
        current_column = c;
    }
}
    
bool P4::isWinner(Player p) const{
    return false;
}
    
bool P4::isValidMove(size_t c) const{
    if(c < NB_COLUMNS){
        if(board.at(NB_LINES - 1).at(c) == EMPTY){
            return true;
        }
    }
    return false;
}
    
size_t P4::chooseNextMove(Player p, unsigned depth){
   
}

string P4::getName() const{
   
}

ostream& operator << (ostream& stream, const P4& p4){
    for(int i = p4.NB_LINES-1; i >= 0; --i){
        for(int j = 0; j < p4.NB_COLUMNS; ++j){
            stream << " " << p4.board.at(i).at(j) ;
        }
        stream << endl;
    }
    for(unsigned i = 0; i < p4.NB_COLUMNS; ++i){
        stream << " " << i;
    }
    stream << endl;
    return stream;
}
