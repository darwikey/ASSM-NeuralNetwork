#pragma once

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include "_kiss_fft_guts.h"

#define REAL float

#define BUFFER_SIZE 1024
#define GENERATOR_SIZE 100

using namespace std;


REAL sigmoide(REAL fInput);
REAL random (REAL fMin, REAL fMax);
int random (int fMin, int fMax);
bool randomBool();



typedef struct
{
	int idInput; // n�gatif pour les entr�es du reseau
	REAL weight;

} structLink;


