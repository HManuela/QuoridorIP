#include "Jucator.h"


Jucator::Jucator()
{
	finish = S;
	x = 4;
	y = 0;
	pion = G;
}

Jucator::Jucator(int fin=S, int culoare=G)
{
	finish = fin;
	if (fin == S)
	{
		x = 4;
		y = 0;
	}

	if (fin == N)
	{
		x = 4;
		y = 8;
	}

	pion = culoare;
}


Jucator::~Jucator()
{
}
