/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tests.h
 * Author: James
 *
 * Created on 23. février 2017, 11:30
 */

#ifndef TESTS_H
#define TESTS_H

#include <vector>

using namespace std;

/**
 * @brief Test la fonction ChercherPosition et calcule le nombre d'itération réalisé 
 *        pour une quantité N de données
 * @param nb_iteration nombre de fois à réalisé le test pour en faire une moyenne plausible
 * @return nombre d'itération moyenne de la fonction ChercherPosition
 */
unsigned testChercherPosition (const unsigned nb_iteration, const unsigned taille_tableau);

/**
 * @brief Test la fonction trier et compte le nombre d'itération réalisé 
 *        selon une quantité N de données
 * @param nb_iteration nombre de fois à réalisé le test
 * @return nombre d'itération moyenne de la fonction Trier
 */
unsigned testTrier(const unsigned nbIteration, const unsigned nbElements);

/**
 * @brief Test la fonction ChercherSiContient et compte le nombre d'itération réalisé
 *        pour un nombre N de données
 * @param nb_iteration nombre de fois à réalisé la fonction
 * @param nb_elements nombre d'élément qui compose le vector dans lequel 
 *        nous exécutons la recherche
 * @return nombre d'itération moyenne de la fonction ChercherSiContient
 */
unsigned testChercherSiContient (const unsigned nb_iteration, const unsigned nbElements);

/**
 * @brief test la fonction f et calcule le nombre d'itération réalisé pour un nombre 
 *        N de données
 * @param nb_iteration nombre de fois à réalisé la fonction
 * @return nombre d'itération moyenne de la fonction f
 */
unsigned testF (const unsigned nb_iteration);
unsigned testG (const unsigned nbIteration, const unsigned nbElement);
double testRandom (const unsigned nb_iteration, unsigned n, unsigned maxVal);
double testRandom2 (const unsigned nb_iteration, unsigned n, unsigned maxVal);

#endif /* TESTS_H */

