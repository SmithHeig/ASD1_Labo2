//
//  Board.hpp
//  Tic Tac Toe
//
//  Created by Olivier Cuisenaire on 07.03.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <cstdlib>
#include <string>

enum Player { O = -1, EMPTY = 0, X = 1 };

class P4Interface {
public:
    virtual std::string getName() const = 0;
    virtual size_t chooseNextMove(Player p, unsigned depth) = 0;
    virtual void playInColumn(size_t c, Player p) = 0;
    virtual void reset() = 0;
    virtual ~P4Interface() { }
};

#endif /* Board_hpp */
