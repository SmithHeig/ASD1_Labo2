//
//  P4Aleatoire.h
//  Tic Tac Toe
//
//  Created by Olivier Cuisenaire on 08.03.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//  P4Aleatoire.h
//
//  Created by Olivier Cuisenaire on 08.03.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//

#ifndef P4Aleatoire_h
#define P4Aleatoire_h

#include "P4Interface.h"
#include <vector>

class P4Aleatoire : public P4Interface {

    static const int COLS = 7;
    static const int ROWS = 6;
    std::vector<size_t> counts;

public:

    P4Aleatoire();
    void reset();
    void playInColumn(size_t c, Player p);
    size_t chooseNextMove(Player p, unsigned depth = ROWS);
    std::string getName() const { return "ALEA"; }
};

#endif /* P4Aleatoire_h */
