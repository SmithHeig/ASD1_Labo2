   //Test n°6, random
   cout << "****Debut test no 6, random : \n\n";
   NB_TEST = 50;
   unsigned nbAAjouter = 0;
   unsigned maxVal;

   for(unsigned i = 1; i <= 200 ; i++){
      if(i%2 == 0){ 
         maxVal = 100000;

      }else{
         maxVal = 100;
         nbAAjouter += 100;
      }  
      cout << "N : " << nbAAjouter << "\t\tValMax : " << maxVal << "\tTemps[ns] : " 
              << testRandom(NB_TEST, nbAAjouter, maxVal) << endl;
   }
   cout << "\n***Fin du test no 6, random " << endl << endl << endl;
   
   
   //Test n°7, random2
   cout << "****Debut test no 7, random2 : \n\n";
   NB_TEST = 50;
   nbAAjouter = 0;
   maxVal;

   for(unsigned i = 1; i <= 200 ; i++){
      if(i%2 == 0){ 
         maxVal = 1000;
      }else{
         maxVal = 100;
         nbAAjouter += 100;
      }  
      cout << "N : " << nbAAjouter << "\t\tValMax : " << maxVal << "\tTemps[ns] : " 
              << testRandom2(NB_TEST, nbAAjouter, maxVal) << endl;
   }
   cout << "\n***Fin du test no 7, random2 " << endl << endl << endl;
}
