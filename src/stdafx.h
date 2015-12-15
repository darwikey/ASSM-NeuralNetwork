#pragma once

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "_kiss_fft_guts.h"

// taille du buffer utilisé par la fft et l'entré du réseau de neurone
#define BUFFER_SIZE 1024

// nombre de générateurs de son
#define GENERATOR_COUNT 100

// nombre de générations pour l'algorihtme génétique
#define GENERATION_COUNT 50

// nombre d'individus par génération dans l'algorithme génétique
#define POOL_SIZE 200


float random (float fMin, float fMax);
int random (int fMin, int fMax);
bool randomBool();


