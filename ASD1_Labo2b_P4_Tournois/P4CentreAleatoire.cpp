#include "P4CentreAleatoire.h"
#include <vector>
// A COMPLETER

P4CentreAleatoire::P4CentreAleatoire() {
	reset();
}

void P4CentreAleatoire::reset() {
	for (size_t lgn = 0; lgn < NB_LIGNES; ++lgn) {
		for (int cln = 0; cln < NB_COLONNES; ++cln) { // TODO: A  tester -> pourquoi le 2eme .size() est violet..?
			grilleDeJeu[lgn][cln] = EMPTY;
		}
	}
	
	//coupAJouerX = NB_COLONNES + 1;
	//coupAJouerO = NB_COLONNES + 1;
	compteurCoupsRestants = 42;
}

/*
bool P42::nbPionAlignes(int incrementLigne, size_t incrementColonne, const Player& p) {
	size_t score = 1;
	
	for (int i = 1; i < 4; ++i) {
		size_t indiceLigne = indiceDerniereLigneJouee + incrementLigne * i;
		size_t indiceColonne = indiceDerniereColonneJouee + incrementColonne * i;
		bool testIndiceLignes = indiceLigne < NB_LIGNES;
		bool testIndiceColonnes = indiceColonne < NB_COLONNES;
		if (testIndiceLignes && testIndiceColonnes) {
			if (grilleDeJeu[indiceLigne][indiceColonne] == p) {
				score++;
			} else if (grilleDeJeu[indiceLigne][indiceColonne] == EMPTY && score == 3) {
				if (p == X) {
					coupAJouerO = indiceColonne;
				} else {
					coupAJouerX = indiceColonne;
				}
				return true;
			} else {
				break;
			}
		}
	}
	
	for (int i = -1; i > -4; --i) {
		size_t indiceLigne = indiceDerniereLigneJouee + incrementLigne * i;
		size_t indiceColonne = indiceDerniereColonneJouee + incrementColonne * i;
		bool testIndiceLignes = indiceLigne < NB_LIGNES;
		bool testIndiceColonnes = indiceColonne < NB_COLONNES;
		if (testIndiceLignes && testIndiceColonnes) {
			if (grilleDeJeu[indiceLigne][indiceColonne] == p) {
				score++;
			} else if (grilleDeJeu[indiceLigne][indiceColonne] == EMPTY && score == 3) {
				if (p == X) {
					coupAJouerO = indiceColonne;
				} else {
					coupAJouerX = indiceColonne;
				}
				return true;
			} else {
				break;
			}
		}
	}
	return false;
}
 */

void P4CentreAleatoire::playInColumn(size_t c, Player p) {
	if (isValidMove(c)) {
		size_t lgn = NB_LIGNES - 1;
		
		while (grilleDeJeu[lgn][c] != EMPTY) {
			--lgn;
		}
		grilleDeJeu[lgn][c] = p;
		
		// On enregistre la position du dernier coup joue. Elle sera utilise pour verifier si le coup est gagnant.
		indiceDerniereColonneJouee = c;
		indiceDerniereLigneJouee = lgn;
		
		compteurCoupsRestants--;
		/*
		if (nbPionAlignes(1, 0, p)) {}
		else if (nbPionAlignes(0, 1, p)) {}
		else if (nbPionAlignes(1, 1, p)) {}
		else if (nbPionAlignes(-1, 1, p));
		 */
	}
}

void P4CentreAleatoire::supprimerDernierCoupJoue() {
	if (grilleDeJeu[indiceDerniereLigneJouee][indiceDerniereColonneJouee] == EMPTY) { // TODO: A SUPPRIMER AVANT DE RENDRE!!!!!!
		cout << "------------------------ ERREUR !!!!!!!!!! -------------------------------" << endl;
	}
	grilleDeJeu[indiceDerniereLigneJouee][indiceDerniereColonneJouee] = EMPTY;
	compteurCoupsRestants++;
}

