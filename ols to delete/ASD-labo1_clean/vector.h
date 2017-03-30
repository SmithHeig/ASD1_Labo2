/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vector.h
 * Author: James
 *
 * Created on 23. février 2017, 11:19
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

using namespace std;

vector<int> CreeRemplirVectorTrier(unsigned taille);
vector<int> CreeVecteurAleatoire(unsigned taille);
void MelangerVector (vector<int>& v);
void AfficherVector (vector<int>& v);

#endif /* VECTOR_H */

