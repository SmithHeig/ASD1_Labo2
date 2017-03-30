/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "vector.h"
#include "random.h"


vector<int> CreeRemplirVectorTrier(unsigned taille){
   vector<int> v(taille);
   for (unsigned i = 0; i < taille;){
      v.at(i) = ++i;
   }
   return v;
}

void MelangerVector (vector<int>& v) {
   for (unsigned i = 0; i < v.size(); ++i) {
      swap(v.at(i), v.at(generateurAleatoire(v.size())));
   }
}

void AfficherVector (vector<int>& v) {
   cout << "[";
   for(unsigned i = 0; i < v.size(); ++i) {
      if (i != 0){
         cout << ",";
      }
      cout << v.at(i);
   }
   cout << "]" << endl;
}

vector<int> CreeVecteurAleatoire(unsigned taille) {
   vector<int> v = CreeRemplirVectorTrier(taille);
   MelangerVector(v);
   return v;
}

