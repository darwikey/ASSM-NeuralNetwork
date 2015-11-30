#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <utility>

using namespace std;


long double sigmoide(long double fInput);
long double random (long double fMin, long double fMax);
int random (int fMin, int fMax);
bool random_bool();



typedef struct
{
	int id_entree; // négatif pour les entrées du reseau
	long double poids;

} struct_lien;


