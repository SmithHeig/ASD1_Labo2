/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <chrono>
#include "vector.h"
#include "complexite.h"
#include "random.h"

using namespace std::chrono;

unsigned testChercherPosition (const unsigned nb_iteration){
   for (unsigned i = 0; i < nb_iteration; ++i){
   }
}

unsigned testTrier(const unsigned nb_iteration){
   
}

unsigned testChercherSiContient (const unsigned nb_iteration, const unsigned nbElements){
   unsigned long long sommeTotal = 0;
   vector<int> v = CreeRemplirVectorTrier(nbElements);
   for (unsigned i = 0; i < nb_iteration; ++i){
      unsigned valRandom = generateurAleatoire(nbElements); //Pas d'element qui n'est pas dans la liste
      sommeTotal += chercherSiContient(v,valRandom);
   }
   unsigned moyenne = sommeTotal/nb_iteration;
   return moyenne;
}

unsigned testF (const unsigned nb_iteration){
   
}

unsigned testG (const unsigned nb_iteration){
   //test f
   int cpt = 0;
   for (int i = 0; i < 10; i++){
      f(i, cpt);
      cout << "Pour n = " << i << " : " << setw(8) << cpt  << " et cpt/3 = " << cpt/2.0 << endl;
      cpt = 0;
   }
}

double testRandom (const unsigned nb_iteration, unsigned n, unsigned maxVal){
   double temps = 0.0;
   for (unsigned i = 0; i < nb_iteration; ++i){
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      random(n, maxVal);
      high_resolution_clock::time_point t2 = high_resolution_clock::now();
      temps += duration_cast<nanoseconds>( t2 - t1 ).count();
   }
   double moyenne = temps / nb_iteration;
   return moyenne;
}



double testRandom2 (const unsigned nb_iteration, unsigned n, unsigned maxVal){
   double temps = 0.0;
   for (unsigned i = 0; i < nb_iteration; ++i){
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      random2(n, maxVal);
      high_resolution_clock::time_point t2 = high_resolution_clock::now();
      temps += duration_cast<nanoseconds>( t2 - t1 ).count();
   }
   double moyenne = temps / nb_iteration;
   return moyenne;
}