bool P4CentreAleatoire::getScore(int incrementLigne, size_t incrementColonne, const Player& p) const {
	size_t score = 1;
	
	for (int i = 1; i < 4; ++i) {
		size_t indiceLigne = indiceDerniereLigneJouee + incrementLigne * i;
		size_t indiceColonne = indiceDerniereColonneJouee + incrementColonne * i;
		bool testIndiceLignes = indiceLigne < NB_LIGNES;
		bool testIndiceColonnes = indiceColonne < NB_COLONNES;
		if (testIndiceLignes && testIndiceColonnes && grilleDeJeu[indiceLigne][indiceColonne] == p) {
			score++;
		} else {
			break;
		}
	}
	
	for (int i = -1; i > -4; --i) {
		size_t indiceLigne = indiceDerniereLigneJouee + incrementLigne * i;
		size_t indiceColonne = indiceDerniereColonneJouee + incrementColonne * i;
		bool testIndiceLignes = indiceLigne < NB_LIGNES;
		bool testIndiceColonnes = indiceColonne < NB_COLONNES;
		if (testIndiceLignes && testIndiceColonnes && grilleDeJeu[indiceLigne][indiceColonne] == p) {
			score++;
		} else {
			break;
		}
	}
	
	return score >= 4;
}

bool P4CentreAleatoire::isWinner(Player p) const {
	return getScore(1, 0, p) || // test colonne gagnante
	       getScore(0, 1, p) || // test ligne gagnante
	       getScore(1, 1, p) || // test diagonale descendante gagnante
	       getScore(-1, 1, p); // test diagonale montante gagnante
}

bool P4CentreAleatoire::isValidMove(size_t c) const {
	return c < NB_COLONNES && grilleDeJeu[0][c] == EMPTY;
}

size_t P4CentreAleatoire::chooseNextMove(Player p, unsigned profondeur)  // A Modifier
{
	static bool firstMove = true;
	
	int grilleScore[NB_COLONNES] = {0};
	int maximum = MIN_INT_VAL;
	//int alpha;
	//int beta;
	
	if (firstMove) {
		firstMove = false;
		return NB_COLONNES / 2;
	}
	
	//size_t mvt = (rand() % NB_COLONNES);
	for (unsigned i = 0; i < NB_COLONNES; ++i) {
		size_t coupAJouer = i;
		//size_t coupAJouer = (mvt + i) % NB_COLONNES;
		if (isValidMove(coupAJouer)) {
			//alpha = MIN_INT_VAL;
			//beta = MAX_INT_VAL;
			//grilleScore[i] = scoreColonneAlphaBeta(coupAJouer, alpha, beta, p, profondeur); // TODO: commenter cette ligne et décommenter celle du dessous afin d'utiliser ou non l'elagage alpha beta.
			grilleScore[i] = scoreColonneMiniMax(i, p, profondeur);
			if (grilleScore[i] > maximum) {
				maximum = grilleScore[i];
			}
		} else {
			grilleScore[i] = MIN_INT_VAL;
		}
	}
	
	size_t meilleurCoupAJouer;
	//if (coupAJouerX >= NB_COLONNES && coupAJouerO >= NB_COLONNES) {
	size_t grilleMeilleursCoupsAJouer[NB_COLONNES];
	size_t taille = 0;
	for (unsigned i = 0; i < NB_COLONNES; ++i) {
		if (grilleScore[i] >= maximum) {
			grilleMeilleursCoupsAJouer[taille++] = i;
		}
	}
	meilleurCoupAJouer = grilleMeilleursCoupsAJouer[(rand() % taille)];
	/*} else if (p == X) {
		meilleurCoupAJouer = coupAJouerO;
		coupAJouerO = NB_COLONNES + 1;
	} else {
		meilleurCoupAJouer = coupAJouerX;
		coupAJouerX = NB_COLONNES + 1;
	}*/
	
	return meilleurCoupAJouer;
}

