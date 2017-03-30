/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "random.h"
#include <time.h>
#include <stdlib.h>

/********************************************************************************************************
 * Nom    : generateurAleatoire
 * But    : Génère de facon aléatoire un entier compris entre deux valeurs entrées en paramètres.
 * Retour : int, la valeur générée aléatoirement.
 * Param  : - int min, valeur minimale pouvant être générée
 *          - int max, valeur maximale pouvant être générée 
 *******************************************************************************************************/
int generateurAleatoire(const int max, const int min){
   // initialiation unique du générateur
   static bool first = true;
   if (first) {
      srand ((unsigned int)time (NULL));
      first = !first;
   }
   return (rand() % (max - min)) + min;
}