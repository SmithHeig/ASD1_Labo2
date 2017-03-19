#include "P4.h"

using namespace std;

P4::P4(){
    board.resize(NB_LINES);
    for(unsigned i = 0; i < NB_LINES;++i){
        board.at(i).resize(NB_COLUMS);
        for(unsigned j = 0; j < NB_COLUMS; ++j){
            board.at(i).at(j) = 0;
        }
    }
}

void P4::reset(){
   
}
    
void P4::playInColumn(size_t c, Player p){
   
}
    
bool P4::isWinner(Player p) const{
   
}
    
bool P4::isValidMove(size_t c) const{
   
}
    
size_t P4::chooseNextMove(Player p, unsigned depth){
   
}

string P4::getName() const{
   
}

ostream& operator << ( std::ostream&, const P4& ){
    
}