int P4CentreAleatoire::scoreColonneMiniMax(size_t cln, const Player& p, size_t profondeur) {
	int scoreJoueur = MIN_INT_VAL;
	int scoreCln = MIN_INT_VAL;
	
	playInColumn(cln, p);
	size_t derniereCln = indiceDerniereColonneJouee;
	size_t derniereLgn = indiceDerniereLigneJouee;
	
	if (isWinner(p)) { // le coup nous fait gagner
		scoreJoueur = MAX_INT_VAL; // GAGNE!!  +inf -> MEILLEUR SCORE POSSIBLE
	} else if (!compteurCoupsRestants) { // il ne reste plus de coup à jouer, donc les joueurs sont egalite
		scoreJoueur = 0;
	} else if (profondeur == 0) { // On arrete la recursion car on a atteint la profondeur maximale et on evalue la position
		scoreCln = valeurPosition(p);
		//scoreJoueur = valeurPosition(p);
	} else { // on ne gagne pas, ya pas egalite et on a pas atteint la profondeur maximale, alors on continue la recursion
		Player adversaire = p == X ? O : X; // si jouer = X, alors adversaire = O, si joueur != X, alors adversaire = X
		int scoreAdversaire = MIN_INT_VAL;
		int clnAleatoire = rand() % NB_COLONNES;
		for (size_t colonne = 0; colonne < NB_COLONNES; ++colonne) {
			//size_t coupAJouer = (derniereCln - 1 + colonne) % NB_COLONNES; // TODO: voir si c'est mieux de commencer depuis la colonne du dernier coup joué plutôt que de toujours commencer par la colonne 0 ?
			size_t coupAJouer = colonne;
			if (isValidMove(coupAJouer)) {
				scoreAdversaire = scoreColonneMiniMax(coupAJouer, adversaire,
				                                      profondeur - 1); // TODO: je n'ai fait que changer cln par colonne et notre algo est devenu sur-intelligent...!
				
				scoreJoueur = scoreAdversaire > scoreJoueur ? scoreAdversaire : scoreJoueur;
			}
		}
		scoreJoueur = -scoreJoueur;
	}
	
	if (scoreCln > scoreJoueur) {
		scoreJoueur = scoreCln;
	}
	
	indiceDerniereColonneJouee = derniereCln;
	indiceDerniereLigneJouee = derniereLgn;
	
	supprimerDernierCoupJoue();
	return scoreJoueur;
}

int P4CentreAleatoire::scoreColonneAlphaBeta(size_t cln, int alpha, int beta, const Player& p, size_t profondeur) {
	int scoreJoueur = MIN_INT_VAL;
	int scoreCln = MIN_INT_VAL;
	
	playInColumn(cln, p);
	size_t derniereCln = indiceDerniereColonneJouee;
	size_t derniereLgn = indiceDerniereLigneJouee;
	
	if (isWinner(p)) { // le coup nous fait gagner
		scoreJoueur = MAX_INT_VAL; // GAGNE!!  +inf -> MEILLEUR SCORE POSSIBLE
	} else if (!compteurCoupsRestants) { // il ne reste plus de coup à jouer, donc les joueurs sont egalite
		scoreJoueur = 0;
	} else if (profondeur == 0) { // On arrete la recursion car on a atteint la profondeur maximale et on evalue la position
		scoreCln = valeurPosition(p);
		//scoreJoueur = valeurPosition(p);
	} else { // on ne gagne pas, ya pas egalite et on a pas atteint la profondeur maximale, alors on continue la recursion
		int meilleurScore = MIN_INT_VAL;
		int scoreAdversaire;
		Player adversaire = p == X ? O : X; // si jouer = X, alors adversaire = O, si joueur != X, alors adversaire = X
		//size_t mvt = (rand() % NB_COLONNES);
		for (size_t colonne = 0; colonne < NB_COLONNES; ++colonne) {
			size_t coupAJouer = (derniereCln - 1 + colonne) % NB_COLONNES;
			if (isValidMove(coupAJouer)) {
				scoreAdversaire = scoreColonneAlphaBeta(coupAJouer, -beta, -alpha, adversaire, profondeur - 1);
				meilleurScore = meilleurScore >= scoreAdversaire ? meilleurScore : scoreAdversaire;
				alpha = alpha > beta ? alpha : beta;
				if (alpha >= beta) {
					break;
				}
			}
		}
		scoreJoueur = -meilleurScore;
	}
	
	if (scoreCln > scoreJoueur) {
		scoreJoueur = scoreCln;
	}
	
	indiceDerniereColonneJouee = derniereCln;
	indiceDerniereLigneJouee = derniereLgn;
	
	supprimerDernierCoupJoue();
	return scoreJoueur;
}

