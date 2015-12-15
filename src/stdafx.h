#pragma once

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "_kiss_fft_guts.h"

// taille du buffer utilis� par la fft et l'entr� du r�seau de neurone
#define BUFFER_SIZE 1024

// nombre de g�n�rateurs de son
#define GENERATOR_COUNT 100

// nombre de g�n�rations pour l'algorihtme g�n�tique
#define GENERATION_COUNT 50

// nombre d'individus par g�n�ration dans l'algorithme g�n�tique
#define POOL_SIZE 200


float random (float fMin, float fMax);
int random (int fMin, int fMax);
bool randomBool();


