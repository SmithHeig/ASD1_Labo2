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
   unsigned chercherSicontientCasMoyen = testChercherSiContient(10000,1000);
   cout << "ChercherSiContient moyenne: " << chercherSicontientCasMoyen << endl;
   
   double tempsRandomMoyen = testRandom(100,100,150);
   cout << "Temps Moyen  Random: " << tempsRandomMoyen << "ns" << endl;
}