int P4CentreAleatoire::valeurCase(int incrementLigne, size_t incrementColonne, size_t indiceLgn, size_t indiceCln, const Player& p) {
	int score = 0;
	short nbPionsAlignes = 1;
	bool coteDroitBoucheParAdversaire = false;
	Player adversaire = p == X ? O : X; // si jouer = X, alors adversaire = O, si joueur != X, alors adversaire = X
	for (int i = 1; i < 4; ++i) {
		size_t indiceLigne = indiceLgn + incrementLigne * i;
		size_t indiceColonne = indiceCln + incrementColonne * i;
		bool testIndiceLignes = indiceLigne < NB_LIGNES;
		bool testIndiceColonnes = indiceColonne < NB_COLONNES;
		
		if (testIndiceLignes && testIndiceColonnes) {
			if (grilleDeJeu[indiceLigne][indiceColonne] == p) {
				nbPionsAlignes++;
				if (i == 1) {
					score += 20;
				} else if (i == 2) {
					score += 10;
				} else {
					score += 5;
				}
				
				if (nbPionsAlignes == 3) {
					score += 100;
				} else if (nbPionsAlignes == 2) {
					score += 10;
				}
			} else if (grilleDeJeu[indiceLigne][indiceColonne] == adversaire) { // le cote est "bouche" par un pion adverse
				coteDroitBoucheParAdversaire = true;
				break;
			} /*else if (grilleDeJeu[indiceLigne][indiceColonne] == EMPTY && nbPionsAlignes == 3) {
				if (p == X) {
					coupAJouerO = indiceColonne;
				} else {
					coupAJouerX = indiceColonne;
				}
			}*/
		} else {
			break;
		}
	}
	for (int i = -1; i > -4; --i) {
		size_t indiceLigne = indiceLgn + incrementLigne * i;
		size_t indiceColonne = indiceCln + incrementColonne * i;
		bool testIndiceLignes = indiceLigne < NB_LIGNES;
		bool testIndiceColonnes = indiceColonne < NB_COLONNES;
		
		if (testIndiceLignes && testIndiceColonnes) {
			if (grilleDeJeu[indiceLigne][indiceColonne] == p) {
				nbPionsAlignes++;
				if (i == -1) {
					score += 20;
				} else if (i == -2) {
					score += 10;
				} else {
					score += 5;
				}
				
				if (nbPionsAlignes == 3) {
					score += 100;
				} else if (nbPionsAlignes == 2) {
					score += 10;
				}
			} else if (grilleDeJeu[indiceLigne][indiceColonne] == adversaire) { // le cote est "bouche" par un pion adverse
				score = coteDroitBoucheParAdversaire ? 0 : score; // les deux cotes sont bouches par l'adversaire -> score = 0
				break;
			} /*else if (grilleDeJeu[indiceLigne][indiceColonne] == EMPTY && nbPionsAlignes == 3) {
				if (p == X) {
					coupAJouerO = indiceColonne;
				} else {
					coupAJouerX = indiceColonne;
				}
			}*/
		} else {
			break;
		}
	}
	return score;
}

int P4CentreAleatoire::valeurPosition(const Player& p) {
	int valeurPosition = valeurCase(1, 0, indiceDerniereLigneJouee, indiceDerniereColonneJouee, p) // valeur de la colonne
	                     + valeurCase(0, 1, indiceDerniereLigneJouee, indiceDerniereColonneJouee, p) // valeur de la ligne
	                     + valeurCase(1, 1, indiceDerniereLigneJouee, indiceDerniereColonneJouee, p) // valeur de la diagonale descendante
	                     + valeurCase(-1, 1, indiceDerniereLigneJouee, indiceDerniereColonneJouee, p); // valeur de la diagonale montante
	
	/* //TODO: Je n'arrive pas à déterminer si cela sert à quelque chose ou non...!
	Player adversaire = p == X ? O : X; // si jouer = X, alors adversaire = O, si joueur != X, alors adversaire = X
	//adversaire = p == X ? O : X;
	
	//int valeurPositionAdversaire =
	valeurPosition -= valeurCase(1, 0, indiceDerniereLigneJouee - 1, indiceDerniereColonneJouee, adversaire)
	                  + valeurCase(0, 1, indiceDerniereLigneJouee - 1, indiceDerniereColonneJouee, adversaire)
	                  + valeurCase(1, 1, indiceDerniereLigneJouee - 1, indiceDerniereColonneJouee, adversaire)
	                  + valeurCase(-1, 1, indiceDerniereLigneJouee - 1, indiceDerniereColonneJouee, adversaire);
	*/
	
	return valeurPosition;
}


string P4CentreAleatoire::getName() const {
	return "BENO";
}

ostream& operator <<(ostream& os, const P4CentreAleatoire& p4) {
	for (size_t i = 0; i < P4CentreAleatoire::NB_LIGNES; ++i) {
		cout << "|";
		for (int j = 0; j < P4CentreAleatoire::NB_COLONNES; ++j) {
			string p;
			if (p4.grilleDeJeu[i][j] == 1) {
				p = "X";
			} else if (p4.grilleDeJeu[i][j] == -1) {
				p = "0";
			} else {
				p = " ";
			}
			cout << " " + p + " |";
		}
		cout << endl;
	}
	cout << "-----------------------------" << endl;
	cout << "  0   1   2   3   4   5   6" << endl;
	return os << endl;
}