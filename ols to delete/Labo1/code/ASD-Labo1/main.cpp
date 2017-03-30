//
//  Labo1.cpp
//  Labos ASD1 2017
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	/* NOMS DES ETUDIANTS ICI */
//

#include <stdlib.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;


int generateurAleatoire(const int max, const int min){
   // initialiation unique du générateur
   static bool first = true;
   if (first) {
      srand ((unsigned int)time (NULL));
      first = !first;
   }
   return (rand() % (max - min)) + min;
}

/**1Guillaume
 * Recherche la position d'une valeur dans un vector.
 * 
 * Pour la complexité, on considère le nombre d'itérations.
 * Tester pour diverses valeurs de val, présentes ou non dans le vector.
 * 
 * @param v vector dans lequel on cherche
 * @param val valeur à chercher
 * @return la position de la valeur dans le vector si trouvé, -1 sinon
 */
size_t chercherPosition( const vector<int>& v , int val ) {
  for(size_t i = 0; i < v.size(); ++i) {
    if(v.at(i) == val)
      return i;
  }
  return -1;
}

unsigned testChercherPosition (const unsigned nb_iteration){
   for (unsigned i = 0; i < nb_iteration; ++i){
      
   }
}

vector<int> CreeRemplirVectorTrier(unsigned taille){
   vector<int> v(taille);
   for (unsigned i = 0; i < taille;){
      v.at(i) = ++i;
   }
   return v;
}


void MelangerVector (vector<int>& v) {
   for (unsigned i = 0; i < v.size(); ++i) {
      swap(v.at(i), v.at(generateurAleatoire(v.size(),0 )));
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


/**4Guillaume
 * Pour la complexité, on considère le nombre d'additions
 * 
 * @param n
 * @return 
 */
unsigned long long f( unsigned n, int& cpt ) {
 
  if( n == 0 ) return 1;
  cpt += 2;
  return f(n-1, cpt) + f(n-1, cpt) + f(n-1, cpt);
}

/**7Guillaume
 * Pour la complexité, on considère les opérations insert()
 * 
 * Evaluer le temps d'exécution
 * 
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
/*
vector<int> random2( size_t N , int maxVal ) {
  
  vector<int> v;
  for(size_t i = 0; i < N; ++i) {
    v.insert(v.begin(), 1 + rand() % maxVal);
  }
  return v;
}*/
/*
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
}*/

int main() {
   //initialisation du générateur aléatoire
   srand (time(NULL));
   const int TAILLE_TABLEAU = 100000;
   vector<int> tab;
   vector<int> tabResultat(TAILLE_TABLEAU);
/*
   for (int i = 0; i< TAILLE_TABLEAU; i++){
      tab = CreeRemplirVectorTrier(TAILLE_TABLEAU);            
      MelangerVector(tab);
      tabResultat.at(i) = chercherPosition(tab, generateurAleatoire(TAILLE_TABLEAU+1 ,0));
   }

   double moyenne = 0;
   //AfficherVector(tabResultat);
   for (int i = 0; i < tabResultat.size(); i++){
      moyenne += tabResultat.at(i);
   }
   cout << "moyenne : " << moyenne/tabResultat.size() << endl;*/

   //test f
   int cpt = 0;
   for (int i = 0; i < 10; i++){
      f(i, cpt);
      cout << "Pour n = " << i << " : " << setw(8) << cpt  << " et cpt/3 = " << cpt/2.0 << endl;
      cpt = 0;
   }
   
   //test random2
//   int nbIte = 2;
//      for (int i = 1; i <= 100000; i*= 10){
//         for (int j = 1; j <= 100000; j*=10){
//            cout << "Nombre de donnee : " <<setw(10)<< i << "  maxVal : " << setw(10)<< j 
//                    << "  Temps moyen (" << nbIte << ") : " <<setw(15) <<  testRandom2(nbIte, i, j) << endl;
//         }
//      }            
}
            

            
            
         
///**6James
// * Pour la complexité, on considère les opérations push_back()
// * 
// * Evaluer le temps d'exécution
// * 
// * @param N nombre de données à générer
// * @param maxVal valeur maximale des données
// * @return vector rempli de N valeurs aléatoires.
// */
//vector<int> random( size_t N , int maxVal ) {
//  
//  vector<int> v;
//  for(size_t i = 0; i < N; ++i) {
//    v.push_back(1+rand()%maxVal);
//  }
//  
//  return v;
//}       

























//
//
///**2Joel
// * Trie un vector.
// * 
// * Pour la complexité, on considère le nombre de comparaisons (>)
// * 
// * @param v vector à trier
// */
//void trier( vector<int>& v ) {
//  if(v.empty()) return;
//  
//  for(int a : v) {
//    auto j = v.begin();
//    auto k = j++;
//    for(; j != v.end(); k = j++ )
//      if(*k > *j )
//        swap(*k, *j);
//  }
//}
//
///**3James
// * Retourne true si la valeur est contenue dans le vector.
// * 
// * Pour la complexité, on considère le nombre d'itérations.
// * v doit être trié en entrée !
// * Tester pour diverses valeurs de val, présentes ou non dans le vecteur.
// * 
// * @param v vector trié dans lequel on cherche
// * @param val valeur à chercher
// * Retourne true si la valeur est contenue dans le vector, false sinon.
// */
//bool chercherSiContient( const vector<int>& v , int val ) {
//  auto first = v.begin();
//  auto last = v.end();
//  
//  while( first != last ) {
//    auto mid = first + ( last - first ) / 2;
//    if(*mid == val) {
//      return true;
//    } else if(*mid < val) {
//      first = mid+1;
//    } else {
//      last = mid;
//    }
//  }
//  return false;
//}
//
///**4Guillaume
// * Pour la complexité, on considère le nombre d'additions
// * 
// * @param n
// * @return 
// */
//unsigned long long f( unsigned n ) {
// 
//  if( n == 0 ) return 1;
//  
//  return f(n-1) + f(n-1) + f(n-1);
//}
//
///**5Joel
// * Pour la complexité, on considère le nombre d'additions (+=)
// * 
// * @param v
// */
//void g( vector<int>& v ) {
//  for(size_t i = 0; i < v.size(); ++i) {
//    for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
//      v.at(i) += v.at(j);
//    }
//  }
//}
//
///**6James
// * Pour la complexité, on considère les opérations push_back()
// * 
// * Evaluer le temps d'exécution
// * 
// * @param N nombre de données à générer
// * @param maxVal valeur maximale des données
// * @return vector rempli de N valeurs aléatoires.
// */
//vector<int> random( size_t N , int maxVal ) {
//  
//  vector<int> v;
//  for(size_t i = 0; i < N; ++i) {
//    v.push_back(1+rand()%maxVal);
//  }
//  
//  return v;
//}
//
///**7Guillaume
// * Pour la complexité, on considère les opérations insert()
// * 
// * Evaluer le temps d'exécution
// * 
// * @param N nombre de données à générer
// * @param maxVal valeur maximale des données
// * @return vector rempli de N valeurs aléatoires.
// */
//vector<int> random2( size_t N , int maxVal ) {
//  
//  vector<int> v;
//  for(size_t i = 0; i < N; ++i) {
//    v.insert(v.begin(),1+rand()%maxVal);
//  }
//  
//  return v;
//}


