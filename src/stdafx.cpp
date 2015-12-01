#include "stdafx.h"




REAL sigmoide(REAL fInput)
{
	REAL _sortie;
	_sortie = 1/ ( 1 + exp( -fInput ) );
	
	return _sortie;
}


REAL random (REAL fMin, REAL fMax)
{
	REAL interval = fMax - fMin;
	return fMin + interval * rand()/(REAL)RAND_MAX;
}


int random (int fMin, int fMax)
{
	int interval = fMax - fMin;
	return fMin + rand() % interval;
}

bool randomBool()
{
	int a = rand();
	a = 1 & a;
	return a!=0;
}
