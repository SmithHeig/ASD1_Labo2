//
//  P4Aleatoire.cpp
//
//  Created by Olivier Cuisenaire on 08.03.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//

#include "P4Aleatoire.h"

using namespace std;

P4Aleatoire::P4Aleatoire()
{
    reset();
}

void P4Aleatoire::reset() {
    counts.assign(COLS,0);
}

void P4Aleatoire::playInColumn(size_t c, Player p)
{
    counts[c]++;
}

size_t P4Aleatoire::chooseNextMove(Player p, unsigned depth)
{
    unsigned c;
    do {
        c = rand() % COLS;
    }
    while( counts[c] >= ROWS );
    return c;
}
