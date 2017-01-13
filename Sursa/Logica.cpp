#include "Joc.h"

void Joc::Logic_Meniu()
{
	if (doaction == 1)
	{
		if (input.y == 3 && input.x >= 3 && input.x <= 5)
		{
			//play
			stare = PREGAME;
		}
		if (input.y == 4 && input.x >= 3 && input.x <= 5)
		{
			//help
			stare = HELP;
		}
		if (input.y == 5 && input.x >= 3 && input.x <= 5)
		{
			stare = EXIT;
		}
		doaction = 0;
	}
}


void Joc::Logic_Pregame()
{
	if (doaction == 1)
	{
		if (input.y == 4 && input.x == 4)
		{
			//play
			stare = JOC;
		}
		if (input.y == 1 && input.x == 4) // galben sus 
			set_pion[Jucator::G] = (set_pion[Jucator::G] + 1) % 3;

		if (input.y == 3 && input.x == 4) // galben jos
			set_pion[Jucator::G] = (set_pion[Jucator::G] + 2) % 3;

		if (input.y == 5 && input.x == 4) //rosu sus 
			set_pion[Jucator::R] = (set_pion[Jucator::R] + 1) % 3;

		if (input.y == 7 && input.x == 4) // rosu jos 
			set_pion[Jucator::R] = (set_pion[Jucator::R] + 2) % 3;

		if (input.y == 4 && input.x == 1) // maro stanga 
			set_pion[Jucator::M] = (set_pion[Jucator::M] + 1) % 3;

		if (input.y == 4 && input.x == 3) // maro dreapta
			set_pion[Jucator::M] = (set_pion[Jucator::M] + 2) % 3;

		if (input.y == 4 && input.x == 5) // portocaliu stanga
			set_pion[Jucator::P] = (set_pion[Jucator::P] + 1) % 3;

		if (input.y == 4 && input.x == 7) // portocaliu dreapta
			set_pion[Jucator::P] = (set_pion[Jucator::P] + 2) % 3;

		doaction = 0;
	}

}


void Joc::Logic()
{
	if (input.tip == PERETE)
	{
		if (input.orientare == ORIZONTAL && input.x >= 8) input.x = 7;
		if (input.orientare == VERTICAL && input.y >= 8) input.y = 7;
		input.valid = PereteValid(jucatori[tura]->pereti_ramasi, input.x, input.y, input.orientare);
	}
	if (input.tip == CASUTA)
		input.valid = MiscareValida(jucatori[tura]->x, jucatori[tura]->y, input.x, input.y);




	if (doaction == 1)
	{
		if (input.tip == PERETE)
		{
			if (input.valid)
			{
				PunePerete(input.x, input.y, input.orientare);

				jucatori[tura]->pereti_ramasi--;
				tura = (tura + 1) % nrjucatori;
			}
		}
		if (input.tip == CASUTA)
		{
			if (input.valid)
			{
				matrice_pereti[jucatori[tura]->x][jucatori[tura]->y] = M_LIBER;
				jucatori[tura]->x = input.x;
				jucatori[tura]->y = input.y;
				matrice_pereti[jucatori[tura]->x][jucatori[tura]->y] = M_JUCATOR;
				tura = (tura + 1) % nrjucatori;
				input.valid = 0;
			}

		}
	
		doaction = 0;
	}

}
