#include "stdafx.h"




long double sigmoide(long double fInput)
{
	long double _sortie;
	_sortie = 1/ ( 1 + exp( -fInput ) );
	
	return _sortie;
}


long double random (long double fMin, long double fMax)
{
	long double interval = fMax - fMin;
	return fMin + interval * rand()/(long double)RAND_MAX;
}


int random (int fMin, int fMax)
{
	int interval = fMax - fMin;
	return fMin + rand() % interval;
}

bool random_bool()
{
	int a = rand();
	a = 1 & a;
	return a!=0;
}

