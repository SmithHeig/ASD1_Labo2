/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <random>
#include <ctime>
#include "tests.h"


/**
 * Recherche la position d'une valeur dans un vector.
 * 
 * Pour la complexitÃ©, on considÃ¨re le nombre d'itÃ©rations.
 * Tester pour diverses valeurs de val, prÃ©sentes ou non dans le vector.
 * 
 * @param v vector dans lequel on cherche
 * @param val valeur Ã  chercher
 * @return la position de la valeur dans le vector si trouvÃ©, -1 sinon
 */
size_t chercherPosition(const vector<int>& v, int val) {
   for (size_t i = 0; i < v.size(); ++i) {
      if (v.at(i) == val)
         return i;
   }
   return -1;
}

/**
 * Trie un vector.
 * 
 * Pour la complexitÃ©, on considÃ¨re le nombre de comparaisons (>)
 * 
 * @param v vector Ã  trier
 */
void trier(vector<int>& v) {
   if (v.empty()) return;

   for (int a : v) {
      auto j = v.begin();
      auto k = j++;
      for (; j != v.end(); k = j++)
         if (*k > *j)
            swap(*k, *j);
   }
}

/**
 * Retourne true si la valeur est contenue dans le vector.
 * 
 * Pour la complexitÃ©, on considÃ¨re le nombre d'itÃ©rations.
 * v doit Ãªtre triÃ© en entrÃ©e !
 * Tester pour diverses valeurs de val, prÃ©sentes ou non dans le vecteur.
 * 
 * @param v vector triÃ© dans lequel on cherche
 * @param val valeur Ã  chercher
 * Retourne true si la valeur est contenue dans le vector, false sinon.
 */
unsigned chercherSiContient(const vector<int>& v, int val) {
   unsigned cmpt = 1;
   auto first = v.begin();
   auto last = v.end();

   while (first != last) {
      auto mid = first + (last - first) / 2;
      if (*mid == val) {
         return cmpt;
      } else if (*mid < val) {
         first = mid + 1;
      } else {
         last = mid;
      }
      ++cmpt;
   }
   return cmpt;
}

/**
 * Pour la complexitÃ©, on considÃ¨re le nombre d'additions
 * 
 * @param n
 * @return 
 */
unsigned long long f(unsigned n) {

   if (n == 0) return 1;

   return f(n - 1) + f(n - 1) + f(n - 1);
}

/**
 * Pour la complexitÃ©, on considÃ¨re le nombre d'additions (+=)
 * 
 * @param v
 */
void g(vector<int>& v) {
   for (size_t i = 0; i < v.size(); ++i) {
      for (size_t j = v.size() - 1; j > 0; j /= 2) {
         v.at(i) += v.at(j);
      }
   }
}

/**
 * Pour la complexitÃ©, on considÃ¨re les opÃ©rations push_back()
 * 
 * Evaluer le temps d'exÃ©cution
 * 
 * @param N nombre de donnÃ©es Ã  gÃ©nÃ©rer
 * @param maxVal valeur maximale des donnÃ©es
 * @return vector rempli de N valeurs alÃ©atoires.
 */
vector<int> random(size_t N, int maxVal) {

   vector<int> v;
   for (size_t i = 0; i < N; ++i) {
      v.push_back(1 + rand() % maxVal);
   }

   return v;
}

/**
 * Pour la complexitÃ©, on considÃ¨re les opÃ©rations insert()
 * 
 * Evaluer le temps d'exÃ©cution
 * 
 * @param N nombre de donnÃ©es Ã  gÃ©nÃ©rer
 * @param maxVal valeur maximale des donnÃ©es
 * @return vector rempli de N valeurs alÃ©atoires.
 */
vector<int> random2(size_t N, int maxVal) {

   vector<int> v;
   for (size_t i = 0; i < N; ++i) {
      v.insert(v.begin(), 1 + rand() % maxVal);
   }

   return v;
}