#include "stdafx.h"



float random (float fMin, float fMax)
{
	float interval = fMax - fMin;
	return fMin + interval * rand()/(float)RAND_MAX;
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
