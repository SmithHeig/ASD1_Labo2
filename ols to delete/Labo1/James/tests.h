/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tests.h
 * Author: James
 *
 * Created on 23. février 2017, 11:30
 */

#ifndef TESTS_H
#define TESTS_H

#include <vector>

using namespace std;

unsigned testChercherPosition (const unsigned NB_ITERATION);
unsigned testTrier(const unsigned nb_iteration);
unsigned testChercherSiContient (const unsigned nb_iteration, const unsigned nbElements);
unsigned testF (const unsigned nb_iteration);
unsigned testG (const unsigned nb_iteration);
double testRandom (const unsigned nb_iteration, unsigned n, unsigned maxVal);

#endif /* TESTS_H */

