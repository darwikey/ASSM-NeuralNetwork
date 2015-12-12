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

#define BUFFER_SIZE 1024
#define GENERATOR_SIZE 100


float sigmoide(float fInput);
float random (float fMin, float fMax);
int random (int fMin, int fMax);
bool randomBool();



typedef struct
{
	int idInput; // négatif pour les entrées du reseau
	float weight;

} structLink;


