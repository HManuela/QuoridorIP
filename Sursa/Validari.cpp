#include "Joc.h"



int Joc::DistantaFinish(int jx, int jy, int fx, int fy)
{
	int diagx[4] = { -1, 1, 1,-1 };
	int diagy[4] = { -1,-1, 1, 1 };
	int path[10][10];

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			path[i][j] = -1;

	punct coada[90];
	int start, fin;
	start = 0;

	coada[start].x = jx;
	coada[start].y = jy;
	path[jx][jy] = 0;
	fin = 0;
	while (start <= fin)
	{
		for (int i = 0; i < 4; i++)
		{

			if (path[coada[start].x + diagx[i]][coada[start].y + diagy[i]] == -1)
				if (MiscareValida(coada[start].x, coada[start].y, coada[start].x + diagx[i], coada[start].y + diagy[i]))
				{
					fin++;
					coada[fin].x = coada[start].x + diagx[i];
					coada[fin].y = coada[start].y + diagy[i];
					path[coada[fin].x][coada[fin].y] = path[coada[start].x][coada[start].y] + 1;
				}

			if (path[coada[start].x + dx[i]][coada[start].y + dy[i]] == -1)
				if (MiscareValida(coada[start].x, coada[start].y, coada[start].x + dx[i], coada[start].y + dy[i]))
				{
					fin++;
					coada[fin].x = coada[start].x + dx[i];
					coada[fin].y = coada[start].y + dy[i];
					path[coada[fin].x][coada[fin].y] = path[coada[start].x][coada[start].y] + 1;
				}

			if (path[coada[start].x + dx[i] * 2][coada[start].y + dy[i] * 2] == -1)
				if (MiscareValida(coada[start].x, coada[start].y, coada[start].x + dx[i] * 2, coada[start].y + dy[i] * 2))
				{
					fin++;
					coada[fin].x = coada[start].x + dx[i] * 2;
					coada[fin].y = coada[start].y + dy[i] * 2;
					path[coada[fin].x][coada[fin].y] = path[coada[start].x][coada[start].y] + 1;
				}
		}
		start++;
	}
	int min = 100;

	if (fx == -1)
		for (int i = 0; i < 9; i++)
			if (path[i][fy] != -1)
				if (path[i][fy] < min)
					min = path[i][fy];
	if (fy == -1)
		for (int i = 0; i < 9; i++)
			if (path[fx][i] != -1)
				if (path[fx][i] < min)
					min = path[fx][i];
	return min;
}

bool Joc::MiscareValida(int jx, int jy, int destx, int desty)
{
	int ret = 0;
	if (!(jx <= 8 && jy <= 8 && destx <= 8 && desty <= 8 &&
		jx >= 0 && jy >= 0 && destx >= 0 && desty >= 0))
		return 0;
	int m_jx = 2 * jx + 1;
	int m_jy = 2 * jy + 1;
	int m_dx = 2 * destx + 1;
	int m_dy = 2 * desty + 1;
	if (matrice_pereti[(m_jx + m_dx) / 2][(m_jy + m_dy) / 2] != 0)
		return 0;
	//----------------------------------------

	//verific daca pot face o miscare mai complicata (salt dublu / in laterala)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < nrjucatori; j++)
		{
			if (jx + dx[i] == jucatori[j]->x &&
				jy + dy[i] == jucatori[j]->y)
			{
				if (destx == jx + dx[i] + dx[i] &&
					desty == jy + dy[i] + dy[i])
				{
					if (matrice_pereti[jx * 2 + 1 + dx[i]][jy * 2 + 1 + dy[i]] == M_LIBER
						&& matrice_pereti[jx * 2 + 1 + dx[i] * 3][jy * 2 + 1 + dy[i] * 3] == M_LIBER)
						if (matrice_pereti[destx * 2 + 1][desty * 2 + 1] == M_LIBER)
							ret = 1;
				}
			}
		}
		for (int j = 0; j < nrjucatori; j++)
		{
			if (matrice_pereti[jx * 2 + 1 + dx[i]][jy * 2 + 1 + dy[i]] == M_LIBER
				&& matrice_pereti[jx * 2 + 1 + dx[i] * 3][jy * 2 + 1 + dy[i] * 3] == M_PERETE)
			{
				if (jx + dx[i] == jucatori[j]->x &&
					jy + dy[i] == jucatori[j]->y)
				{
					for (int d = 0; d < 4; d++)
						if (matrice_pereti[(jx + dx[i] + dx[d]) * 2 + 1][(jy + dy[i] + dy[d]) * 2 + 1] == M_LIBER &&
							destx == jx + dx[i] + dx[d] &&
							desty == jy + dy[i] + dy[d]) //destinatia e libera si cea dorita
							if (matrice_pereti[(jx + dx[i]) * 2 + 1 + dx[d]][(jy + dy[i]) * 2 + 1 + dy[d]] == M_LIBER) // daca nu e perete
								ret = 1;
				}
			}
		}
	}

	for (int j = 0; j < nrjucatori; j++)
		if (destx == jucatori[j]->x && desty == jucatori[j]->y)
			return 0;
	for (int i = 0; i < 4; i++)
		if (destx + dx[i] == jx && desty + dy[i] == jy)
			return 1;

	return ret;
}

