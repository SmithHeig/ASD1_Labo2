//
//  P4CentreAleatoire.h
//
//  Created by Olivier Cuisenaire on 08.03.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//

#ifndef P4CentreAleatoire_h
#define P4CentreAleatoire_h


#include "P4Interface.h"
#include <array>
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

class P4CentreAleatoire : public P4Interface {
private:
	friend std::ostream& operator <<(std::ostream&, const P4CentreAleatoire&);
	
	// A COMPLETER SELON VOS BESOINS EN ATTRIBUTS ET METHODES PRIVEES
	const int MIN_INT_VAL = numeric_limits<int>::lowest(); // TODO: Utiliser lower / max ou inf...?
	const int MAX_INT_VAL = numeric_limits<int>::max();
	
	const static size_t NB_LIGNES = 6;
	const static size_t NB_COLONNES = 7;
	
	Player grilleDeJeu[NB_LIGNES][NB_COLONNES];
	
	size_t indiceDerniereColonneJouee;
	size_t indiceDerniereLigneJouee;
	
	//size_t coupAJouerX;
	//size_t coupAJouerO;
	
	unsigned compteurCoupsRestants;
	
	//bool nbPionAlignes(int incrementLigne, size_t incrementColonne, const Player& p);
	
	bool getScore(int incrementLigne, size_t incrementColonne, const Player& p) const;
	
	void supprimerDernierCoupJoue();
	
	int scoreColonneMiniMax(size_t cln, const Player& p, size_t profondeur);
	
	int scoreColonneAlphaBeta(size_t cln, int alpha, int beta, const Player& p, size_t profondeur);
	
	int valeurCase(int incrementLigne, size_t incrementColonne, size_t indiceLgn, size_t indiceCln, const Player& p);
	
	int valeurPosition(const Player& p);

public:
	// NE PAS MODIFIER L'INTERFACE PUBLIC.
	// IMPLEMENTER LES METHODES SEPAREMENT
	// DANS UN FICHIER .CPP
	
	/**
	 *  @brief Constructeur par defaut
	 */
	P4CentreAleatoire();
	
	/**
	 *  @brief Remet à zèro les attributs pour jouer une nouvelle partie
	 */
	void reset();
	
	/**
	 *  @brief Le joueur p joue dans la colonne c.
	 *
	 *  @param c Le numero de colonne entre 0 et 6
	 *  @param p Le joueur X ou O
	 */
	void playInColumn(size_t c, Player p);
	
	/**
	 *  @brief Verifie si le joueur p gagne
	 *
	 *  @param p Le joueur X ou O
	 *
	 *  @return vrai si 4 a la suite pour p, faux sinon
	 */
	bool isWinner(Player p) const;
	
	/**
	 *  @brief Verifie si jouer dans la colonne c est valide
	 *
	 *  @param c Le numero de colonne entre 0 et 6
	 *
	 *  @return vrai si c est entre 0 et 6 et que la
	 *          colonne n'est pas pleine. Faux sinon
	 */
	bool isValidMove(size_t c) const;
	
	/**
	 *  @brief Choisit la prochain mouvement pour le joueur p
	 *
	 *  @param p     Le joueur X ou O
	 *  @param depth La profondeur de recherche de l'algorithme minimax
	 *
	 *  @return retourne un numero de colonne entre 0 et 6
	 *          sans modifier l'etat de la grille du jeu
	 *          typiquement calcule avec une variante a
	 *          choix de l'algorithme minimax
	 */
	size_t chooseNextMove(Player p, unsigned depth);
	
	/**
	 *  @brief Renvoie le nom de votre classe pour le tournoi
	 *
	 *  @return Un nom qui sera typiquement tronque a l'affichage
	 *          pour ne garder que les 4 premieres lettres
	 */
	std::string getName() const;
};

/**
 *  @brief Surcharge de << pour afficher la grille du jeu
 *
 *  @param std::ostream&     le flux utilise pour laffichage
 *  @param P4& un objet de votre classe P4
 *
 *  @return le flux original
 */
std::ostream& operator <<(std::ostream&, const P4CentreAleatoire&);


#endif /* P4_h */
