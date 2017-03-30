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
#include "save_csv.h"

using namespace std::chrono;

unsigned testChercherPosition (const unsigned nb_iteration, const unsigned taille_tableau){
   vector<int> tab;
   
   unsigned sommeTotal = 0; 
   
   for (int i = 0; i < nb_iteration; i++){
      tab = CreeRemplirVectorTrier(taille_tableau);            
      MelangerVector(tab);
      sommeTotal += chercherPosition(tab, generateurAleatoire(taille_tableau + 1 ,0));      
   }
   
   unsigned moyenne = sommeTotal/nb_iteration;
   
   vector<unsigned> save {moyenne, taille_tableau};
   save_in_csv(save,"1.ChercherPosition.csv");
   
   return moyenne;
}

unsigned testTrier(const unsigned nbIteration, const unsigned nbElements){
    vector<int> v;
    unsigned sommeComp = 0;
    unsigned sommeSwap = 0;
    //cout << "tirer n Element, aléatoiers : " << nbElements << endl;

    for(int i = 0; i < nbIteration; i++){
        v = CreeVecteurAleatoire(nbElements);        
        unsigned nbComp = 0, nbSwap = 0;
        trier(v, nbComp, nbSwap);
        sommeComp += nbComp;
        sommeSwap += nbSwap;
        //cout << "nombre de comparaison : " <<  nbComp << "  nombre de swaps : " << nbSwap << endl;
    }
    unsigned moyenneComp = sommeComp/ nbIteration;
    unsigned moyenneSwap = sommeSwap/ nbIteration;
    vector<unsigned> save{moyenneComp, moyenneSwap, nbElements};
    save_in_csv(save,"2.Trier.csv");
    
    return sommeComp;
}

unsigned testChercherSiContient (const unsigned nb_iteration, const unsigned nb_elements){
   unsigned long long sommeTotal = 0;
   vector<int> v = CreeRemplirVectorTrier(nb_elements);
   for (unsigned i = 0; i < nb_iteration; ++i){
      unsigned valRandom = generateurAleatoire(nb_elements); //Pas d'element qui n'est pas dans la liste
      sommeTotal += chercherSiContient(v,valRandom);
   }
   unsigned moyenne = sommeTotal;///nb_iteration;
   vector<unsigned> save {moyenne, nb_elements};
   save_in_csv(save,"3.ChercherSiContient.csv");
   return moyenne;
}

unsigned testF (const unsigned nb_iteration){
   int cpt = 0;
   f(nb_iteration, cpt);
   
   vector<unsigned> save {cpt, nb_iteration};
   save_in_csv(save,"4.f.csv");
   
   return cpt;
}

unsigned testG (const unsigned nbIteration, const unsigned nbElement){
    vector<int> v;
    unsigned somme = 0;
    //cout << "o(N)log2(N) N : " << nbElement << endl;

    for(int i = 0; i < nbIteration; i++){
        v = CreeVecteurAleatoire(nbElement);        
        unsigned nbAdd = 0;
	//AfficherVector(v);
        g(v, nbAdd);
        somme+= nbAdd;
        //cout << "nombre additions : " <<  nbAdd<< endl;
	//AfficherVector(v);
	//cout << endl << "----------------------------------------------------------------------------------------------" << endl;
    }
    unsigned moyenne = somme/nbIteration;
    vector<unsigned> save{moyenne,nbElement};
    save_in_csv(save,"5.G.csv");
    return moyenne;

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
   vector<double> save{moyenne, n, maxVal};
   save_in_csv(save,"6.Random.csv");
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
   vector<double> save{moyenne, n, maxVal};
   save_in_csv(save,"7.Random2.csv");
   return moyenne;
}