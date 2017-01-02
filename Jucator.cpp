#include "Jucator.h"


Jucator::Jucator()
{
	finish = S;
	x = 4;
	y = 0;
	pion = G;
}

Jucator::Jucator(int fin, int culoare, int pereti_ram)
{
	pereti_ramasi = pereti_ram;
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

	if (fin == E)
	{
		x = 0;
		y = 4;
	}

	if (fin == V)
	{
		x = 8;
		y = 4;
	}


	pion = culoare;
}

bool Jucator::Castigat()
{
	if (finish == N && y == 0)
		return 1;
	if (finish == S && y == 8)
		return 1;
	if (finish == E && x == 8)
		return 1;
	if (finish == V && x == 0)
		return 1;
	return 0;
}


Jucator::~Jucator()
{
}
