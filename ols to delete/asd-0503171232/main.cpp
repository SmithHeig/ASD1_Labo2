//
//  Labo1.cpp
//  Labos ASD1 2017
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright Â© 2016 Olivier Cuisenaire. All rights reserved.
//
//	/* NOMS DES ETUDIANTS ICI */
//

#include "tests.h"
#include <iostream>

using namespace std;



int main() {
   
   //Test n°1, chercher position
   cout << "****Debut test no 1, chercher position : \n\n";
   unsigned NB_ITERATION = 1000;
   double temp;
   cout << "Nombre de test : " << NB_ITERATION << endl << endl;
   for (unsigned i = 10; i <= 100000; i *= 10){
      temp = testChercherPosition(NB_ITERATION, i);
      cout << "Taille tableau : " << i << "\tMoyenne : " <<  temp <<
              "\tTaille/moyenne : " << double(i)/temp << endl;
   }
   cout << "\n***Fin du test no 1, chercher position " << endl << endl << endl;
   
   
   //Test n°2, trier
   cout << "****Debut test no 2, trier : \n\n";
   NB_ITERATION = 20;
   cout << "Nombre de test : " << NB_ITERATION << endl << endl;
   for (unsigned i = 0; i <= 100; i += 10){      
      temp = testTrier(NB_ITERATION, i);
      
      cout << "Nombre d'element : " << i << "\tMoyenne " << temp <<
              "\tNombre element / moyenne" << double(i)/temp << endl;
   }
   cout << "\n***Fin du test no 2, trier " << endl << endl << endl;
//   
//      cout << testTrier(20, 1) << endl <<
//   testTrier(20, 10) << endl <<
//   testTrier(20, 20) << endl <<
//   testTrier(20, 40) << endl <<
//   testTrier(20, 50) << endl <<
//   testTrier(20, 60) << endl;
    
      //Test n°3, Chercher si contient
   cout << "****Debut test no 3, Chercher si contient : \n\n";
   NB_ITERATION = 100;
   cout << "Nombre de test : " << NB_ITERATION << endl << endl;
   for (unsigned i = 100; i <= 10000000; i *= 10){      
      temp = testChercherSiContient(NB_ITERATION, i);
      
      cout << "Nombre d'element : " << i << "\tMoyenne " << temp << endl;
   }
   cout << "\n***Fin du test no3, Chercher si contient " << endl << endl << endl;
      
      
      
//         cout << testChercherSiContient(100,100) << endl <<
//   testChercherSiContient(100,1000) << endl <<
//   testChercherSiContient(100,10000) << endl <<
//   testChercherSiContient(100,100000) << endl <<
//   testChercherSiContient(100,1000000) << endl <<
//   testChercherSiContient(100,10000000) << endl;
//   cout << "ChercherSiContient: Fini" << endl;
//   
   
   
   
   
      //Test n°4, f
   cout << "****Debut test no 4, f : \n\n";
   int tmp; 
   int old = 0;
   unsigned NB_TEST = 15;
   for (int i = 0; i < NB_TEST; i++){

   tmp = testF(i);
   cout <<"Somme : " << tmp << "\tNouvelle valeur : " << tmp-old << "\tnouvelle valeur /2 : " << (tmp - old)/2 << endl;
   old = tmp;
   }
   cout << "\n***Fin du test no 4, f " << endl << endl << endl;
   
   
     //Test n°5, g
   cout << "****Debut test no 5, g : \n\n";
      NB_TEST = 15;
   for (unsigned i = 1; i <= 100000; i*=10){
      temp = testG(NB_TEST, i);
      cout << "N : " << i << "\tNombre d'addition" << temp << "\tnb d'addition / N " << temp/i <<  endl;
   }
   cout << "\n***Fin du test no 5, g " << endl << endl << endl;
//           cout << testG(100,1) << endl <<
//      testG(100,10) << endl <<
//      testG(100,100) << endl <<
//      testG(100,1000) << endl <<
//      testG(100,10000) << endl <<
//      testG(100,100000) << endl;
//   
   
   
   
   
   //Test n°6, random
   cout << "****Debut test no 6, random : \n\n";
   NB_TEST = 100;
   unsigned nbAAjouter = 10;
   unsigned maxVal;

   for(unsigned i = 1; i <= 10 ; i++){
      if(i%2 == 0){ 
         maxVal = 100000;

      }else{
         maxVal = 100;
         nbAAjouter *= 10;
      }  
      cout << "N : " << nbAAjouter << "\t\tValMax : " << maxVal << "\tTemps[ns] : " 
              << testRandom(NB_TEST, nbAAjouter, maxVal) << endl;
   }
   cout << "\n***Fin du test no 6, random " << endl << endl << endl;
   
   
   //Test n°7, random2
   cout << "****Debut test no 7, random2 : \n\n";
   NB_TEST = 100;
   nbAAjouter = 10;
   maxVal;

   for(unsigned i = 1; i <= 6 ; i++){
      if(i%2 == 0){ 
         maxVal = 1000;
      }else{
         maxVal = 100;
         nbAAjouter *= 10;
      }  
      cout << "N : " << nbAAjouter << "\t\tValMax : " << maxVal << "\tTemps[ns] : " 
              << testRandom2(NB_TEST, nbAAjouter, maxVal) << endl;
   }
   cout << "\n***Fin du test no 7, random2 " << endl << endl << endl;
}
