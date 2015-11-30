#pragma once

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <utility>

#define BUFFER_SIZE 1024

using namespace std;


long double sigmoide(long double fInput);
long double random (long double fMin, long double fMax);
int random (int fMin, int fMax);
bool random_bool();



typedef struct
{
	int idInput; // n�gatif pour les entr�es du reseau
	long double weight;

} structLink;