int Joc::TesteazaPerete(int x, int y, int orientare)
{
	PunePerete(x, y, orientare);
	int rezultat=100;
	for (int i = 0; i < nrjucatori; i++)
	{
		int fx, fy;
		if (jucatori[i]->finish == Jucator::N)
			fx = -1, fy = 0;
		if (jucatori[i]->finish == Jucator::S)
			fx = -1, fy = 8;
		if (jucatori[i]->finish == Jucator::E)
			fx = 8, fy = -1;
		if (jucatori[i]->finish == Jucator::V)
			fx = 0, fy = -1;

		int rez = DistantaFinish(jucatori[i]->x, jucatori[i]->y, fx, fy);
		if (rez < rezultat && tura!=i)
			rezultat = rez;
		if (rez < rezultat && tura == i)
			rezultat = 1;
		if (rez == 100)
		{
			ScoatePerete(x, y, orientare);
			if (DEBUG == 1) cout << "fail la testul de drum\n";
			return 0;
		}
	}
	ScoatePerete(x, y, orientare);
	if (rezultat == 100)
	{
		if (DEBUG == 1) cout << "fail la testul de drum\n";
		rezultat = 0;
	}
	return rezultat;
}

bool Joc::PereteValid(int pereti_ramasi, int x, int y, int orientare)
{
	int i;
	if (pereti_ramasi <= 0)
	{
		cout << "nu mai am pereti\n";
		return 0;
	}
	for (i = 0; i < nrpereti; i++)
	{
		if (pereti[i].orientare == orientare) // peretii sa nu se suprapuna
			if (orientare == VERTICAL)
			{
				if (abs(pereti[i].y - y) < 2 && x == pereti[i].x)
				{
					if (DEBUG==1)	cout << "peretele s-ar suprapune cu altul pe verticala\n";
					return 0;
				}
			}
			else
			{
				if (abs(pereti[i].x - x) < 2 && y == pereti[i].y)
				{
					if (DEBUG==1)	cout << "peretele s-ar suprapune cu altul pe orizontala\n";
					return 0;
				}
					
			}

		if (orientare == VERTICAL && pereti[i].orientare == ORIZONTAL) //sa nu se incruciseze (exista un singur caz de incrucisare - pct de inceput al fiecarui perete sa fie in diagonala)
		{
			if (pereti[i].y - y == 1 && x - pereti[i].x == 1)
			{
				if (DEBUG==1) cout << "peretele s-ar incrucisa cu un perete orizontal\n";
				return 0;
			}
		}
		if (orientare == ORIZONTAL && pereti[i].orientare == VERTICAL)
		{
			if (pereti[i].x - x == 1 && y - pereti[i].y == 1)
			{
				if (DEBUG==1) cout << "peretele s-ar incrucisa cu un perete vertical\n";
				return 0;
			}
		}
	}
	return TesteazaPerete(x, y, orientare);
}
