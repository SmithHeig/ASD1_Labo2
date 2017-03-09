//
//  TicTacToe.cpp
//
//  Created by Olivier Cuisenaire on 18.02.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
using namespace std;

//
// Variables globales
//

// les joueurs sont +1 et -1. 0 pour les cases vides
const int X = 1, O = -1, EMPTY = 0;

// tableau de 3x3 cases.
int board[3][3];

/////////////////////////////////////////////////

//
// Fonctions
//

// calcule la ligne correspondant à un movement
// de 1 à 9.
int iFromN(int n) {
    return (n-1)/3;
}
// calcule la colonne correspondant à un movement
// de 1 à 9.
int jFromN(int n) {
    return (n-1)%3;
}

// efface le tableau
void clearBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = EMPTY;
}

// applique un movement en mettant à
// currentPlayer la case du tableau
// correspondante.
void applyMove(int n, int player) {
    int i = iFromN(n);
    int j = jFromN(n);
    board[i][j] = player;
}

void eraseMove(int n) {
    applyMove(n,EMPTY);
}

// verifie sur le joueur est gagnant.
// player doit être +1 ou -1;
bool isWinner(int player) {
    int win = 3*player;
    return ( (board[0][0] + board[0][1] + board[0][2] == win)          // ligne 0
            || (board[1][0] + board[1][1] + board[1][2] == win)        // ligne 1
            || (board[2][0] + board[2][1] + board[2][2] == win)        // ligne 2
            || (board[0][0] + board[1][0] + board[2][0] == win)        // colonne 0
            || (board[0][1] + board[1][1] + board[2][1] == win)        // colonne 1
            || (board[0][2] + board[1][2] + board[2][2] == win)        // colonne 2
            || (board[0][0] + board[1][1] + board[2][2] == win)        // diagonale
            || (board[2][0] + board[1][1] + board[0][2] == win) );     // diagonale
}

// trouve le joueur gagnant. Renvoie EMPTY
// si aucun joueur ne gagne à ce stade.
int  getWinner() {
    if (isWinner(X)) return X;
    else if (isWinner(O)) return O;
    else return EMPTY;
}

// indique si le tableau est plein
// (les 9 cases sont non vides)
bool isFull() {
    for (int i=0;i<3;++i)
        for (int j=0;j<3;++j)
            if (board[i][j] == EMPTY)
                return false;
    return true;
}

// verifie le validite d'un movement.
// doit etre entre 1 et 9 (inclus) et
// la case corrspondant doit etre vide.
bool isValidMove(int n) {
    if(n<1 || n>9) return false;
    int i = iFromN(n);
    int j = jFromN(n);
    if(board[i][j] != EMPTY) return false;
    return true;
}

// affiche le tableau
void printBoard() {
    cout << "\n+-+-+-+\n";
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            switch (board[i][j]) {
                case X:     cout << "X"; break;
                case O:     cout << "O"; break;
                case EMPTY: cout << " "; break;
            }
            cout << "|" ;
        }
        cout << "     ";
        for (int j = 0; j < 3; j++)
            cout << j+3*i+1 << " ";
        cout << "\n+-+-+-+\n";
    }
}

// calcule le score estime par l'AI pour
// un movement donne.
//
// Vous pouvez appeler les fonctions suivantes
//
//      applyMove
//      eraseMove
//      isWinner
//      isFull
//      isValidMove
//
// et bien sur la fonction score elle-même cette
// fonction étant normalement recursive.
//

double score(int n, int player) {
    // A MODIFIER
    
    double playerScore = rand();
    return playerScore;
}

// choisit automatiquement le prochain mouvement
// comme etant celui qui donne le meilleur score
// appelle typiquement la fonction score ci-dessus.

int ai(int player) {
    // A MODIFIER

    int bestMove = 1+rand()%9;
    
    while (! isValidMove(bestMove) ) {
        bestMove = 1+rand()%9;
    }
    
    return bestMove;
}

// choisit interactivement le prochain mouvement
// en le demandant au joueur et en verifiant que
// le choix est licite.
// cette fonction est recursive si le choix est
// illicite.
int interactive(int player) {
    cout << endl << "Prochain mouvement du joueur " << ((player==X) ? "X" : "O" ) << ": " << flush;
    
    int n;
    cin >> n;
    cout << endl;
    
    if(!cin.good() || !isValidMove(n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Mouvement non valide. Essayez encore." << endl;
        return interactive(player);
    } else
        return n;
}

// choisit interactivement le nombre de joueurs humains
// en le demandant au joueur et en verifiant que
// le choix est licite.
// cette fonction est recursive si le choix est
// illicite.
int askNumberOfPlayers() {
    
    cout << "Combien de joueurs humains? (0,1 ou 2) " << flush;
    
    int n;
    cin >> n;
    cout << endl;
    
    if(!cin.good() || (n < 0) || (n>2) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Nombre de joueur invalide. " << endl;
        return askNumberOfPlayers();
    }
    else
        return n;
}

// programme principal. Demande le nombre de joueurs
// humains, choisit aleatoirement qui commence en cas
// de match humain/ordinateur. Puis boucle tant qu'il
// n'y a pas de vainqueur et que le tableau n'est pas
// plein. Affiche le resultat du match.
int main() {
    // joueur courant. +1 ou -1;
    int currentPlayer;
    // indique si un joueur est humain ou ordinateur
    bool human[2];
    
    srand ( (int) time(0) );
    
    int np = askNumberOfPlayers();
    
    switch(np) {
        case 0:
            human[0] = human[1] = false;
            break;
        case 1:
            human[0] = rand() % 2;  // choix aleatoire du premier joueur
            human[1] = !human[0];
            break;
        case 2:
            human[0] = human[1] = true;
            break;
    }
    
    clearBoard();
    currentPlayer = X;
    
    while( getWinner() == EMPTY && !isFull() ) {
        printBoard();
        
        int nextMove;
        if (human[(currentPlayer + 1) / 2])
            nextMove = interactive(currentPlayer);
        else {
            nextMove = ai(currentPlayer);
            cout << endl << "AI joue " << nextMove << endl;
        }
        applyMove(nextMove,currentPlayer);
        currentPlayer = - currentPlayer;
    }
    
    printBoard();
    
    int winner = getWinner();
    if (winner != EMPTY)
        cout << " \n\n" << (winner == X ? 'X' : 'O') << " gagne! \n\n\n";
    else
        cout << " \n\n Egalité! \n\n\n";
    
    return EXIT_SUCCESS;
}