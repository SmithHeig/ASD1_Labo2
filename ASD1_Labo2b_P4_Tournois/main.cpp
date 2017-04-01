// REMPLACER LES 2 LIGNES QUI SUIVENT PAR L'INCLUSION
// ET LA DEFINITION DE P4Type COMME ETANT VOTRE
// CLASSE P4

#include "P4.h"
using P4Type = P4;

// NE RIEN CHANGER DANS CE QUI SUIT

#include <iostream>
#include <iomanip>
#include <chrono>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

#include "P4Aleatoire.h"
#include "P4CentreAleatoire.h"

typedef std::chrono::high_resolution_clock Clock;

bool play( P4Interface& p1, P4Interface& p2, P4Type& ref,
          Player XO, int cnt, const int MAX_TIME, bool verbose
          )
{
    unsigned depth = 0;
    
    Clock::time_point t1,t2;
    
    do {
        depth++;
        t1 = Clock::now();
        p1.chooseNextMove(XO,depth);
        t2 = Clock::now();
    } while (depth < 43-cnt and chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() < MAX_TIME);
    depth--;

    if(verbose)
        cout << depth;
    size_t c = p1.chooseNextMove(XO,depth);
    p1.playInColumn( c , XO);
    p2.playInColumn( c , XO);
    ref.playInColumn( c , XO);
    if(verbose)
        cout << ref;
    return ref.isWinner(XO);
}

Player match(P4Interface* player1,
             P4Interface* player2,
             const int MAX_TIME,
             bool verbose = true) {
    
    player1->reset();
    player2->reset();
    
    P4Type referee;
    Player winner = EMPTY;
    
    for (int i = 0; i < 42; ) {
        if( play(*player1,*player2,referee,X,i++,MAX_TIME,verbose) ) {
            winner = X; break;
        }
        if( play(*player2,*player1,referee,O,i++,MAX_TIME,verbose) ) {
            winner = O; break;
        }
    }

    return winner;
}

void ShowResultsGrid ( const vector<vector<int>>& wins, const vector<P4Interface*>& players)
{
    cout << endl;
    
    const int W = 5;
    cout << setw(W) << " ";
    for (size_t i1 = 0; i1 < players.size(); ++i1)
        cout << setw(W) << players[i1]->getName().substr(0,W-1);
    cout << endl;
    
    for (size_t i1 = 0; i1 < players.size(); ++i1) {
        cout << setw(W) << players[i1]->getName();
        for (size_t i2 = 0; i2 < players.size(); ++i2) {
            cout << setw(W);
            if ( i1 == i2 ) cout << "*";
            else cout << wins[i1][i2] ;
        }
        cout << endl;
    }

cout << endl;

}
int main() {

    const unsigned nbOfTries = 5;
    const int timeOfTries = 10;
    
    srand ( (int) time(0) );

    vector<P4Interface*> players;
    
    players.push_back(new P4Aleatoire);
    players.push_back(new P4CentreAleatoire);
    players.push_back(new P4Type);
    
    vector<vector<int>> wins(players.size(),vector<int>(players.size()));
    vector<vector<int>> ties(players.size(),vector<int>(players.size()));
    vector<vector<int>> losses(players.size(),vector<int>(players.size()));
    
    for (size_t i1 = 0; i1 < players.size(); ++i1) {
        for (size_t i2 = 0; i2 < players.size(); ++i2) {
            if (i1 != i2) {
                for (unsigned t = 0; t < nbOfTries; ++t) {
                    cout << '.'; cout.flush();
                    Player winner = match(players[i1], players[i2], timeOfTries, false );
                    wins[i1][i2] += (winner == X);
                    ties[i1][i2] += (winner == EMPTY);
                    losses[i1][i2] += (winner == O);
                }
            }
        }
    }
    cout << endl;
    
    cout << "Wins";
    ShowResultsGrid(wins,players);
    cout << "Ties";
    ShowResultsGrid(ties,players);
    cout << "Losses";
    ShowResultsGrid(losses,players);
    
    vector<tuple<int,int,int,string>> results;
    
    for (size_t i1 = 0; i1 < players.size(); ++i1) {
        int won = 0;
        int tied = 0;
        for (size_t i2 = 0; i2 < players.size(); ++i2) {
            won += wins[i1][i2];
            tied += ties[i1][i2];
            won += losses[i2][i1];
            tied += ties[i2][i1];
        }
        results.push_back(make_tuple(3*won+tied, won, tied, players[i1]->getName() ) );
    }
    
    sort(results.rbegin(),results.rend());

    const int W = 5;
    cout << endl << setw(W) << "Algo" << setw(W) << "Pts" << setw(W) << "Wins" << setw(W)
    << "Ties" << endl << endl;
    for (size_t i = 0; i < players.size(); ++i) {
        cout << setw(W) << get<3>(results[i]).substr(0,W-1)
        << setw(W) << get<0>(results[i])
        << setw(W) << get<1>(results[i])
        << setw(W) << get<2>(results[i])
        << endl;
    }
    
    for (auto& p : players) {
        delete p;
    }
}
