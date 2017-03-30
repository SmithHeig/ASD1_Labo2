/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "save_csv.h"

void save_in_csv (const vector<unsigned>& v, string name_file){
   fstream my_file;
   my_file.open(name_file, fstream::app);
   for(unsigned i = 0; i < v.size(); ++i){
      my_file << v.at(i) << ";";
   }
   my_file << endl;
   my_file.close();
}

